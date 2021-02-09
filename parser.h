#ifndef PARSER_H
#define PARSER_H


// Nombre maximum de caractères d'une ligne
#define MAX_LINE_SIZE 1024
// Nombre maximum de mots sur une ligne
#define MAX_ARGS       512

/*
  Fonction trim_str : Supprime les caractères d'espacement (' ' et '\t') au
                      début et à la fin de la chaîne
      Paramètre str : la chaîne à modifier
      Retourne 0 en cas de succés, une autre valeur en cas d'échec
 */
int trim_str(char* str);

/*
  Fonction clean_str :  Supprime les doublons de caractères d'espacement (' '
                        et '\t') à l'intérieur de la chaîne
      Paramètre str : la chaîne à modifier
      Retourne 0 en cas de succés, une autre valeur en cas d'échec
 */
int clean_str(char* str);

/*
  Fonction tokenize_str : Découpe la ligne sur les caractères d'espacement
                          (' ' et '\t') et enregistre les pointeurs sur le
                          début de chaque mot dans tokens (NULL-terminated)
      Paramètre str : la chaîne à découper
      Paramètre tokens : le tableau dans lequel stocker les éléments de str
      Retourne le nombre de chaînes dans tokens
 */
int tokenize_str(char* str, char* tokens[]);

/*
  Fonction env_str :  Remplace les noms des variables d'environnement par
                      leur contenu dans tokens (terminé par NULL)
      Paramètre tokens : le tableau dans lequel les substitutions sont faites
      Retourne 0 en cas de succés, une autre valeur en cas d'échec
 */
int env_str(char* tokens[]);



#endif
