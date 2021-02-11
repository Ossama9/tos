#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "processus.h"
#include "utils.h"


// Nombre maximum de caractères d'une ligne
#define MAX_LINE_SIZE 1024

// Nombre maximum de mots sur une ligne
#define MAX_ARGS 512

//Déclaration de processus
processus_t proc[MAX_ARGS];


/*
  Fonction init_process : Crée l'enchaînement de processus à partir du
                          tableau tokens
      Paramètre proc : pointeur sur la structure à remplir
      Paramètre tokens :  tableau (NULL-terminated) contenant les chaînes
                          de la ligne de commande à analyser
      Retourne 0 en cas de succés et une autre valeur en cas d'échec
 */

int init_process(processus_t *proc,char *tokens[]){

  for(int i=0;i<MAX_ARGS;i++){
      //Remplir les champs de processus
      proc[i].stdin=0;
      proc[i].stdout=1;
      proc[i].stderr=2;
      proc[i].bg=0;
      //Vider le tableau des arguments
      clear_tokens(proc[i].argv);
      proc[i].next=NULL;
      proc[i].next_succes=NULL;
      proc[i].next_failure=NULL;
}

      //Index de processus
      int proc_id=0;

      //Index de l'argument de processus
      int argv_id=0;

      //Index de tokens
       int i=0;

       //Parcourir le tableau de tokens
      while(tokens[i] != NULL){

        //Vérifier si la commande contient "<"
        if(strcmp(tokens[i],"<")==0){

          //Ouvrir un fichier en mode lecture et le rediriger vers l'entrée standard
          int fd=open(tokens[i+1],O_RDONLY);
          proc[proc_id].stdin=fd;
          ++i;++i;
          continue;

        }

        //Vérifier si la commande contient "|"
        if(strcmp(tokens[i],"|")==0){

        proc[proc_id].bg=1;
        int fd[2];
        pipe(fd);
        proc[proc_id].stdout=fd[1];
        proc[proc_id+1].stdin=fd[0];
        proc[proc_id].next=&proc[proc_id+1];
        ++proc_id;
        argv_id=0;
        ++i;
        continue;
        }

        //Vérifier si la commande contient ">"
        if(strcmp(tokens[i],">")==0){

        /*  Ouvrir un fichier en mode lecture et écriture et le rediriger vers
           la sortie standard
           */
          proc[proc_id].stdout=open(tokens[i+1],O_WRONLY | O_CREAT , 0777 | O_TRUNC );
          ++i;++i;
          continue;
        }

        //Vérifier si la commande contient ">>"
        if(strcmp(tokens[i],">>")==0){
          /*  Ouvrir un fichier en mode lecture et écriture et le rediriger vers
             la sortie standard.
             Si le fichier est déjà crée et il contient des éléments, la fonction
             ajoute les nouveaux éléments vers la fin.
             */
          proc[proc_id].stdout=open(tokens[i+1],O_WRONLY | O_CREAT , 0777 | O_APPEND );
          ++i;++i;
          continue;
        }
        //Vérifier si la commande contient "2>"
        if(strcmp(tokens[i],"2>")==0){
          /*  Ouvrir un fichier en mode lecture et écriture et le rediriger vers
             la sortie des erreurs.
             */
          proc[proc_id].stderr=open(tokens[i+1],O_WRONLY | O_CREAT , 0777 | O_TRUNC);
          ++i;++i;
          continue;
        }

        //Vérifier si la commande contient "2>>"
        if(strcmp(tokens[i],"2>>")==0){
          /*  Ouvrir un fichier en mode lecture et écriture et le rediriger vers
             la sortie des erreurs.
             Si le fichier est déjà crée et il contient des éléments, la fonction
             ajoute les nouveaux éléments vers la fin.
             */
          proc[proc_id].stderr=open(tokens[i+1],O_WRONLY | O_CREAT , 0777 | O_APPEND);
          ++i;++i;
          continue;
        }
        //Vérifier si la commande contient "&"
        if(strcmp(tokens[i],"&")==0){
          //affecter 1 à bg pour l'Exécuter en arrière plan
           proc[proc_id].bg=1;
           ++i;
           continue;

        }
        //Vérifier si la commande contient "&&"
        if(strcmp(tokens[i],"&&")==0){
          proc[proc_id].next_succes=&proc[proc_id+1];
          argv_id=0;
          ++proc_id;
          ++i;
          continue;
        }

        //Vérifier si la commande contient "||"
        if(strcmp(tokens[i],"||")==0){
          proc[proc_id].next_failure=&proc[proc_id+1];
          argv_id=0;
          ++proc_id;
          ++i;
          continue;
        }

        //Vérifier si la commande contient ";"
        if(strcmp(tokens[i],";")==0){
          proc[proc_id].next=&proc[proc_id+1];

          argv_id=0;
          ++proc_id;
          ++i;
          continue;
        }

        proc[proc_id].argv[argv_id]=tokens[i];
        ++argv_id;
        ++i;

  }
      proc = NULL;
      return 0;
}

/*
  Fonction exec_cmdline : Lance les processus de la ligne de commande dans
                          l'ordre attendu en respect des conditions demandées
      Paramètre proc : la structure décrivant les processus à lancer
      Retroune 0 en cas de succés et une autre valeur en cas d'échec
 */
int exec_cmdline(processus_t *proc){

//Créer l'enchaînement des processus
  while(proc != NULL){

    //Exécuter un processus
    exec_processus(proc);

    //Gérer les valeurs des retours pour les erreurs
    if(proc->status!=0 && proc->status!=1){
      printf("Commande échouée : %s\n",strerror(WEXITSTATUS(proc->status)) );
    }else if(proc->status==1){
      printf("Commande échouée : %s\n",strerror(proc->status));
    }

    //Gestion des opérateurs comme le bash

    //Pour l'opérateur ";"
    if(proc->next != NULL){
      proc = proc->next;
      continue;
    }
    //Pour l'opérateur "&&"
    if(proc->next_succes != NULL){
      if(WEXITSTATUS(proc->status)==0){
        proc = proc->next_succes;
        continue;
      }else{
        proc =NULL;
      }
    }
    //Pour l'opérateur "||"
    if(proc->next_failure != NULL){
      if(WEXITSTATUS(proc->status) != 0){
        proc = proc->next_failure;
        continue;
      }else{
        proc =NULL;
      }
    }

    proc=NULL;

  }
}
