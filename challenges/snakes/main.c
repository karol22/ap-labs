#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <ncurses.h>

int num_enemies;
int num_fruits;

#include "lib/controller/config.c"
#include "lib/controller/print_to_console.c"
#include "lib/view/print_field.c"
#include "lib/view/instructions.c"
#include "lib/controller/keyboard_input.c"
#include "lib/model/food.c"
#include "lib/model/snake.c"
#include "lib/model/snake_positions.c"
#include "lib/controller/move_snake.c"
#include "lib/controller/game_step.c"


int main(){
    print_instructions();
      
      int snake_speed=100000;
      int score=0;

      snake a_snake;
      snake_pos pos1;
      food food1;
      snake_init(&a_snake);
      pos_init(&pos1);
      food_init(&food1);

      system("clear");
      system("stty -echo");             
      snake_place(&a_snake,&pos1);
      set_borders();
      food_print(&food1);

      system ("/bin/stty raw");

      while(!(game_over(&a_snake,&pos1))){
          while (!kbhit()){
                 usleep(snake_speed);
                 snake_move(&a_snake,&pos1,&food1,&score);
                 if (game_over(&a_snake,&pos1)) break;
          }
          a_snake.prev_direction=a_snake.direction;
          int w = getchar();
          if(w == UP || w == DOWN || w == LEFT || w == RIGHT)
            a_snake.direction=w;
     }
      system ("/bin/stty cooked");
      system("stty echo");
      system("clear");
      printf("\n\n Game finished, your score: %d \n\n", score);
      return 0;
}
