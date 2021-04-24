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

// 3.A.
//Membuat sebuah direktori dengan nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss] setiap 40 detik **
//untuk mebuat direktori, kami menggunakan fungsi `buatFolder'

void buatFolder(char namafolder[])
{
    pid_t pid;
    pid = fork();

    int status;
    if(pid == 0)
    {
        char *argv[] = {"mkdir","-p", namafolder, NULL};
        execv("/bin/mkdir",argv);
    }
    
    while ((wait(&status)) > 0);
}

// 3.B.
/*untuk melakukan download, pada fungsi download sebanyak 10 gambar dengan melakukan looping dan setiap 5 detik sekali 
dengan memaikai fungsi sleep(5) */

void download(char namafolder[])
{
    pid_t pid;
    int status;
    int i = 0;

    for(i ; i<10 ; i++) //looping download sebanyak 10 gambar
    {
        pid = fork();

        time_t t = time(NULL);
        struct tm curTime = *localtime(&t);
        char namafile[100];
        clock_t start = time(NULL), end;
        strftime(namafile, sizeof(namafile),"%Y-%m-%d_%H:%M:%S",&curTime);

        if(pid == 0)
        {
            char source[50] = "https://picsum.photos/";  
            char size[20];
            sprintf(size,"%ld",t%1000+50); //ukuran foto sesuai permintaan soal
            strcat(source,size);

            char savefile[300];
            sprintf(savefile, "/home/rihan/Desktop/Sisop/Praktikum 2/soal3/%s/%s.jpeg", namafolder, namafile); //savean file

            char *argv[] = {"wget","-q",source, "-O", savefile, NULL};
            execv("/bin/wget",argv);
        }
        
        sleep(5); // untuk 5 detik sekali

    }
}

// 3.C.
void successStat(char namafolder[])
{
    char pesan[20] = "Download Success", ch;
    int i,key = 5;

    //Soal 3C : Enkripsi Caesar Cipher
    for(i = 0; pesan[i] != '\0'; ++i)
    {
		ch = pesan[i];
		if(ch >= 'a' && ch <= 'z'){
			ch = ch + key;
			if(ch > 'z')	ch = ch - 'z' + 'a' - 1;
			pesan[i] = ch;
		}
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch + key;
			if(ch > 'Z')	ch = ch - 'Z' + 'A' - 1;
			pesan[i] = ch;
		}
	}

    char path[112]; //e
    sprintf(path, "%s/status.txt", namafolder);    
    FILE *fptr = fopen(path, "w");
    fputs(pesan, fptr);
    fclose(fptr);
}


void zipFile(char namafolder[]) //fungsi untuk melakukan zip (kemudian untuk melakukan zip pada direktori yang telah selesai dengan menggunkan fungsi zipFile)
{
    pid_t pid;
    pid = fork();
    int status;

    if(pid == 0)
    {
        char zip_path[150]; sprintf(zip_path, "%s.zip", namafolder);
        char *argv[] = {"zip", "-qrm", zip_path, namafolder, NULL};
        execv("/bin/zip", argv);
    }

    while(wait(&status) > 0);
}

// 3.D.
//Membuat program Killer.sh pada fungsi fileKill
/* kemudian pada fungsi fileKill jika argumen -z digunakan killall untuk melakukan kill pada parent 
    sehingga program utama akan langsung menghentikan semua operasinya, sedangkan untuk argumen -x 
    menggunakan kill maka program utama akan berhenti namun membiarkan proses di setiap direktori yang masih berjalan hingga selesai*/
void fileKill(const char *argv[],int sid)
{
    FILE *fptr;
    fptr = fopen("killer.sh","w");
    fputs("#!/bin/bash\n\n",fptr);
    char program[100];

    if(!strcmp(argv[1],"-z"))
    {
        sprintf(program,"killall -9 %s\nrm killer.sh",argv[0]);
        fputs(program,fptr);
    }
    else if (!strcmp(argv[1],"-x"))
    {
        sprintf(program,"kill -9 %d\nrm killer.sh",sid);
        fputs(program,fptr);
    }

    fclose(fptr);
}

int main(int argc, const char **argv)
{
    pid_t parentPID;
    parentPID = getpid();
    //3e
    //pada fungsi main menginisialisaikan program bisa berjalan dengan argumen -z dan -x
    if(!strcmp(argv[1],"-z") || !strcmp(argv[1],"-x"))
    {
        fileKill(argv, (int)parentPID);
//agar direktori dapat dibuat setiap selama 40 detik maka menggunakan sleep(40) di fungsi main dan menamai direktori dengan "%Y-%m-%d_%H:%M:%S"
        while(1)
        {
            time_t t = time(NULL);
            struct tm curTime = *localtime(&t);
            char namafolder[100];
            clock_t start = time(NULL), end;

            if(fork() == 0)
            {
                //soal 3A Membuat folder berdasarkan timestamp [YYYY-MM-dd_hh:mm:ss] per 40 detik
                strftime(namafolder, sizeof(namafolder),"%Y-%m-%d_%H:%M:%S",&curTime);
                buatFolder(namafolder); //fungsi 3b
                download(namafolder);//fungsi 3c
                successStat(namafolder);// fungsi 3d
                zipFile(namafolder);
                exit(EXIT_SUCCESS);
            }

            sleep(40);
        }
    }
}
