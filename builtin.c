#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include <errno.h>

#define MAX_LINE_SIZE 1024
#define MAX_ARGS 512

/*
  Fonction cd : Changer le répértoire courant
      Paramètre path : le répértoire à accéder
      Retourne 0 en cas de succés, une autre valeur(1) en cas d'échec
 */
int cd(const char *path){

    //La fonction chdir pour accéder à un chemain donnée en paramètre(Path)
int  r=chdir(path);
  if(r==0){
    char dir[MAX_ARGS];

    // Récupérer le chemain et l'afficher
    getcwd(dir,sizeof(dir));
    printf("Directory is changed : %s\n",dir );
    return 0;
  }else{
    return 1;
  }

}

/*
  Fonction export : Permet de propager une variable "au dela" du programme ou
              du terminal dans laquelle elle a été créé
      Paramètre env : variable d'environnemnt
      Retourne 0 en cas de succés, une autre valeur en cas d'échec
 */
int export(const char *env){

  //Déclaration d'un variable VAR
 const char *var= "VAR";

 //affecter Var par le contenu d'un variable d'environnemnt(env)
 if(setenv(var,env,1)==0){

   //Affichage comme titre d'information
   printf("VAR = %s\n",getenv(var));
   return 0;
 }else{
return 1;
}
}



/*
  Fonction unset : Permet d'éffecer la mémoire d'une variable passée en paramètre
      Paramètre env : variable d'environnemnt laquelle on va supprimer sa mémoire
      Paramètre fderr : Sortie des erreurs
      Retourne 0 en cas de succés, une autre valeur(1) en cas d'échec
 */
int unset(const char *env,int fderr){

  //Récupérer le contenu de variable VAR
  if(getenv("VAR") != NULL){
    //éffecer la mémoire de variable
    unsetenv(env);
    return 0;
  }else{
    write(fderr,"variable undefined\n",strlen("variable undefined\n"));
    return 1;
  }

}

/*
  Fonction env : Permet d'afficher les variables d'environnemnts
      Paramètre fdout : la sortie standard
      Paramètre fderr : la Sortie des erreurs
      Retourne 0 en cas de succés, une autre valeur(1) en cas d'échec
 */
int env(int fdout,int fderr){

    extern char **environ;
          printf("\n");
    for(int i=0;environ[i];++i){
      printf("\n");
    int  w=write(fdout,environ[i],strlen(environ[i])*sizeof(*environ[i]));

    if(w<0){
      write(fderr,"Erreur au niveau de la recuperation des variables d'environnemnt\n",strlen("Erreur au niveau de la recuperation des variables d'environnemnt\n"));
      printf("\n");
      return 1;
    }

    }
    printf("\n");
return 0;
}


/*
  Fonction exit_ : Permet de quitter la shell
      Paramètre val : le code de exit (1 en cas de succes)
      Paramètre fdout : la sortie standard
      Paramètre fderr : la Sortie des erreurs
      Retourne 0 en cas de succés, une autre valeur(1) en cas d'échec
 */
int exit_(int val,int fdout,int fderr){

int pid=getppid();

if(val == 1){
  kill(pid,9);
  return 0;
}else{

  write(fderr,"USAGE : exit 1\n",strlen("USAGE : exit 1\n"));
  return 1;
}
}


/*
  Fonction cwd : Permet d'afficher le répértoire courant
      Paramètre fdout : la sortie standard
      Paramètre fderr : la Sortie des erreurs
      Retourne 0 en cas de succés, une autre valeur(1) en cas d'échec
 */
int cwd(int fdout,int fderr){


if(system("pwd")==0){
    return 0;
}else{
write(fderr,"Operation undefined",strlen("Operation undefined"));
return 1;
}
 }
