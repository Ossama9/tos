#ifndef UTILS_H
#define UTILS_H



#include <stdlib.h>


/*
  Fonction clear_tokens : Vide le tableau tokens
      Paramètre tokens : le tableau à réinitialiser
      Retourne le pointeur sur le tableau ou NULL en cas d'erreur
 */
char** clear_tokens(char* tokens[]){
  // Variable i pour boucler sur le tableau tokens
  int i=0;
  // Entrer dans la boucle tant que la case tokens[i] possède du chaîne
  while (tokens[i] != NULL) {
  // Rende la case actuelle null
    tokens[i] = NULL;
    i++;
  }
  return tokens;
}


#endif
