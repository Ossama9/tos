

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "cmdline.h"

// Nombre maximum de caractères d'une ligne
#define MAX_LINE_SIZE 1024

// Nombre maximum de mots sur une ligne
#define MAX_ARGS 512
char *prompt (void)
{
   char *invite = NULL;
   char const *user = getenv("USERNAME");

   if (user == NULL)
   {
      user = getenv("USER");

      if (user == NULL)
      {
         user = "";
      }

   }

   {
      char const *host = getenv("HOSTNAME");

      if (host == NULL)
      {
         host = "";
      }

      {
         char const *aux = getenv("PWD");

         if (aux == NULL)
         {
            aux = "";
         }
         {
            char const *rep = aux + strlen(aux);

            while (rep >= aux && *rep != '/')
            {
               rep--;
            }

            rep++;

            invite = malloc(strlen(user) + strlen(host) + strlen(rep) + 6);

            if (invite != NULL)
            {
               strcpy(invite, "[");
               strcat(invite, user);
               strcat(invite, "@");
               strcat(invite, host);
               strcat(invite, " ");
               strcat(invite, rep);
               strcat(invite, "]");
               strcat(invite, "$");
               strcat(invite, " ");
            }

         }

      }
   }
   return invite;
}
int main(int argc, char *argv[],char *envp[]){

// Chaine de caractères à entrér
char static *str=NULL;
char *s = prompt();


// tableau des tokens
char *tab[MAX_ARGS]={NULL};


printf("---------------Welcome to MiniShell---------------\n");
while(!feof(stdin)){

  //Affichage Prompt 
  printf ("%s:", s);
  char *str=(char *)malloc(MAX_ARGS);

  //Récupérer la chaine

  fgets(str,MAX_LINE_SIZE,stdin);
  printf("\n");

  //Enlever les espaces de départ et de la fin
  trim_str(str);

  //Enlever les doubles espaces à l'intérieur de la chaîne
  clean_str(str);

  //Découper la chaine
  int nbr=tokenize_str(str,tab);

  //Remplace les noms des variables d'environnement par leur contenu
  env_str(tab);

  //Déclaration de processus
  processus_t *proc=NULL;

  proc = (processus_t *)malloc(sizeof(processus_t)*1024);

  //Initialiser les processus
  init_process(proc,tab);

  //Exécuter l'enchaînement des processus
  exec_cmdline(proc);
}

return 0;

}
