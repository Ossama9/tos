#ifndef PROCESSUS_H
#define PROCESSUS_H

#define MAX_LINE_SIZE 1024
#define MAX_ARGS 512

/*
    Structure processus_t permettant de décrire les paramètres d'un
    processus lancé ou à lancer (PID, argv, stdin, stdout, stderr, status, next,
    next_succes, next_failure)
 */
typedef struct processus_t {

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
int exec_processus(processus_t* proc);

/*
 Fonction status_processus :  récupérer le status d'un processus (en cours,
                              terminé, ...)
      Paramètre proc : pointeur sur une structure décrivant le processus
      Retourne le "status" d'un processus lancé en arrière plan
 */
int status_processus(processus_t* proc);

#endif
