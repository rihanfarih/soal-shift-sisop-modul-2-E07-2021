#include <sys/types.h>
#include <wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

char *link_stevanny[] = {"https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download",
                        "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download",
                        "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"};
char *folder_stevanny[] = {"Pyoto", "Musyik", "Fylm"};
char *zip_stevanny[] = {"Foto_for_Stefany.zip", "Musik_for_Stevany.zip", "Film_for_Stevany.zip"};
char *extract_stevanny[] = {"FOTO", "MUSIK", "FILM"};

char dir_now[] = "/home/sfayha/sisop/modul2/";

// 1a create folders
void createF(int ind) {
    pid_t child_id;
    int status;

    child_id = fork();
    if(child_id == 0) {
        char *argv[] = {"mkdir", folder_stevanny[ind], NULL};
        execv("/usr/bin/mkdir", argv);
    }
    while(wait(&status) > 0); // ini buat kalo dia udah selese ngejalanin fungsi diatas, fungsi selanjutnya bisa jalan
}

// 1b download files
void downloadF(int ind) {
    pid_t child_id;
    int status;

    child_id = fork();
    if(child_id == 0) {
        char *argv[] = {"wget", "--no-check-certificate", "-q", link_stevanny[ind], "-O", zip_stevanny[ind], NULL};
        execv("/usr/bin/wget", argv);
    }
    while(wait(&status) > 0);
}

// 1c extract zip downloads
void extractF(int ind) {
    pid_t child_id;
    int status;

    child_id = fork();
    if(child_id == 0) {
        char *argv[] = {"unzip", "-q", zip_stevanny[ind], NULL};
        execv("/usr/bin/unzip", argv);
    }
    while(wait(&status) > 0);
}

 // 1f delete the extract folders
void removenExtract(int ind) {
    pid_t child_id;
    int status;

    child_id = fork();
    if(child_id  == 0) {
        char *argv[] = {"rm", "-d", extract_stevanny[ind], NULL};
        execv("/usr/bin/rm", argv);
    }
    while(wait(&status) > 0);
}

// 1f zip folders and delete the folders
void zipStev(int ind) {
    pid_t child_id;
    int status;

    child_id  = fork();
    if(child_id  == 0) {
        char *argv[] = {"zip", "-q", "-r", "-m", "Lopyu_Stevanny.zip", folder_stevanny[ind], NULL};
        execv("/usr/bin/zip", argv);
    }
    while(wait(&status) > 0);
}

// 1d move all the files from the extract folder to the destination folder
void moveF(int ind) {
    pid_t child_id;
    int status;

    char expath[]="/home/sfayha/sisop/modul2/";
    char stpath[]="/home/sfayha/sisop/modul2/";

 
    strcat(expath, extract_stevanny[ind]);
    strcat(stpath, folder_stevanny[ind]);

    child_id = fork();
    if(child_id == 0) {
        char *argv[] = {"find", expath, "-type", "f", "-iname", "*.*", "-exec", "mv", "{}", stpath, ";", NULL};
        execv("/usr/bin/find", argv);
    }
    while(wait(&status) > 0);
}


int main() {
    pid_t pid, sid;
    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    if ((chdir(dir_now)) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    

    while(1) {
        
        time_t now = time(NULL);
        
        // Obtain current time
        // `time()` returns the current time of the system as a `time_t` value
        time(&now);

        // localtime converts a `time_t` value to calendar time and
        // returns a pointer to a `tm` structure with its members
        // filled with the corresponding values
        struct tm *local = localtime(&now);

        // variables to store the date and time components
        int month, day, hour, minute, second;
        month = local -> tm_mon + 1;        // get month of year (0 to 11)
        day = local -> tm_mday;             // get hours since midnight (0-23)
        hour = local -> tm_hour;
        minute = local -> tm_min;

        // ini bday_mon dkk-nya diset dulu
        int bday_hour = 22;              
        int bday_mon = 4;               
        int bday_day = 9;
        int bday_minute = 22;
        if(bday_mon == month && bday_day == day && bday_minute == minute && bday_hour-6 == hour) {
                // 1a make folders
                for(int i=0; i<3; i++){
                    createF(i);
                }

                // 1b download zip files
                for(int i=0; i<3; i++) {
                    downloadF(i);
                }

                // 1c extract zip files
                for(int i=0; i<3; i++) {
                    extractF(i);
                }

                // 1d move file from extract folders to stev folders
                for(int i=0; i<3; i++) {
                    moveF(i);
                }
            } 

        else if(bday_mon == month && bday_day == day && bday_minute == minute && bday_hour == hour) { 
                
                for(int i=0; i<3; i++) {
                    zipStev(i);
                }
                for(int i=0; i<3; i++) {
                    removenExtract(i);
                }
                
                
            }

        sleep(30);
    }
}
