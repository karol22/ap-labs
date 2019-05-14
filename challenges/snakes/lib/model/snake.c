typedef struct Snake{
    char symbol;
    int size;
    char direction;
    char prev_direction;
    int tail_X;
    int tail_Y;
    int head_X;
    int head_Y;

}snake;

void snake_init(snake *snake1, char symb){
    snake1->symbol=symb;
    snake1->size=10;
    snake1->direction=RIGHT;
    snake1->prev_direction=DOWN;
    int x = rand()%(NROWS-5);
    int y = rand()%(NCOLS-5);
    snake1->tail_X=x;
    snake1->tail_Y=y;
    snake1->head_X=snake1->tail_X+snake1->size-1;
    snake1->head_Y=y;
}