#include <stdio.h>
#include<stdlib.h> 
#include <string.h> 
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>  
#include <unistd.h>

#define REPORT_FILE "report.txt"
#define NUMBER_OF_STRINGS 200
#define MAXN 50000
char *keys[NUMBER_OF_STRINGS];
char *values[NUMBER_OF_STRINGS];
char *current_line;
char *current_prefix;
char *helper;
int counter;
int start;

void analizeLog(char *logFile, char *report);
int isSameType(char* line, int zl);

int main(int argc, char **argv) {

    if (argc < 2) {
	printf("Usage:./dmesg-analizer.o logfile.txt\n");
	return 1;
    }
    //initialize size of containers for types of logs
    keys[0]=malloc(500*sizeof(char));
    current_prefix=malloc(500*sizeof(char));
    values[0]=malloc(MAXN*sizeof(char));
    current_line=malloc(MAXN*sizeof(char));
    helper = malloc(MAXN*sizeof(char));
    strcpy(current_prefix, "WWWWWWWW");
    int counter = 0;

    analizeLog(argv[1], REPORT_FILE);
    free(keys[0]);
    free(values[0]);
    free(current_line);
    free(current_prefix);
    return 0;
}

void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);

    // Implement your solution here.
    int inputFile, outputFile, sz; 
    char *c = malloc(sizeof(char)); 
    char *aux = malloc(2*sizeof(char)); 
    aux[1]='\n';
    inputFile = open("example.txt", O_RDONLY); 
    outputFile = open(report, O_WRONLY | O_CREAT, 0644 );    
    if (inputFile < 0) { 
        return; 
    } 
    
    
    strcpy(keys[0], "General: \n");
    while((sz = read(inputFile, c, 1)) > 0){
        printf("%s", c);
        strcpy(aux, c);
        strcat(current_line, aux);
        if(aux[0]=='\n'){
            strcpy(current_prefix, "hola");
            int result = isSameType(current_line, strlen(current_line));
            
            if(result == -2){
                strcat(values[0], "\t");
                strcat(values[0], current_line);
            } else if(result > 0){
                int k;
                int l = strlen(current_prefix);
                printf("la longitud del prefijo actual es %d %s\n", l, current_prefix);
                for(k=0; k<l; k++){
                    current_prefix[k]='\0';
                }
                printf("soy un nuevo tipo de log\n");
                counter++;
                //strcpy(helper, current_line);
                /*
                strncpy(keys[counter], helper+start, result);
                strcat(values[counter], "\t");
                strcat(values[counter], helper+start);
                */
                //printf("counter: %d result: %d \n", counter, result);
                
            } else if( result = -1){
                //strcpy(helper, current_line);
                /*
                strcat(values[counter], "\t");
                strcat(values[counter], helper+start);
                */
                
                
            }
            //printf("result: %d counter %d start: %d\n", result, counter, start);
            printf("counter: %d result: %d    %s xx\n", counter, result, current_prefix);
            
            strcpy(current_line, "");
        }
        //write(outputFile, c, strlen(c));
    }
    write(outputFile, keys[0], strlen(keys[0]));
    write(outputFile, values[0], strlen(values[0]));
    close(inputFile);
    close(outputFile);
    printf("Report is generated at: [%s]\n", report);
    
}

//this is a checker that compares a current prefix (type of log) within a new line
//  USE:
//      return:
//          -5  invalid log
//             same string
//          -2  general type
//          i   new prefix, i is the length 
int isSameType(char* line, int zl){
    helper = strstr(line, current_prefix);
    if(helper != NULL){
        return -1; 
    }
    int closed=0; //found first ]

    if(line[0]!='['){
        printf("Error: An invalid log is contained in the file.\n");
        return -5; //error, invalid log
    }
    //printf("lengths: %d %d \n", zc, zl);
    int i;
    for(i=1; i<zl; i++){
        if(closed ==0){
            if(line[i]==']'){
                closed=i;
                break;
            }
        }
    }
    i++;
    i++; //i has the value of the first character after the space after ]
    printf("value of i: %c\n", line[i]);


    if(line[i]==' ' || line[i]=='\t'){ //is the same
        return -1;
    }
    int j=i;
    start = i;
    for(j;j<zl; j++){
        if(j - closed  > 20 || j == zl-1){
            return -2;
        } 
        if(line[j]==':'){
            //printf("is this case\n");
            strncpy(current_prefix, current_line+i,j-i+1 );
            printf("\nThe new prefix is: %s\n", current_prefix);
            return j-i+1;
        }
    }
    
}

