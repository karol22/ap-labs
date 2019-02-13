//Karol Gutierrez
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
    if (argc < 2){
        printf("Error: missing message \n");
        return 1;
    } 
    char *origin="/dev/pts/";
    DIR *dir=opendir(origin);
    if (dir==NULL){
        printf("Error! \n");
        return 1;
    } 
    struct dirent *parent;
    parent=readdir(dir); 
    while(parent!=NULL){//search for all names
        char *route=malloc(1+sizeof(char)*(strlen(parent->d_name)+strlen(origin)));
        strcpy(route, origin);
        strcat(route, parent->d_name);
        int user=open(route, O_WRONLY);
        int i=0;
        for(i=1;i<argc;i++){
            write(user, argv[i], strlen(argv[i]));
            write(user, " ", 1); //add space between words
        }
        write(user, "\n", 1);//add endline
        close(user);
        parent=readdir(dir);
        free(route);
    }
    closedir(dir);
}