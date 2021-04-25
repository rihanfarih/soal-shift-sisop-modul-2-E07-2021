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
##### 1a.
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
##### 1b.
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
##### 1c.
Pada 1c diminta untuk meng-extract atau un-zip hasil download yang berupa Foto_for_Stefany.zip, Musik_for_Stevany.zip, Film_for_Stevany.zip. Sama seperti sebelumnya kami menggunakan exec, fork dengan command __unzip__ untuk meng-extract dan wait.
```
...
char *argv[] = {"unzip", "-q", zip_stevanny[ind], NULL};
        execv("/usr/bin/unzip", argv);
...
```
##### 1d.
Pada 1d diminta untuk memindahkan hasil extract ke dalam folder yang telah dibuat (hanya file yang dimasukkan). Kami menggunakan __find__ untuk mencari filesnya, karna find membutuhkan path untuk mencari files nya kami memasukkan path directory ke dalam string dan strcat. selanjutnya memakai __-exec mv {}__ untuk memindahkan files nya ke dalam folder yang telas dibuat.

![nomor1dfylm](https://github.com/rihanfarih/soal-shift-sisop-modul-2-E07-2021/blob/main/Screenshots/fylmc.png)
![nomor1dmusyik](https://github.com/rihanfarih/soal-shift-sisop-modul-2-E07-2021/blob/main/Screenshots/musyikc.png)
![nomor1dpyoto](https://github.com/rihanfarih/soal-shift-sisop-modul-2-E07-2021/blob/main/Screenshots/pyotoc.png)

##### 1e.
Pada 1e diminta untuk menjalankan 1a, 1b, 1c, 1d otomatis 6 jam sebelum waktu ulang tahun Stevany. Disini kami menggunakan daemon, dan time.h untuk mendapatkan local time dan mensetting waktu jalan scriptnya. 
```
time_t now = time(NULL);
        
        // Obtain current time
        // `time()` returns the current time of the system as a `time_t` value
        time(&now);
        
        // variables to store the date and time components
        int month, day, hour, minute, second;
        
        // localtime converts a `time_t` value to calendar time and
        // returns a pointer to a `tm` structure with its members
        // filled with the corresponding values
        struct tm *local = localtime(&now);
        month = local -> tm_mon + 1;        // get month of year (0 to 11)
        day = local -> tm_mday;             // get hours since midnight (0-23)
        hour = local -> tm_hour;
        minute = local -> tm_min;
        seconds = local->tm_sec;

        // ini bday_mon dkk-nya disetting dulu sesuai ulang tahun Stevanny
        int bday_hour = 22;              
        int bday_mon = 4;               
        int bday_day = 9;
        int bday_minute = 22;
        if(bday_mon == month && bday_day == day && bday_minute == minute && hour == 16) {
                ... menjalankan 1a, 1b, 1c, 1d ...
            }
```
![nomor1e](https://github.com/rihanfarih/soal-shift-sisop-modul-2-E07-2021/blob/main/Screenshots/1e.png)
##### 1f.
Pada 1f diminta untuk pada waktu ulang tahunnya Stevany, semua folder akan di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete(sehingga hanya
menyisakan .zip). 
```
...
// untuk mengzip dan mendelete folder yang telah terzip
char *argv[] = {"zip", "-q", "-r", "-m", "Lopyu_Stevanny.zip", folder_stevanny[ind], NULL};
        execv("/usr/bin/zip", argv);
...
// untuk mendelete folder yang tersisa
 char *argv[] = {"rm", "-d", extract_stevanny[ind], NULL};
        execv("/usr/bin/rm", argv);
...
// untuk menjalankap zip dan delet pada waktu ulang tahun Stevanny
else if(bday_mon == month && bday_day == day && bday_minute == minute && bday_hour == hour)
...
```
![nomor1f](https://github.com/rihanfarih/soal-shift-sisop-modul-2-E07-2021/blob/main/Screenshots/1f.png)
##### Kendala Pengerjaan:
* Masih sedikit bingung untuk menggunakan fork dalam satu fungsi di main dan saat dicoba didalam satu main function terdapat banyak error
* Terjadi error saat melakukan testing daemonnya
* Beberapa kali error saat mensetting localtime nya karna belum tau cara mensetting local time
* Beberapa kali error saat membuat argv di fork dan exec nya
* Tingkat kesulitan soal meningkat sedikit pesat 
* Banyak fungsi yang belum pernah diketahui jadi banyak terjadi error/ kadang fungsi tidak berhasil dieksekusi  
    

### Soal 2

Loba bekerja di sebuah petshop terkenal, suatu saat dia mendapatkan zip yang berisi banyak sekali foto peliharaan dan Ia diperintahkan untuk mengkategorikan foto-foto peliharaan tersebut. Loba merasa kesusahan melakukan pekerjaanya secara manual, apalagi ada kemungkinan ia akan diperintahkan untuk melakukan hal yang sama. Kamu adalah teman baik Loba dan Ia meminta bantuanmu untuk membantu pekerjaannya.

##### 2a.
Pertama-tama program perlu mengextract zip yang diberikan ke dalam folder “/home/[user]/modul2/petshop”. Karena bos Loba teledor, dalam zip tersebut bisa berisi folder-folder yang tidak penting, maka program harus bisa membedakan file dan folder sehingga dapat memproses file yang seharusnya dikerjakan dan menghapus folder-folder yang tidak dibutuhkan.

```
void ekstrak()
{
    pid_t child_id;
    child_id = fork();
    int status;
    char asal[100] = "/home/nizar/Downloads/pets.zip";
    char tujuan[100] = "/home/nizar/modul2/petshop";

    if(child_id<0)
    {
       exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
    }

    if (child_id==0)
    {
        char *argv[] = {"mkdir","-p",tujuan,NULL};
        tunda("/bin/mkdir", argv);
    }

    else {
        while ((wait(&status))>0);
        char *argv2[] = {"unzip","-q",asal,"-x","*/*","-d",tujuan,NULL};
        //-x berfungsi untuk exclude dimana */* untuk file folder. Sehingga folder tidak ter zip.
        tunda("/bin/unzip", argv2);
    }
}

void tunda(char perintah[],char *argv[])
{
    pid_t child_id;
    int status;

    child_id=fork();

    if(child_id==0)
    {
        execv(perintah, argv);
    }

    else
    {
        while ((wait(&status))>0);
    }
}

```

fungsi tunda adalah untuk melaksanakan perintah namun menunggu childnya selesai sehingga program dapat dilaksanakan dengan runtut dan tidak tumpang tindih. Kemudian fungsi ekstrak untuk mengunzip file zip yang diberikan dengan menggunakan perintah tunda untuk mengeksekusi argumen yang diberikan. Argumen tersebut adalah untuk mengekstrak file petshop.zip yang terdapat pada direktori Downloads ke direktori /home/user/modul2/petshop. Namun, sebelum melakukan ekstrak program harus membuat folder dengan menggunakan argumen mkdir pada program dan menggunakan fork agar tidak tumpang tindih.

##### 2b.
Foto peliharaan perlu dikategorikan sesuai jenis peliharaan, maka kamu harus membuat folder untuk setiap jenis peliharaan yang ada dalam zip. Karena kamu tidak mungkin memeriksa satu-persatu, maka program harus membuatkan folder-folder yang dibutuhkan sesuai dengan isi zip. Contoh: Jenis peliharaan kucing akan disimpan dalam “/petshop/cat”, jenis peliharaan kura-kura akan disimpan dalam “/petshop/turtle”.

```
void buatfolder()
{
    pid_t child_id;
    child_id = fork();
    int status;
    if(child_id<0)
    {
       exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti 
    }

    if (child_id==0)
    {
    DIR *dp;
    char path[100] = "/home/nizar/modul2/petshop";
    dp = opendir(path);
        if (dp != NULL)
        {
            struct dirent *ep;
            while((ep = readdir(dp))!= NULL)
            {   
                if(ep->d_type == DT_REG)
                {
                    char *temp1,*temp2,*temp3,*temp4;
                    char *namafile=ep->d_name;
                    char *namabaru=potong(namafile);
                    
                    char copy1[100], copy2[100], copy3[100];
                    char base2[100], base3[100];
                    
                    for(temp1=strtok_r(namabaru,"_",&temp3); temp1!=NULL; temp1=strtok_r(NULL,"_",&temp3))
                    {
                        char hewan[100], nama[100], umur[100];
                        int ket=0;
                        char base[100]="/home/nizar/modul2/petshop/";
                        
                        strcpy(copy1, ep->d_name);
                        strcpy(base2, base);
                        strcpy(base3, base);
                        strcpy(copy2, ep->d_name);
                        strcpy(copy3, ep->d_name);

                        for(temp2=strtok_r(temp1,";",&temp4); temp2!=NULL; temp2=strtok_r(NULL,";",&temp4))
                            {
                                if(ket==0) strcpy(hewan,temp2);
                                if(ket==1) strcpy(nama,temp2);
                                if(ket==2) strcpy(umur,temp2);
                                ket=ket+1;
                            }
                        

                        //2b
                        strcat(base,hewan);
                        char *argmk[]={"mkdir","-p",base,NULL};
                        tunda("/bin/mkdir",argmk);
```
Dengan menggunakan fungsi yang ada di dirent.h, kita menggunakan DIR untuk membuka directory dan struct dirent untuk mmebaca list folder yang ada di direktori yang ditunjuk. Kemudian dengan menggunakan fungsi tersebut sebagai parameter pada fungsi, diambil string pertama sebelum tanda ; dimana string tersebut merupakan jenis hewan dan diguakan untuk folder. Kemudian di akhir nanti menggunakan argumen dan fungsi tunda untuk membuat direktori sesuai dengan jenis nama hewan yang telah dibaca tadi.

##### 2c.
Setelah folder kategori berhasil dibuat, programmu akan memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan.
Contoh: “/petshop/cat/joni.jpg”.

```
//2c
//memindahkan ke folder
  strcat(nama,".jpg");
  strcat(base2,copy2);
                        
  char *pindah[]={"cp","-r", base2, base, NULL};
  tunda("/bin/cp",pindah);

//merubah nama
  strcpy(base3,base);
  strcat(base3,"/");
  strcat(base3,copy2);
  strcat(base,"/");
  strcat(base,nama);
  char *rename[]={"mv",base3,base,NULL};
  tunda("/bin/mv",rename);
  
char* potong (char* s){
    int n, i;
    char* new;
    for (i = 0; s[i] != '\0'; i++);
    // panjang string baru
    n = i - 4 + 1;
    if (n < 1)
        return NULL;
    new = (char*) malloc (n * sizeof(char));
    for (i = 0; i < n - 1; i++)
        new[i] = s[i];
    new[i] = '\0';
    return new;
}
```
di sini gabungkan string yang diambil dengan jpg karena pada fungsi sebelumya terjadi pemotongan format file untuk scanning dan membuat base2 menjadi alamat tujuan. Setelah itu dengan menggunakan fungsi tunda untuk execute dipindahkan dengan menggunakan cp untuk mencopy. Lalu ubah namanya menjadi nama.jpg pada proses rename menggunakan fungsi mv. fungsi potong tadi digunakan untuk memotong jpg untuk menscan list file yang ada di direktori.

##### 2d.
Karena dalam satu foto bisa terdapat lebih dari satu peliharaan maka foto harus di pindah ke masing-masing kategori yang sesuai. Contoh: foto dengan nama “dog;baro;1_cat;joni;2.jpg” dipindah ke folder “/petshop/cat/joni.jpg” dan “/petshop/dog/baro.jpg”.

```
 if(ep->d_type == DT_REG)
                {
                    char *temp1,*temp2,*temp3,*temp4;
                    char *namafile=ep->d_name;
                    char *namabaru=potong(namafile);
                    
                    char copy1[100], copy2[100], copy3[100];
                    char base2[100], base3[100];
                    
                    for(temp1=strtok_r(namabaru,"_",&temp3); temp1!=NULL; temp1=strtok_r(NULL,"_",&temp3))
                    {
                        char hewan[100], nama[100], umur[100];
                        int ket=0;
                        char base[100]="/home/nizar/modul2/petshop/";
                        
                        strcpy(copy1, ep->d_name);
                        strcpy(base2, base);
                        strcpy(base3, base);
                        strcpy(copy2, ep->d_name);
                        strcpy(copy3, ep->d_name);

                        for(temp2=strtok_r(temp1,";",&temp4); temp2!=NULL; temp2=strtok_r(NULL,";",&temp4))
                            {
                                if(ket==0) strcpy(hewan,temp2);
                                if(ket==1) strcpy(nama,temp2);
                                if(ket==2) strcpy(umur,temp2);
                                ket=ket+1;
                            }
```
pada for pertama digunakan untuk memotong nama file string setiap bertemu dengan _ dan di for kedua digunakan untuk memoting nama file string setiap bertemu dengan ; dengan menggunakan fungsi strtok_r dari direktori awal, parameter, dan tempat alamat untuk menyimpan.

##### 2e.
Di setiap folder buatlah sebuah file "keterangan.txt" yang berisi nama dan umur semua peliharaan dalam folder tersebut

```
//2e sementara
                 char txtloc[100],txtpath[100];
                 strcpy(txtloc,base);
                 stpcpy(txtpath,txtloc);
//2e
                 strcat(txtpath,"/keterangan.txt");
                 strcpy(isi,"nama : ");
                 strcat(isi,namaditxt);
                 strcat(isi,"\n");
                 strcat(isi,"umur : ");
                 strcat(isi,umur);
                 strcat(isi,"tahun\n\n");
                 FILE *fptr=fopen(txtpath,"a");
                 fputs(isi,fptr);
                 fclose(fptr);
//menghapus file yang telah dipindah
                if(ep->d_type == DT_REG)
                {
                    char base[99]="/home/nizar/modul2/petshop/";
                    strcat(base,ep->d_name);

                    char *hapus[]={"rm","-rf",base,NULL};
                    tunda("/bin/rm",hapus);
                }
```
pada string txtpath, digunakan untuk alamat keterangan.txt Selain itu string isi berisi konten yang akan dipush ke file keterangan dimana terdapat rangkaian proses untuk strcat untuk menginput nama dan juga umur hewan. Lalu string isi dipush ke txtpath menggunakan "a" agar string yang lama tidak dihapus. Setelah serangkaian proses dijalankan hal yang terakhir dilakukan adalah menghapus file foto yang telah diproses.

###Kendala selama pengerjaan
Kesulitan dalam memahami maksud soal
Bingung harus menggunakan fungsi apa dan bagaimana
Tidak tau harus menggunakan fungsi variatif yang tidak ada di modul seperti dirent.h dan lain lain

###Screenshot hasil pengerjaan

### Soal 3
#### 3a
Membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp **YYYY-mm-dd_HH:ii:ss**

pertama untuk mebuat direktori, kami menggunakan fungsi `buatFolder` membuat folder dengan memanggil mkdir menggunakan execv
```
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
```
lalu agar direktori dapat dibuat setiap selama 40 detik maka menggunakan sleep(40) di fungsi main dan menamai direktori dengan "%Y-%m-%d_%H:%M:%S" kita gunakan:
```
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
```
#### 3b
Setiap direktori yang sudah dibuat diisi dengan 10 gambar yang didownload dari https://picsum.photos/, dimana setiap gambar akan didownload setiap 5 detik. Setiap gambar yang didownload akan diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss] dan gambar tersebut berbentuk persegi dengan ukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix.

kita gunakan fungsi perulangan serta sleep untuk melakukan download dimana pada fungsi download sebanyak 10 gambar dengan melakukan looping dan setiap 5 detik sekali dengan memakai fungsi sleep(5)
```
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
        strftime(namafile, sizeof(namafile),"%Y-%m-%d_%H:%M:%S",&curTime); // dahulu format penamaan hasil download dengan mengambil waktu ketika melakukan proses download

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
```
Untuk mendownload gambar dengan nama format timestamp juga caranya sama seperti soal bagian a.
Untuk menjadikan gambar tersebut berbentuk persegi dengan ukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix, 
kami menggunakan sprintf yang sebelumnya n sudah mengambil waktu local terlebih dahulu.

#### 3c
Setelah direktori telah terisi dengan 10 gambar, program tersebut akan membuat sebuah file “status.txt”, dimana didalamnya berisi pesan “Download Success” yang terenkripsi dengan teknik Caesar Cipher dan dengan shift 5. Caesar Cipher adalah Teknik enkripsi sederhana yang dimana dapat melakukan enkripsi string sesuai dengan shift/key yang kita tentukan. Misal huruf “A” akan dienkripsi dengan shift 4 maka akan menjadi “E”. Karena Ranora orangnya perfeksionis dan rapi, dia ingin setelah file tersebut dibuat, direktori akan di zip dan direktori akan didelete, sehingga menyisakan hanya file zip saja.

pertama Membuat file status.txt pada fungsi succecStat 
```
void successStat(char namafolder[])
{
    char pesan[20] = "Download Success", ch;
    int i,key = 5;
  ```
  
  lalu melakukan enkripsi caesar chiper dimana Untuk melakukan enkripsi caesar cipher shift 5, dapat dilakukan dengan menambah 5 pada ASCII setiap karakter. 
    Namun, perlu diperhatikan apabila ketika ASCII karakter ditambah 5 sudah melebihi 'z', 
    karakter tersebut harus diputar lagi kembali ke 'a'*/
    
 ```
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
 ```
 setelah itu memasukan hasil chiper yang sudah dibuat sebelumnya, kami menggunakan kode sebagai berikut. dimana program akan membuat file yang bernama `status.txt` yang isinya adalah hasil dari chiper text diatas (denganfputs)
 ```
 har path[112]; //e
    sprintf(path, "%s/status.txt", namafolder);    
    FILE *fptr = fopen(path, "w");
    fputs(pesan, fptr);
    fclose(fptr);
}
```
terakhir fungsi untuk melakukan zip (kemudian untuk melakukan zip pada direktori yang telah selesai dengan menggunkan fungsi zipFile)
```
void zipFile(char namafolder[]) 
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
```
#### 3d
Untuk mempermudah pengendalian program, pembimbing magang Ranora ingin program tersebut akan men-generate sebuah program “Killer” yang executable, dimana program tersebut akan menterminasi semua proses program yang sedang berjalan dan akan menghapus dirinya sendiri setelah program dijalankan. Karena Ranora menyukai sesuatu hal yang baru, maka Ranora memiliki ide untuk program “Killer” yang dibuat nantinya harus merupakan program bash.

Membuat program Killer.sh pada fungsi fileKill
```
void fileKill(const char *argv[],int sid)
{
    FILE *fptr;
    fptr = fopen("killer.sh","w");
    fputs("#!/bin/bash\n\n",fptr);
    char program[100];
```

#### 3e
Untuk mengaktifkan mode pertama, program harus dijalankan dengan argumen -z, dan Ketika dijalankan dalam mode pertama, program utama akan langsung menghentikan semua operasinya Ketika program Killer dijalankan. Sedangkan untuk mengaktifkan mode kedua, program harus dijalankan dengan argumen -x, dan Ketika dijalankan dalam mode kedua, program utama akan berhenti namun membiarkan proses di setiap direktori yang masih berjalan hingga selesai (Direktori yang sudah dibuat akan mendownload gambar sampai selesai dan membuat file txt, lalu zip dan delete direktori).

pertama pada fungsi main menginisialisaikan program bisa berjalan dengan argumen -z dan -x
```
 if(!strcmp(argv[1],"-z") || !strcmp(argv[1],"-x"))
    {
        fileKill(argv, (int)parentPID);
```
 lalu memasukkan source code dimana Apabila -z akan memasukkan string killall -9 soal3 untuk mematikan seluruh proses
untuk -x akan memasukkan string kill -9 %d dimana %d adalah pid untuk mematikan proses utama. Sehingga apabila -x dijalankan, 
program akan menyelesaikan proses terakhir, baru kemudian berhenti.*/
```
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
```

#### kendala pengerjaan
* Tingkat kesulitan soal meningkat sedikit pesat 
* Banyak fungsi yang belum pernah dicoba sehingga kesulitan saat pengerjaan
* pada run/compile pertama muncul error segmentation fault (core dumped)
![nomor3error](https://github.com/rihanfarih/soal-shift-sisop-modul-2-E07-2021/blob/main/Screenshots/error3.jpg)

#### Screenshoot hasil
* hasil pengerjaan
![nomor3](https://github.com/rihanfarih/soal-shift-sisop-modul-2-E07-2021/blob/main/Screenshots/tiga3.jpg)
* File zip yang berisi 10 foto dan status.txt
![nomor3-1](https://github.com/rihanfarih/soal-shift-sisop-modul-2-E07-2021/blob/main/Screenshots/tiga2.jpg)
* Isi status.txt, berisi pesan Download Success yang telah dienkripsi
![nomor3-2](https://github.com/rihanfarih/soal-shift-sisop-modul-2-E07-2021/blob/main/Screenshots/tiga1.jpg)


        

    


