#include "stm32l476xx.h"
#include "render.h"
#include "game.h"
#include "screens.h"
#include "stdlib.h"
#include "time.h"

#define NONE  0
#define LEFT  1
#define RIGHT 2

#define TIME  10

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
static int speed = 0;
static int timer = TIME;
static unsigned int score = 0;
static unsigned int high_score = 0;
static unsigned int explosion = 0;
const unsigned char* DIFFICULTIES[4] = { "Easy", "Medium", "Hard", "Insane" };
static unsigned int difficulty = 0;

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

    srand(10000); 
}

void next_game_frame(void)
{
    check_inputs();
	
    switch(state)
    {
        case START:
            for (int i = 0; i < SIZEX; i++)
            {
                game_array[i]   = START_SCREEN[i];
                space_array[i]  = EMPTY_SCREEN[i];
                player_array[i] = PLAYER_SCREEN[i];
            }
            switch (direction)
            {
                case LEFT:
                    if (speed < 6)
                    {
                        speed += 2;
                        difficulty++;
                        // Print difficulty
                        while (direction == LEFT)
                            check_inputs();
                    }
                    break;
                case RIGHT:
                    if (speed > 0)
                    {
                        speed -= 2;
                        difficulty--;
                        // Print difficulty
                        while (direction == RIGHT)
                            check_inputs();
                    }
                    break;
            }
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
                        player_delay = 2;
                    }
                    break;
                case RIGHT:
                    if (player_array[SIZEX - 1] == 0 && player_delay <= 0)
                    {
                        for (int i = SIZEX - 1; i > 0; i--)
                            player_array[i] = player_array[i - 1];
                        player_array[0] = 0;
                        player_delay = 2;
                    }
                    break;
                case NONE:
                    player_delay = 0;
                    break;
            }
            player_delay--;

            if (timer == speed)
            {
                if ((checkBit & 1) && (checkBit & 2) == 0)
                {
                    score++;   
                    if ((score % 10) == 0 && speed < TIME)
                        speed++;
                }
                for (int i = 0; i < SIZEX; i++)
                {
                    space_array[i] >>= 1;
                    game_array[i] = space_array[i] | player_array[i];
                    if (space_array[i] & player_array[i])
                    {
                        state = OVER;
                    }
                }
						timer = TIME;
            }
            break;
        case PAUSE:
            break;
        case OVER:
            timer--;
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
                        state = HIGH;
                    else
                        state = START;
                    explosion = 0;
				}
				timer = TIME * 2;
            }
            break;
        case HIGH:
            // put in name
            state = START;
            break;
    } 

    renderScreen(game_array);

    direction = NONE;
}

void check_inputs(void)
{
    if (GPIOB->IDR & 15)
    {
        if (GPIOB->IDR & 1) // Red Button
        {
            state = PAUSE;
			return;
        }
        if (GPIOB->IDR & 2) // Green Button
        {
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