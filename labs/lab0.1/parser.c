#include <stdio.h>
#include <stdlib.h>
#define MAXN 100

char opuesto(char x){
    if(x==')') return '(';
    if(x==']') return '[';
    if(x=='}') return '{';
    else return '\0';
}
 
int main(int argc, char** argv)
{
   char ch;
   FILE *fp;
 
   char* file_name = argv[1];
 
   fp = fopen(file_name, "r"); // read mode
 
   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
 
   printf("The analysis of %s is the following:\n", file_name);
   int inmulticomment=0;
   int inlinecomment=0;
   int insinglequote=0;
   int indoublequote=0;
   int line=1;
   int parenthesis[2][MAXN];
   int allgood=1;
   int ibraces;
   int ibrackets;
   int iparenthesis=-1;
   int islastslash=0;
   int islastasterisk=0;
   int lastsingle=-1;
   int lastdouble=-1;
   int numdouble=0;
   int numsingle=0;
   
   int i, j;
   for(i=0; i<2; i++){
       for(j=0; j<MAXN; j++){
           parenthesis[i][j]=0;
       }
   }
 
   while((ch = fgetc(fp)) != EOF){
       if(ch == '\n'){
           line++;
           if(inlinecomment){
               inlinecomment=0;
           }
       }
       if(ch == '(' || ch == '[' || ch == '{'){
           if(insinglequote==0 && indoublequote==0 && inlinecomment==0 && inmulticomment==0){
               iparenthesis++;
               parenthesis[0][iparenthesis]=line;
               parenthesis[1][iparenthesis]=ch;
           }
       }
       if(ch == ')' || ch == ']' || ch == '}'){
           if(insinglequote==0 && indoublequote==0 && inlinecomment==0 && inmulticomment==0){
                if(iparenthesis==-1){
                    allgood = 0;
                    printf("\n   Error, %c in line: %d\n\n", ch, line);
                } else {
                    if(parenthesis[1][iparenthesis]==opuesto(ch)){
                        iparenthesis--;
                    } else {
                        allgood = 0;
                        printf("\n   Error, %c in line: %d\n\n", ch, line); 
                        iparenthesis--;
                    }
                }
           }
       }
       if(ch =='/'){
           if(indoublequote == 0 && insinglequote == 0){
               if(inmulticomment == 0 && islastslash==1){
                   inlinecomment = 1;
               }
               if(inmulticomment == 1 && islastasterisk == 1){
                   inmulticomment = 0;
               }
           }
       }
       if(ch == '*'){
           if(indoublequote == 0 && insinglequote == 0 && inlinecomment == 0){
               if(islastslash){
                   inmulticomment = 1;
               }
           }
       }
       if(ch == '\''){
           if(inlinecomment == 1 || inmulticomment == 1 || indoublequote == 1){
               ;
           }else{ //valid single quote
               lastsingle=line;
               numsingle++;
               if(numsingle%2==0){
                   insinglequote=0;
               } else insinglequote=1;
           }
       }
       if(ch =='"'){
           if(inlinecomment == 1 || inmulticomment == 1 || insinglequote == 1){
               ;
           }else{ //valid double quote
               lastdouble=line;
               numdouble++;
               if(numdouble%2==0){
                   indoublequote=0;
               } else indoublequote=1;
           }
       }
       if(ch != '/'){
           islastslash=0;
       } else islastslash = 1;
       if(ch != '*'){
           islastasterisk=0;
       } else islastasterisk = 1;

       //printf("%c", ch);
   }
   if(iparenthesis > -1){
       allgood = 0;
       printf("\n   Error, missing ) in line: %d\n\n", parenthesis[0][iparenthesis]);
   }

   if(allgood){
       printf("\n    RESULT: \n      All good, bro!\n\n");
   }
 
   fclose(fp);
   return 0;
}