#include <stdio.h>
#include <stdlib.h>

int mystrlen(char *str){
    int l=0;
    while(str[l] !='\0'){
        l++;
    }
    return l;
}

char *stradd(char *origin, char *addition){
      char* ptr = origin+mystrlen(origin);
      while (*addition != '\0')
		*ptr++ = *addition++;
	*ptr = '\0';
	return origin;
}

int mystrfind(char *origin, char *substr){
      int l1=mystrlen(origin), l2=mystrlen(substr);
      //printf("a comparar %s %s\n", origin, substr);
      if(l1 < l2)
            return 0;
      int i=0, j=0;
      for(i=0; i<l1; i++){
            for(j=0; i+j<l1 && j<l2; j++){
                  if(origin[i+j]!=substr[j])
                        break;
                  if(j == l2-1)
                        return 1;
            }
      }
      return 0;
}
