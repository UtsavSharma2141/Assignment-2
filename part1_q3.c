/*
   File: part1_q1.c
   Author: Utsav Sharma	
   */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h> 
#include <readline/readline.h>
#include <readline/history.h> 
#include <stdbool.h> 
#include <signal.h> 
#include <string.h> 
#include <time.h> 
#include <sys/socket.h>
#include <linux/un.h> 
#include <math.h>

void ctrlCHandler(int signum)
{
  fprintf(stderr,"Command server terminated using <ctrl>C\n");  
  exit(1); 
  } 

char *safecat(char * dest, char *src, int maxSize) 
{
  return strncat(dest,src,maxSize-strlen(dest)-1);  
  } 
  
char * getportname(char * portNo);
int getportnum(char * portName);


struct CMDSTRUCT
{
   char *cmd;
   char *(*method)();
   char *port;
}
cmdStruct[]={{"port",getportname,"port:\n"},
				{"service",getportnum,"service:\n"},
                              {NULL,NULL,NULL}};
 
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

char *interpret(char *cmdline)
{
  char **tokens;
  char *cmd;
  int  i; 
  char *result; 

  tokens=history_tokenize(cmdline);   //Split cmdline into individual words.  
  if(!tokens) return "no response needed"; 
  cmd=tokens[0]; 


  for(i=0;cmdStruct[i].cmd;i++)
    if(strcasecmp(cmd,cmdStruct[i].cmd)==0) return (cmdStruct[i].method)(cmd,&tokens[1],cmdline);    
  
 
  return "command not found"; 

 } 
int main(int argc, char * argv[],char * envp[])
{
  char cmd[100]; 
  char *cmdLine; 
  int  nBytes; //size of msg rec'd

  signal(SIGINT,ctrlCHandler); 
 

  fprintf(stdout,"Enter port command\n"); 
  while(true) {

          cmdLine=readline("Enter a command: ");   
          if(!cmdLine) break; 
          char *response=interpret(cmdLine); 
          fprintf(stdout,"%s\n",response);
fprintf(stdout,"The service's name corresponding to the port number is: %s\n", getportname(envp[1]));

  fprintf(stdout,"Server is now terminated \n"); 
  return 0;
  }

}