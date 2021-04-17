#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
#include <dirent.h>
#include <time.h>

void unduh(){

pid_t anak_a, anak_b, anak_c;
int status;

anak_a = fork();
  if(anak_a < 0){
    exit(EXIT_FAILURE);
  }
if(anak_a==0) {
    char *argv[] = {"wget", "--no-check-certificate", "-q", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O", "Musik_for_Stefany.zip", NULL};
    execv("/bin/wget", argv); }

 
else {
    while((wait(&status))>0);
        anak_b= fork();
}
  if(anak_b<0) {
        exit(EXIT_FAILURE);
}
  if(anak_b==0) {
    char *argv[] = {"wget", "--no-check-certificate", "-q", "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-O", "Film_for_Stefany.zip", NULL};
    execv("/bin/wget", argv); }
 else {
    while((wait(&status))>0);
        anak_c= fork();
}
  if(anak_c<0) {
        exit(EXIT_FAILURE);
}
  if(anak_c==0) {
    char *argv[] = {"wget", "--no-check-certificate", "-q", "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O", "Foto_for_Stefany.zip", NULL};
    execv("/bin/wget", argv); }
}

int main() {

pid_t anak_1, anak_2, anak_3, anak_4, anak_5, anak_6;
        int status;


        anak_1 = fork();
        if(anak_1 < 0){
            exit(EXIT_FAILURE);}

        if(anak_1==0) {
            char *argv[]={"mkdir", "-p", "Musyik", "Fylm", "Pyoto", NULL};
            execv("/bin/mkdir", argv);}
        else {
            while((wait(&status)) > 0);
            anak_2 = fork();
                }
        if(anak_2<0) {
            exit(EXIT_FAILURE);
            }
        if(anak_2==0) {
            unduh();}
}
