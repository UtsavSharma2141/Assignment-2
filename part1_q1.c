/*
   File: part1_q1.c
   Author: Utsav Sharma	
   */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

char * getportname(char * portNo)
{
   static char result[100];
   FILE *fp=fopen("/etc/services","r");
   char delims[20];

   //Change the set of characters history_tokenize uses to split a string
   fprintf(stdout,"Initial set of token delimiters: %s\n",history_word_delimiters);
   strcpy(delims,history_word_delimiters);
   strcat(delims,"/");
   history_word_delimiters=delims;

   fprintf(stdout,"Modified set of token delimiters: %s\n\n\n",history_word_delimiters);

   char line[120];
   char **tokens;
   while(fgets(line,sizeof line,fp)){
          tokens=history_tokenize(line);
          if(!tokens) continue;    //skip empty lines with no tokens

          if(tokens[0][0]=='#' ||  tokens[0][0]=='\n') continue;
		//check port number with value of tokens at index 1
          if(strcasecmp(tokens[1],portNo)==0){
				//copy value to results
                strcpy(result,tokens[0]);


           }
   }

   if(!result) return -1;

   fclose(fp);
   return result;
 }

int main(int argc, char *argv[]){

        fprintf(stdout,"The service's name of the port number is: %s\n", getportname(argv[1]));
              return 0;

}
