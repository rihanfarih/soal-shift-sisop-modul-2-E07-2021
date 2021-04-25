# Soal Shift Modul 2 Kelompok E07

* Nizar Mayraldo	      05111940000004
* Rihan farih bunyamin	05111940000165 
* Fayha Syifa Qalbi   	05111940000185

### Soal 1
Pada suatu masa, hiduplah seorang Steven yang hidupnya pas-pasan. Steven punya pacar,
namun sudah putus sebelum pacaran. Ketika dia galau memikirkan mantan, ia selalu menonton
https://www.youtube.com/watch?v=568DH_9CMKI untuk menghilangkan kesedihannya.
Di lain hal Steven anak yang tidak amat sangat super membenci matkul sisop, beberapa jam
setelah diputus oleh pacarnya dia menemukan wanita lain bernama Stevany, namun Stevany
berkebalikan dengan Steven karena menyukai sisop. Steven ingin terlihat jago matkul sisop
demi menarik perhatian Stevany.
Pada hari ulang tahun Stevany, Steven ingin memberikan Stevany zip berisikan hal-hal yang
disukai Stevany. Steven ingin isi zipnya menjadi rapi dengan membuat folder masing-masing
sesuai extensi. 
 * (a) Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama
folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg (b) untuk
musik Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link
dibawah juga :). (c) Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu
meng-extract-nya setelah didownload serta (d) memindahkannya ke dalam folder yang telah
dibuat (hanya file yang dimasukkan).
* (e) Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis 6 jam sebelum
waktu ulang tahun Stevany). (f) Setelah itu pada waktu ulang tahunnya Stevany, semua folder
akan di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete(sehingga hanya
menyisakan .zip).
Kemudian Steven meminta bantuanmu yang memang sudah jago sisop untuk membantunya
mendapatkan hati Stevany. Bantu Woy!!

#### Note: 
* Ulang Tahun Stevany : 09 April Pukul 22.22 WIB
* Semua poin dijalankan oleh 1 script di latar belakang, termasuk mendownload file
zip-nya. Jadi cukup jalankan script 1x serta ubah time dan date untuk check hasilnya.
* Tidak boleh menggunakan fungsi system(), mkdir(), dan rename() (Yang di bahasa C)
.... FORBIDDENNN!!
* Tidak boleh pake cron !!!
* Menggunakan fork dan exec.
#### Jawab:
###### 1a.
Pada 1a. diminta untuk membuat folder  Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg dengan menggunakan __fork__ dan __exec__. Fork disini berguna untuk membuat proses baru/child proses dan setelah berhasil membuat proses baru menggunakan exec untuk menjalankan programnya yaitu __mkdir__. Kemudian setelah fork dan exec ditambahkan __wait__, yang berguna menunggu child process selesai melakukan tugasnya, yaitu membuat folder. 
```
void createF(int ind) {
    pid_t child_id;
    int status;
    
    child_id = fork();
    if(child_id == 0) {
        char *argv[] = {"mkdir", folder_stevanny[ind], NULL};
        execv("/usr/bin/mkdir", argv);
    }
    while(wait(&status) > 0); 
}
```
###### 1b.
Pada 1b diminta untuk mendownload file - file .jpg, .mp3, .mp4 dari link yang yang ada. Untuk mendownload file - file tersebut kami juga menggunakan fork juga exec dengan command __wget__, seperti tips yang telah diberikan.

```
void downloadF(int ind) {
    ...
    if(child_id == 0) {
        char *argv[] = {"wget", "--no-check-certificate", "-q", link_stevanny[ind], "-O", zip_stevanny[ind], NULL};
        execv("/usr/bin/wget", argv);
    }
    ...
}
```
###### 1c.
Pada 1c diminta untuk meng-extract atau un-zip hasil download yang berupa Foto_for_Stefany.zip, Musik_for_Stevany.zip, Film_for_Stevany.zip. Sama seperti sebelumnya kami menggunakan exec, fork dengan command __unzip__ untuk meng-extract dan wait.
```
...
char *argv[] = {"unzip", "-q", zip_stevanny[ind], NULL};
        execv("/usr/bin/unzip", argv);
...
```
###### 1d.
Pada 1d diminta untuk memindahkan hasil extract ke dalam folder yang telah dibuat (hanya file yang dimasukkan). Kami menggunakan __find__ untuk mencari filesnya, karna find membutuhkan path untuk mencari files nya kami memasukkan path directory ke dalam string dan strcat. selanjutnya memakai __-exec mv {}__ untuk memindahkan files nya ke dalam folder yang telas dibuat.

![nomor1dfylm](https://github.com/rihanfarih/soal-shift-sisop-modul-2-E07-2021/blob/main/Screenshots/fylmc.png)
![nomor1dmusyik](https://github.com/rihanfarih/soal-shift-sisop-modul-2-E07-2021/blob/main/Screenshots/musyikc.png)
![nomor1dpyoto](https://github.com/rihanfarih/soal-shift-sisop-modul-2-E07-2021/blob/main/Screenshots/pyotoc.png)

###### 1e.


### Soal 2

### Soal 3
