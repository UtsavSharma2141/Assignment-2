/*
   File: part1_q2.c
   Author: Utsav Sharma	
   */
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

int getportnum(char * portName)
{
   static char result[100];
   int final = 0;
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

          for(int i=0;tokens[i];i++){
          if(strcasecmp(portName,tokens[i])==0){

                strcpy(result,tokens[1]);
                final = atoi(result);
          }}
   }

   if(!result) return -1;

   fclose(fp);
   return final;
 }

int main(int argc, char *argv[]){

        fprintf(stdout,"The service's port number corresponding to the name is: %d\n", getportnum(argv[1]));
              return 0;

}
