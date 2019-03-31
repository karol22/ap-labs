#include <ctype.h>
#include <dirent.h>    
#include <stdlib.h>  
#include <stdio.h> 
#include "logger.h"
#include <signal.h> 
#include <string.h>
#include <sys/types.h> 
#include <time.h>
#include <unistd.h> 
#define ROOT "/proc"

DIR * direc;
struct dirent * entry;
FILE * file;
char* pid;
char* parent;
char *path;
char* name;
char* pState;
char* threads;
char* memory;
char* helper;
char* word;
char* topFile;
char* route;

//functions
void clear();
FILE * getSnapshot();
void printLine(int opened, int mode);
void getProcessInfo(int mode);
void signalHandler(int sig);
void process();

int main() {
    // Place your magic here
    initLogger("stdout");
    direc = opendir(ROOT);
    entry = readdir(direc);
    pid = malloc(1000*sizeof(char));
    parent= malloc(1000*sizeof(char));
    path= malloc(1000*sizeof(char));
    name= malloc(1000*sizeof(char));
    pState= malloc(1000*sizeof(char));
    threads= malloc(1000*sizeof(char));
    memory= malloc(1000*sizeof(char));
    helper= malloc(1000*sizeof(char));
    topFile= malloc(1000*sizeof(char));
    route= malloc(1000*sizeof(char));
    word= malloc(1000*sizeof(char));

    signal(SIGINT, signalHandler);

    while(1) {
        process();
    }
}

void clear() {
  system("clear");
}
FILE * getSnapshot() {
    FILE * outFile;
    time_t t = time(NULL);
    struct tm today = * localtime( & t);
    sprintf(topFile, "mytop-status-%d%d%d", today.tm_mday, today.tm_mon + 1, today.tm_year + 1900);
    outFile = fopen(topFile, "w");
    return outFile;
}
void printLine(int opened, int mode) {
   if (mode) {
        fprintf(file, "|%8s|%8s| %-24s|%18s|%12s|%12s|%12d|\n", pid, parent, name, pState, memory, threads, opened);
    } else {
      printf("|%8s|%8s| %-24s|%18s|%12s|%12s|%12d|\n", pid, parent, name, pState, memory, threads, opened);
    }
}
void getProcessInfo(int mode) {
    direc = opendir(ROOT);
    if (direc == NULL) {
        panicf("The file cannot be read.");
        exit(-1);
    }
    FILE * current;
    char ch;
    int opened = 0;

    while ((entry = readdir(direc))) {
        int i = -1;
        int part= 0;
        int n_pid = -1;
        sscanf(entry -> d_name, "%d", & n_pid);
        if (n_pid == -1) continue;
        sprintf(path, "%s/%s/status", ROOT, entry -> d_name);
        current = fopen(path, "r");
        if (current == NULL) {
            panicf("The file cannot be read.");
            continue;
        }
        while ((ch = fgetc(current)) != EOF) {
            if (part== 0) {
                i++;
                if (ch == ':') {
                    part= 1;
                    word[i] = '\0';
                    i = -1;
                    continue;
                }
                word[i] = ch;
            } else if (part== 1) {
                part++;
            } else if (part== 2) {
                i++;

                if (ch == '\n') {
                    helper[i] = '\0';
                    if (strcmp(word, "Pid") == 0) {
                        strcpy(pid, helper);
                    } else if (strcmp(word, "PPid") == 0) {
                        strcpy(parent, helper);
                    } else if (strcmp(word, "State") == 0) {
                        strcpy(pState, helper);
                    } else if (strcmp(word, "Threads") == 0) {
                        strcpy(threads, helper);
                    } else if (strcmp(word, "Name") == 0) {
                        strcpy(name, helper);
                    } else if (strcmp(word, "VmHWM") == 0) {
                        strcpy(memory, helper);
                    }
                    i = -1;
                    part= 0;
                    continue;
                }
                helper[i] = ch;
            }
        }
        fclose(current);
        DIR * folder;
        struct dirent * fnt;
        opened = 0;
        sprintf(route, "%s/%s/fd", ROOT, entry -> d_name);
        folder = opendir(route);
        if (folder == NULL) continue;
        while ((fnt = readdir(folder))) opened++;
        (void) closedir(folder);
        printLine(opened, mode);
    }
    (void) closedir(direc);
}
void process(){
  clear();
  printf("|--------|--------|-------------------------|------------------|------------|------------|------------|\n");
  printf("| PID    | Parent | Name                    | State            | Memory     | # Threads  | Open Files |\n");
  printf("|--------|--------|-------------------------|------------------|------------|------------|------------|\n");
  getProcessInfo(0);
  printf("|--------|--------|-------------------------|------------------|------------|------------|------------|\n");
  sleep(3);
}
void signalHandler(int sig) {
    file = getSnapshot();
    direc = opendir(ROOT);
    entry = readdir(direc);
    fprintf(file, "|--------|--------|-------------------------|------------------|------------|------------|------------|\n");
    fprintf(file, "| PID    | Parent | Name                    | State            | Memory     | # Threads  | Open Files |\n");
    fprintf(file, "|--------|--------|-------------------------|------------------|------------|------------|------------|\n");
    getProcessInfo(1);
    fprintf(file, "|--------|--------|-------------------------|------------------|------------|------------|------------|\n");
    exit(-1);
    fclose(file);
}