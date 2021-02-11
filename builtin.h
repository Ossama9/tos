#ifndef BUILTIN_H
#define BUILTIN_H




int cd(const char* path);

int export(const char* env);

int unset(const char* env, int fderr);

int env(int fdout, int fderr);

int exit_(int val, int fdout, int fderr);

int cwd(int fdout, int fderr);

#endif
