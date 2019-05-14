void gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,x,y);
}

void printScreen(){
    system("clear"); 
    gotoxy(0, 0);
    printf("\t\t\t\t\tMULTI-SNAKE GAME\n"); 
    int i, j, lines =2;
    for(i=0; i<VERTICAL; i++){
        for(j=0; j<HORIZONTAL; j++){
            if(i==0 || j==0 || i==VERTICAL - 1 || j== HORIZONTAL - 1){
                gotoxy(i+lines, j);
                printf("X");
            }
        }
    }
}