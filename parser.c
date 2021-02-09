

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Nombre maximum de caractères d'une ligne
#define MAX_LINE_SIZE 1024

// Nombre maximum de mots sur une ligne
#define MAX_ARGS 512

// les variables d'environnemnt
extern char **environ;

// Chaine de caractères pour l'utiliser dans les fonctions
char  *chaine=NULL;

/*
  Fonction trim_str : Supprime les caractères d'espacement (' ' et '\t') au
                      début et à la fin de la chaîne
      Paramètre str : la chaîne c modifier
      Retourne 0 en cas de succés, une autre valeur en cas d'échec
 */
int trim_str(char *str){

  int dep=0;
  int fin=0;
  int len=0;

  /*
    Fonction get_espace : Récupérer l'espace dans une chaine de caractères
        Paramètre s : le caractère
        Retourne l'espace
   */
    int get_espace(char s) {
          return (s == ' ' || s == '\t');
      }

      // Récupérer l'indice de départ de la chaine sans espaces
    while (get_espace(str[dep])) {
        dep += 1;
    }

    // Récupérer la longueur de la chaine
    while (str[len] != '\0') {
        len = len + 1;
    }

    // Récupérer l'indice de fin de la chaine sans espaces
     fin = len - 1;
    while (get_espace(str[fin-1])) {

        fin = fin-1;
    }

        int i = 0;
        int j=dep;
        len = (fin - dep);
        chaine = (char *)malloc(len);

      // Récupérer  la chaine sans espaces au debut et à la fin
        while (i < len) {
            chaine[i] = str[j];
            i += 1;
            j += 1;
        }
        chaine[i] = '\0';

        strcpy(str,chaine);

  if(chaine){

    return 0;
  }else{
    return 1;
  }


}


/*
  Fonction clean_str :  Supprime les doublons de caractères d'espacement (' '
                        et '\t') à l'intérieur de la chaîne
      Paramètre str : la chaîne à modifier
      Retourne 0 en cas de succés, une autre valeur en cas d'échec
 */
int clean_str(char *str){
  int i=0;
  int j=0;

  //chaine de caractères temporaire pour stocker la chaine sans double espacement
  char *chaine1=NULL;
  chaine1 = (char *)malloc(MAX_ARGS);

  i=0;
  j=0;

  //Enlever les doubles espaces dans la chaine
  while(str[i] != '\0'){

      if( (str[i] == ' ' || str[i] == '\t') &&
      (str[i+1] == ' ' || str[i+1] == '\t')){

      chaine1[j]=str[i];
  }else{
    chaine1[j]=str[i];
    j++;
  }
  i++;

}

  strcpy(str,chaine1);
  if(str){

    return 0;
  }else{
    return 1;
  }
}


/*
  Fonction tokenize_str : Découpe la ligne sur les caractères d'espacement
                          (' ' et '\t') et enregistre les pointeurs sur le
                          début de chaque mot dans tokens (NULL-terminated)
      Paramètre str : la chaîne à découper
      Paramètre tokens : le tableau dans lequel stocker les éléments de str
      Retourne le nombre de chaînes dans tokens
 */

int tokenize_str(char *str,char *tokens[]){

  //nombre de chaînes dans tokens
  int pos=0;

      //chaine de caractères temporaire pour la stocker dans le tableau tokens
     char *chaine1=NULL;

     //couper la chaine par espace
    chaine1=strtok(str," ");
    while(chaine1 != NULL){
      tokens[pos]=chaine1;
      chaine1=strtok(NULL," ");
      pos++;
    }
    tokens[pos]=NULL;

    //Retourner le nombre de chaînes dans tokens
    return pos;

}


/*
  Fonction env_str :  Remplace les noms des variables d'environnement par
                      leur contenu dans tokens (terminé par NULL)
      Paramètre tokens : le tableau dans lequel les substitutions sont faites
      Retourne 0 en cas de succés, une autre valeur en cas d'échec
 */
int env_str(char *tokens[]){

  int l=0;
  int i=0;

  //chaine de caractères temporaire pour l'utiliser à récupérer les variables d'environnemnts
  char *chaine1=NULL;
  chaine1 = (char *)malloc(MAX_ARGS);

    while(tokens[l] != NULL){
      chaine1 = (char *)malloc(MAX_ARGS);

    while(tokens[l][i] != '\0'){

      chaine1[i]=toupper(tokens[l][i]);
      i++;
    }
      //remplacer le nom de variable d'environnemnt par son contenu
       char *val=getenv(chaine1);
       if(val != NULL){
         
         //stocker le variable d'environnemnt dans le tableau de tokens
         tokens[l]=val;
}
  char *chaine1=NULL;
  i=0;
  l++;
  }


if(tokens){

  return 0;
}else{
  return 1;
}
}
