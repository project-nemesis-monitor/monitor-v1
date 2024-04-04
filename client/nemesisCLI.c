#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 

#define MAXCOM 1000 // max number of letters to be supported 
#define MAXLIST 100 // max number of commands to be supported 

// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")

//function to greet user during startup
void init_shell();

// Function to take input
int takeInput(char* str);

// Function to print Current Directory.
void printDir();

// Function where the system command is executed
void execArgs(char** parsed);

// Function where the piped system commands is executed
void execArgsPiped(char** parsed, char** parsedpipe);

// Help command builtin
void openHelp();

// Function to execute builtin commands 
int ownCmdHandler(char** parsed);

// function for finding pipe 
int parsePipe(char* str, char** strpiped);

// function for parsing command words 
void parseSpace(char* str, char** parsed);
int processString(char* str, char** parsed, char** parsedpipe);

int main(int argc, char *argv[]){

  char inputString[MAXCOM], *parsedArgs[MAXLIST]; 
  char* parsedArgsPiped[MAXLIST]; 
  int execFlag = 0;
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

void init_shell(){

  clear(); 
    printf("\n\n\n\n******************"
        "************************"
        "**************************\n\n");
    printf("\n\t\t⠀⠀⠀⠀⠀⠀⠀⠀  ⢀⣀⣤⣤⣤⣤⣴⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("\t\t⠀⠀⠀⠀⠀⠀⠀⣀⣴⣾⠿⠛⠋⠉⠁⠀⠀⠀⠈⠙⠻⢷⣦⡀⠀⠀⠀⠀⠀⠀\n");
    printf("\t\t⠀⠀⠀⠀⠀⣤⣾⡿⠋⠁⠀⣠⣶⣿⡿⢿⣷⣦⡀⠀⠀⠀⠙⠿⣦⣀⠀⠀⠀⠀\n");
    printf("\t\t⠀⠀⢀⣴⣿⡿⠋⠀⠀⢀⣼⣿⣿⣿⣶⣿⣾⣽⣿⡆⠀⠀⠀⠀⢻⣿⣷⣶⣄⠀\n");
    printf("\t\t⠀⣴⣿⣿⠋⠀⠀⠀⠀⠸⣿⣿⣿⣿⣯⣿⣿⣿⣿⣿⠀⠀⠀⠐⡄⡌⢻⣿⣿⡷\n");
    printf("\t\t⢸⣿⣿⠃⢂⡋⠄⠀⠀⠀⢿⣿⣿⣿⣿⣿⣯⣿⣿⠏⠀⠀⠀⠀⢦⣷⣿⠿⠛⠁\n");
    printf("\t\t⠀⠙⠿⢾⣤⡈⠙⠂⢤⢀⠀⠙⠿⢿⣿⣿⡿⠟⠁⠀⣀⣀⣤⣶⠟⠋⠁⠀⠀⠀\n");
    printf("\t\t⠀⠀⠀⠀⠈⠙⠿⣾⣠⣆⣅⣀⣠⣄⣤⣴⣶⣾⣽⢿⠿⠟⠋⠀⠀⠀⠀⠀⠀⠀\n");
    printf("\t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⠛⠛⠙⠋⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\n\n\n");

    printf("\t███    ██ ███████ ███    ███ ███████ ███████ ██ ███████ \n");
    printf("\t████   ██ ██      ████  ████ ██      ██      ██ ██      \n");
    printf("\t██ ██  ██ █████   ██ ████ ██ █████   ███████ ██ ███████ \n");
    printf("\t██  ██ ██ ██      ██  ██  ██ ██           ██ ██      ██ \n");
    printf("\t██   ████ ███████ ██      ██ ███████ ███████ ██ ███████ \n");
    
    printf("\n\t\t-HOW ABOUT CHECKING FILE PROPERTIES ?-"); 
    printf("\n\t\t-v1.0 Nemesis Group-"); 
    printf("\n\n\n\n*******************"
        "***********************"
        "*************************"); 
    char* username = getenv("USER"); 
    printf("\n\n\nUSER is: @%s", username); 
    printf("\n"); 
    sleep(3); 
    //clear();
}

int takeInput(char* str){

  char* buf;

  buf = readline("fsmonitor>>> ");
  if (strlen(buf) != 0){
    add_history(buf);
    strcpy(str, buf);
    return 0;
  } else {
    return 1;
  }
}

void printDir(){
  char cwd[1024]; 
  getcwd(cwd, sizeof(cwd)); 
  printf("\nDir: %s | ", cwd);
}

void execArgs(char** parsed){
  pid_t pid = fork();

  if (pid == -1){
    printf("Failed forking child..");
    return;
  } else if (pid == 0){
    if (execvp(parsed[0], parsed)){
      printf("\nCould not execute command..");
    }
    exit(0);
  } else {
    wait(NULL);
    return;
  }

  return;
}

void execArgsPiped(char** parsed, char** parsedpipe){
  int pipefd[2];
  pid_t p1, p2;

  if(pipe(pipefd) < 0){
     printf("\nPipe could not be initialized"); 
     return; 
    if(p1 == 0){
      close(pipefd[0]);
      dup2(pipefd[1], STDOUT_FILENO);
      close(pipefd[1]);
    }
  } else {
    p2 = fork(); 
  
    if (p2 < 0) { 
        printf("\nCould not fork"); 
        return; 
    } 

    if(p2 == 0){
      close(pipefd[1]); 
      dup2(pipefd[0], STDIN_FILENO); 
      close(pipefd[0]);

      if(execvp(parsedpipe[0], parsedpipe) < 0){
        printf("\nCould not execute command 2..");
        exit(0);
      }
    } else {
      wait(NULL); 
      wait(NULL);
    }
  }
}

void openHelp(){
   puts("\n***WELCOME TO THE FILE SYSTEM MONITORING TOOL***"
        "\nCopyright @ Wing-builder"
        "\n- The tool is used for those who the file properties are the sinews of war..."
        "\nList of Commands supported:"
        "\n>cd"
        "\n>ls"
        "\n>exit"
        "\n>all other general commands available in UNIX shell"
        "\n>pipe handling"
        "\n>improper space handling"); 

  return; 
}

int ownCmdHandler(char** parsed){
  int NumOfOwnCmds = 5, i, switchOwnArg = 0;
  char* ListOfOwnCmds[NumOfOwnCmds];
  char* username;

  ListOfOwnCmds[0] = "exit"; 
  ListOfOwnCmds[1] = "cd"; 
  ListOfOwnCmds[2] = "help"; 
  ListOfOwnCmds[3] = "hello";
  ListOfOwnCmds[4] = "king";

  for(i = 0; i < NumOfOwnCmds; i++){
    if(strcmp(parsed[0], ListOfOwnCmds[i]) == 0){
      switchOwnArg = i + 1;
      break;
    }
  }

  switch(switchOwnArg){
    case 1:
      printf("\nGoodbye\n");
      exit(0);

    case 2:
      chdir(parsed[1]);
      return 1;

    case 3:
      openHelp();
      return 1;

    case 4:
      username = getenv("USER");
      printf("Hello %s.\nJust say you know "
        "don't mess up with this thing."
        "\nUse help to learn how to handle it..\n", 
        username);
      return 1;

    case 5:
      printf("Yes you're a king\n"
            "But don't get cocky");
      return 1;

    default:
      break;
  }

  return 0;
}

int parsePipe(char* str, char** strpiped) {
  int i;
  for (i = 0; i < 2; i++){
    strpiped[i] = strsep(&str, "|");
    if(strpiped[i] == NULL){
      return 0;
    } else {
      return 1;
    }
  }
}

void parseSpace(char* str, char** parsed){
  int i;

  for(i = 0; i < MAXLIST; i++){
    parsed[i] = strsep(&str, " ");

    if(parsed[i] == NULL){
      break;
    }

    if(strlen(parsed[i]) == 0){
      i--;
    }
  }
}

int processString(char* str, char** parsed, char** parsedpipe){
  char* strpiped[2];
  int piped = 0;

  piped = parsePipe(str, strpiped);

  if(piped){
    parseSpace(strpiped[0], parsed);
    parseSpace(strpiped[1], parsedpipe);
  } else {
    parseSpace(str, parsed);
  }

  if(ownCmdHandler(parsed)){
    return 0;
  } else {
    return 1 + piped;
  }
}

