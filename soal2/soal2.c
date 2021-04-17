#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main() {
  pid_t child_id;
  int status;

  child_id = fork();

  if (child_id < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }

  if (child_id == 0) {
    // this is child

    char *argv[] = {"mkdir", "-p", "/home/nizar/modul2/petshop", NULL};
    execv("/bin/mkdir", argv);

  } else {
    // this is parent
    while ((wait(&status)) > 0);
    char *argv[] = {"unzip", "-q", "/home/nizar/Downloads/pets.zip", "-x", "*/*", "-d", "/home/nizar/modul2/petshop", NULL};
    execv("/bin/unzip", argv);
  }
}