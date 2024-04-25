#include "nemesis.h"
#include<readline/readline.h> 
#include<readline/history.h> 

void init_shell(){

  clear(); 
    printf("\n\n\n\n******************"
        "************************"
        "**************************\n\n");
    printf("\n\t\t⠀⠀⠀⠀⠀⠀⠀⠀ ⢀⣀⣤⣤⣤⣤⣴⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
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
        "\n ! Careful, some printed results are in french !\n"
        "\nList of Commands supported:"
        "\n>cd: change directory"
        "\n>lperm: list entity permissions"
        "\n>chperm: change entity permissions"
        "\n>exit: quitting the tool"
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
  ListOfOwnCmds[3] = "lperm";
  ListOfOwnCmds[4] = "chperm";


  for(i = 0; i < NumOfOwnCmds; i++){
    if(strcmp(parsed[0], ListOfOwnCmds[i]) == 0){
      switchOwnArg = i + 1;
      break;
    }
  }

  switch(switchOwnArg){
    case 1:
      printf("\nGoodbye\n");
      sleep(1);
      clear();
      exit(0);

    case 2:
      chdir(parsed[1]);
      return 1;

    case 3:
      openHelp();
      return 1;

    case 4:
      printf("\n! Fonction à implémenter !\n\n");
      printf("Modèle:\n\n");
      printf("Dossier parent : Documents\n Fichier : toto.txt\n Nom Propriétaire : dupond\n"
      "Droits Propriétaire : Lecture, Ecriture, Exécution\n Droits Groupe : Lecture, Exécution\n" 
      "Droits autres : Exécution\n Chemin aboslu : /home/dupond/Documents");

      return 0;

    case 5:
      printf("\n! Fonction à implémenter !\n\n");
      printf("Modèle:\n\n");
      printf("Choisissez les droits pour le propriétaire:\n\n");
      printf("[1] Lecture\n[2] Ecriture\n[3] Execution\n[4] SUID\n[5] Lecture Ecriture\n"
      "[6] Ecriture Execution\n[7] Lecture Execution\n[8] Tous les droits\n[9] Aucun droit\n[10] Pas de choix");
      printf("\n\nVotre choix: <choix des droits>\n\n");
      printf("Idem pour le groupe et les autres utilisateurs.");

      return 0;

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