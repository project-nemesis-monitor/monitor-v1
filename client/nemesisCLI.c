#include "nemesis.h"
#include<stdio.h> 
#include<stdlib.h> 

int main(int argc, char *argv[]){

  char inputString[MAXCOM], *parsedArgs[MAXLIST]; 
  char* parsedArgsPiped[MAXLIST]; 
  int execFlag = -1;
  init_shell();

  while(1){
    printDir();

    if (takeInput(inputString)){
      continue;
    }

    execFlag = processString(inputString, 
    parsedArgs, parsedArgsPiped); 

    if (execFlag == 1){
      execArgs(parsedArgs);
    }

    if (execFlag == 2){
      execArgsPiped(parsedArgs, parsedArgsPiped);
    }
  }

  return 0;
}

