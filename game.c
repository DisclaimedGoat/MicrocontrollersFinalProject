#include "stm32l476xx.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "render.h"
#include "game.h"
#include "screens.h"
#include "LCD.h"
#include "ports.h"

#define LCD_REFRESH_TICKS 25

#define NONE  0
#define LEFT  1
#define RIGHT 2
#define UP    3
#define DOWN  4

#define TIME  15

#define START 0
#define RUN   1
#define PAUSE 2
#define OVER  3
#define HIGH  4

unsigned int* game_array;
unsigned int* space_array;
unsigned int* player_array;
static int state = 0;
static int direction = NONE;
static int player_delay = 0;
static int speed;
static unsigned int timer = TIME;
static unsigned int score = 0;
static unsigned int high_score = 0;
static unsigned int explosion = 0;
const char* DIFFICULTIES[4] = { "      Easy >    ", "   < Medium >   ", "    < Hard >    ", "   < Insane     " };
static unsigned int difficulty = 0;
static unsigned int character = 0;
static char name[3] = {'/', '/', '/'};

static int lcd_refresh_count = 0;

void game_init(void)
{
    game_array   = (unsigned int*) malloc(sizeof(int) * SIZEX);
    space_array  = (unsigned int*) malloc(sizeof(int) * SIZEX);
    player_array = (unsigned int*) malloc(sizeof(int) * SIZEX);
    for (int i = 0; i < SIZEX; i++)
    {
        game_array[i]   = START_SCREEN[i];
        space_array[i]  = EMPTY_SCREEN[i];
        player_array[i] = PLAYER_SCREEN[i];
    }

    state = START;
}

void update_lcd() {
	// Only update every 'LCD_REFRESH_TICKS'
	if (++lcd_refresh_count % LCD_REFRESH_TICKS != 0) return;
	
	char* buff;
	snprintf(buff, 32, "Count: %d", lcd_refresh_count);
	LCD_Print(buff);
}

void next_game_frame(void)
{
	check_inputs();
	
    switch(state)
    {
        case START:
            timer++;
            for (int i = 0; i < SIZEX; i++)
            {
                game_array[i]   = START_SCREEN[i];
                space_array[i]  = EMPTY_SCREEN[i];
                player_array[i] = PLAYER_SCREEN[i];
            }
            LCD_PrintLine(0, "- Level Select -");
            switch (direction)
            {
                case LEFT:
                    if (speed > 0)
                    {
                        speed -= 2;
                        difficulty--;
                        while (direction == LEFT)
						{
							direction = NONE;
                            check_inputs();
						}
                    }
                    break;
                case RIGHT:
                    if (speed < 6)
                    {
                        speed += 2;
                        difficulty++;
                        while (direction == RIGHT)
						{
						    direction = NONE;
                            check_inputs();
						}
                    }
                    break;
            }
            LCD_PrintLine(1, DIFFICULTIES[difficulty]);
            break;
        case RUN:
            timer--;
            int checkBit = 0;
            for (int i = 0; i < SIZEX; i++)
            {
                checkBit |= space_array[i];
            }
            if (!(checkBit >> 20)) // Need a new obstacle
            {
                int obstacle = (int) rand() % 6;
                for (int i = 0; i < SIZEX; i++)
                {
                    switch(obstacle)
                    {
                        case 0: 
                            space_array[i] |= RIGHT_OBSTACLE_SCREEN[i];
                            break;
                        case 1: 
                            space_array[i] |= LEFT_OBSTACLE_SCREEN[i];
                            break;
                        case 2: 
                            space_array[i] |= MID_OBSTACLE_SCREEN[i];
                            break;
                        case 3: 
                            space_array[i] |= BOTH_OBSTACLE_SCREEN[i];
                            break;
                        case 4: 
                            space_array[i] |= BOTH_LEFT_OBSTACLE_SCREEN[i];
                            break;
                        case 5: 
                            space_array[i] |= BOTH_RIGHT_OBSTACLE_SCREEN[i];
                            break;            
                    }   
                }
            }
                    
            switch(direction)
            {
                case LEFT:
                    if (player_array[0] == 0 && player_delay <= 0)
                    {
                        for (int i = 0; i < SIZEX - 1; i++)
                            player_array[i] = player_array[i + 1];
                        player_array[SIZEX - 1] = 0;
                        player_delay = 8;
                    }
                    break;
                case RIGHT:
                    if (player_array[SIZEX - 1] == 0 && player_delay <= 0)
                    {
                        for (int i = SIZEX - 1; i > 0; i--)
                            player_array[i] = player_array[i - 1];
                        player_array[0] = 0;
                        player_delay = 8;
                    }
                    break;
                case NONE:
                    player_delay = 0;
                    break;
            }
            player_delay--;

            if (timer == speed)
            {
                timer = TIME;
                if ((checkBit & 1) && (checkBit & 2) == 0)
                {
                    score++;
                    char score_str[17];
                    sprintf(score_str, "Score: %-9d", score);
                    LCD_PrintLine(1, score_str);
                    if ((score % 10) == 0 && speed < 10)
                    {
                        speed++;
                        buzz(5, 10);
                    }
                }
                for (int i = 0; i < SIZEX; i++)
                {
                    space_array[i] >>= 1;
                    game_array[i] = space_array[i] | player_array[i];
                    if (space_array[i] & player_array[i])
                    {
                        state = OVER;
                        timer = 5;
                    }
                }
            }
            break;
        case PAUSE:
            break;
        case OVER:
            speed = 0;
            timer--;
            put_odr_bit(GPIOB, P4, 1);
            delay(40);
            put_odr_bit(GPIOB, P4, 0);
            delay(40);
            if (timer <= 0)
            {
                for (int i = 0; i < SIZEX; i++)
                {
                    game_array[i] = PLAYER_EXPLOSION_SCREENS[explosion][i]; // change this to explosion later
                } 
                explosion++;
                if (explosion > 3)
				{
                    if (score > high_score)
                    {
                        high_score = score;
                        state = HIGH;
                        timer = 20;
                        char high_str[17];
                        sprintf(high_str, "NEW BEST! %-6d", high_score);
                        LCD_PrintLine(0, high_str);
                        name[0] = '/';
                        name[1] = '/';
                        name[2] = '/';
                        for (int i = 0; i < SIZEX; i++)
                        {
                            game_array[i] = EMPTY_SCREEN[i]; // change this to explosion later
                        } 
                    }
                    else
                        state = START;
                    score = 0;
                    explosion = 0;
				}
				timer = 5;
            }
            break;
        case HIGH:
            check_inputs();
            if (character == 2 && direction == RIGHT)
            {
                while (direction == RIGHT)
                {
                    direction = NONE;
                    check_inputs();
                }
                state = START;
                character = 0;
            }
            else
            {
                char cur_char = name[character];
                switch(direction)
                {
                    case UP:
                        cur_char++;
                        if (cur_char > 57 && cur_char < 65)
                            cur_char = 65;
                        else if (cur_char > 90)
                            cur_char = 48;
                        name[character] = cur_char;
                        while (direction == UP)
						{
							direction = NONE;
                            check_inputs();
						}
                        break;
                    case DOWN:
                        cur_char--;
                        if (cur_char > 57 && cur_char < 65)
                            cur_char = 57;
                        else if (cur_char < 48)
                            cur_char = 90;
                        name[character] = cur_char;
                        while (direction == DOWN)
						{
							direction = NONE;
                            check_inputs();
						}
                        break;
                    case RIGHT:
                        if (cur_char != '/')
                            character++;
                        while (direction == RIGHT)
						{
							direction = NONE;
                            check_inputs();
						}
                        break;
                }
            }
            timer--;
            char name_str[20];
            if (timer <= 5)
            {
                switch (character)
                {
                    case 0:
                        sprintf(name_str, "Enter name:  %c%c  ", name[1], name[2]);
                        break;
                    case 1:
                        sprintf(name_str, "Enter name: %c %c  ", name[0], name[2]);
                        break;
                    case 2:
                        sprintf(name_str, "Enter name: %c%c   ", name[0], name[1]);
                        break;
                }
            }
            else
                sprintf(name_str, "Enter name: %s  ", name);
            if (timer <= 0)
                timer = 20;
            LCD_PrintLine(1, name_str);
            break;
    } 

	renderScreen(game_array);

	direction = NONE;
			
	if (timer == speed)
			timer = TIME;
	
	// update_lcd();
}

void check_inputs(void)
{
    if (GPIOB->IDR & 15)
    {
        if (GPIOB->IDR & 1) // Red Button
        {
            direction = UP;
            if (state == RUN)
                state = PAUSE;
			return;
        }
        if (GPIOB->IDR & 2) // Green Button
        {
            direction = DOWN;
            if (state == START)
            {
                srand(timer);
                timer = TIME;
                difficulty = 0;
                char high_score_str[17];
                sprintf(high_score_str, "High: %s - %-5d", name, high_score);
                LCD_PrintLine(0, high_score_str);
                LCD_PrintLine(1, "Score: 0        ");

            }
            if (state == START || state == PAUSE)
                state = RUN;
			return;
        }
        if (GPIOB->IDR & 4) // Yellow Button
        {
            direction = LEFT;
			return;
        }
        if (GPIOB->IDR & 8) // Blue Button
        {
            direction = RIGHT;
			return;
        }
    }
}

void buzz(unsigned int count, unsigned int d_count)
{
    put_odr_bit(GPIOB, P4, 0);
    for (int i = 0; i < count; i++)
    {
        put_odr_bit(GPIOB, P4, 1);
        delay(d_count);
        put_odr_bit(GPIOB, P4, 0);
        delay(d_count);
    }
}

void delay(unsigned int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 80; j++)
            ;
}