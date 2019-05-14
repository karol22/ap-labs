typedef struct food{
    int X;
    int Y;
    char symbol;

}food;

void food_init(food *food1){
    food1->X=(rand()%(NCOLS-5))+1;
    food1->Y=(rand()%(NROWS-5))+1;
    food1->symbol='F';
}

void food_print(food *food1){
    gotoxy(food1->X,food1->Y);
    printf("%c",food1->symbol);
}
