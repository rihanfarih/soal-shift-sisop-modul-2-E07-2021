#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include <dirent.h>
#include <sys/types.h>

void download(){
}


int main(void) {
  pid_t anak_1, anak_2, anak_3, anak_4, anak_5, anak_6;
  int status;

  anak_1 = fork();
  if(anak_1 < 0){
    exit(EXIT_FAILURE);
  }

  if(anak_1==0) {
    char *argv[]={"mkdir", "-p", "Musyik", NULL};
    execv("/bin/mkdir", argv);
  }
  else {
    while((wait(&status)) > 0);
    anak_2 = fork();
  }
  if(anak_2<0) {
    exit(EXIT_FAILURE);
    }
  if(anak_2==0) {
    //sleep(5);
    char *argv[]={"mkdir", "-p", "Fylm", NULL};
    execv("/bin/mkdir", argv);
  }
  else {
    while((wait(&status))>0);
    anak_3 = fork();
  }

  if(anak_3<0){
    exit(EXIT_FAILURE);}

  if(anak_3==0) {
    char *argv[]={"mkdir", "-p", "Pyoto", NULL};
        execv("/bin/mkdir", argv);}

  else {
    while((wait(&status))>0);
        anak_4 = fork();
}
  if(anak_4<0) {
        exit(EXIT_FAILURE);
}
  if(anak_4==0) {
    char *argv[] = {"wget", "--no-check-certificate", "-q", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O", "Musik_for_Stefany.zip", NULL};
    execv("/bin/wget", argv);
    
  }

/* else {
    while((wait(&status))>0);
        anak_5 = fork();
}
  if(anak_5<0) {
        exit(EXIT_FAILURE);
}
  if(anak_5==0) {
    char *argv[] = {"wget", "--no-check-certificate", "-q", "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp-J&export=download", "-O", "Film_for_Stefany.zip", NULL};
    execv("/bin/wget", argv);
    
  }
else {
    while((wait(&status))>0);
        anak_6 = fork();
}
  if(anak_6<0) {
        exit(EXIT_FAILURE);
}
  if(anak_6==0) {
    char *argv[] = {"wget", "--no-check-certificate", "-q", "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD-J&export=download", "-O", "Foto_for_Stefany.zip", NULL};
    execv("/bin/wget", argv);
    
  }

*/
}
