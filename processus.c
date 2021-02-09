 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "builtin.h"
#include <sys/wait.h>
#include <errno.h>

// Nombre maximum de caractères d'une ligne
#define MAX_LINE_SIZE 1024

// Nombre maximum de mots sur une ligne
#define MAX_ARGS 512

/*
      Structure processus_t permettant de décrire les paramètres d'un
    processus lancé ou à lancer (PID, argv, stdin, stdout, stderr, status, next,
    next_succes, next_failure)

 */
typedef struct processus_t{


  pid_t pid;
  int status;
  char *argv[MAX_ARGS];
  int stdin,stdout,stderr;
  int bg;
  struct processus_t *next;
  struct processus_t *next_succes;
  struct processus_t *next_failure;

} processus_t;


/*
  Fonction exec_processus : Permet le lancement d'un processus avec les
  propriétés choisies (redirections, lancement en "arrière plan", ...)
      Paramètre proc : pointeur sur une structure décrivant le processus
      Retourne 0 en cas de succés, une autre valeur en cas d'échec
 */

int exec_processus(processus_t *proc){


  if(strcmp(proc->argv[0],"cd")==0){
    //Retourner la valeur de retour de cd
    return proc->status=cd(proc->argv[1]);
  }

  else if(strcmp(proc->argv[0],"unset")==0){

    proc->argv[1]="VAR";
    //Retourner la valeur de retour de unset
    return unset(proc->argv[1],2);

  }
  else if(strcmp(proc->argv[0],"env")==0){
    //Retourner la valeur de retour de env
    return env(1,2);
  }
  else if(strcmp(proc->argv[0],"exit")==0 ){
    //Retourner la valeur de retour de exit
    return exit_(atoi(proc->argv[1]),1,2);
  }
  else if(strcmp(proc->argv[0],getenv("PWD"))==0 ){
    //Retourner la valeur de retour de cwd
    return cwd(1,2);
  }
else{

  //Déclaration d'un variable pour Retourner le code d'erreur dans le cas d'échec de la commande
  int val=0;
  if((proc->pid == fork())!=0){

    //écrire sur la sortie standard
    if(proc->stdout > 1){
     dup2(proc->stdout,1);
      close(proc->stdout);
     close(proc->stdin);
    }

    //écrire sur l'entrée standard
    if(proc->stdin > 0){
     dup2(proc->stdin,0);
      close(proc->stdin);

    }

    //écrire sur la sortie des erreurs
    if(proc->stderr > 2){
     dup2(proc->stderr,2);
     close(proc->stderr);

    }

    //éxecuter le processus
    execvp(proc->argv[0],proc->argv);
    //Dans le cas d'échec de execvp(ne connait pas la commande entrée) affecter 1 à val
    val=1;
  }


  wait(NULL);
  //Dans le cas d'échec de execvp Retourner un erreur
  if(val==1){
      proc->status=1;

    }

}

}

