#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>

int main () {
   char str[80];
   while(1){
        scanf("%[^\n]%*c", str);
        const char s[2] = " ";
        char *token;
        /* get the first token */
        token = strtok(str, s);

        /* walk through other tokens */
        while( token != NULL ) {
            printf( " %s\n", token );
            token = strtok(NULL, s);
        }

        if(strcmp("exit", str)==0){
			exit(0);
        }  	
    }
   return(0);
}