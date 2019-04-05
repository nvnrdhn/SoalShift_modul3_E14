# soal1

    for (int i = 1;i<argc;i++)
      sscanf(argv[i], "%llu", &num[i-1]);


Potongan kode diatas berfungsi untuk mengubah argumen yang diberikan ke program dari bentuk char ke bentuk unsigned long long kemudian disimpan kedalam array num[].

`qsort(num, n, sizeof(unsigned long long), cmpfunc);`

Kemudian argumen diurutkan dari kecil ke besar menggunakan fungsi qsort dan fungsi compare cmpfunc.

    for (int i=0;i<n;i++) 
      pthread_create(&t[i], NULL, fact, (void*)&num[i]);

Kemudian untuk setiap argumen yang diberikan, program akan membuat sebuah thread untuk menghitung faktorial dari argumen tersebut.

    void *fact( void *ptr )
    {
      unsigned long long ans=1;
      unsigned long long *f = (unsigned long long*)ptr;
      pthread_t id = pthread_self();
      for (int i=2;i<=*f;i++)
        ans*=i;
      for (int i=0;i<n;i++) {
        if (pthread_equal(id, t[i])) {
          hasil[i] = ans;
        }
      }
    }
    
Fungsi diatas digunakan untuk menghitung faktorial dari argumen, kemudian hasilnya disimpan di array hasil[]. Terakhir, program akan mencetak hasil dari index 0 sampai n-1.

# soal2

# serverjual

Langkah pertama membuat variabel stok yang di share dengan server pembeli. Awalnya stok bernilai 0. Kemudian buat 2 thread: thread pertama berfungsi sebagai server, thread kedua berfungsi untuk mencetak banyak stok tiap 5 detik. Server penjual dibuka di port 8080. Limit banyak client yang terkoneksi dengan mengubah argumen fungsi listen `listen(server_fd, 1);`. Server penjual akan menangkap string yang dikirim oleh client penjual. Jika string yang ditangkap adalah string "tambah", maka tambah stok dengan 1. Jika string yang ditangkap adalah string "exit", maka server akan berhenti.

# clientjual

Langkah pertama membuat koneksi dengan server penjual di port 8080. Selama server berjalan, client dapat mengirim string ke server.
 
# serverbeli

Langkah pertama membuat variabel stok yang di share dengan server penjual. Kemudian buat server di port 8081 agar tidak bentrok dengan server penjual. Selama server berjalan, server dapat menerima string yang dikirim oleh client penjual. Jika string yang diterima adalah string "beli" dan jika stok masih ada, maka stok dikurangi 1 dan server akan mengirim respon berupa string "transaksi berhasil" ke client pembeli. Jika stok habis maka server akan mengirim respon "transaksi gagal".

# clientbeli

Langkah pertama membuat koneksi dengan server pembeli di port 8081. Selama server berjalan, client dapat mengirim string ke server. Jika string yang dikirim adalah string "beli", maka client akan menunggu respon dari server.

# soal3

Pada soal ini dibuat dua thread, yaitu untuk Agmal, dan untuk Iraj. Kemudian lakukan looping untuk scan sesuai dengan fittur yang ada ( variable scan digunakan supaya bisa terus menerus dilakukan scan),lalu status sendiri terdiri atas dua, yaitu satu untuk melakukan perintah "Agmal Ayo Bangun", dan 2 untuk "Iraj Ayo Tidur". Kemudian setiap penambahan atau pengurangan pada wakup dan spirit status, terdapat masing-masing counter. Jika counter sudah mencapai tiga, maka dilakukan sleep. Namun dalam kode ini masih terdapat kesalahan yaitu ketika dijumlahkan atau dikurangkan, hasilnya menjadi tiga kali lipatnya. (Misal hanya ditambah 15, namun menjadi 30)

# soal4

Pada soal ini dibuat tiga thread, yaitu untuk zip, unzip, dan membuat teks. Pada thread teks, terdapat array untuk command  `ps -aux | head -11` hal ini bertujuan untuk mengambil data 10 teratas dari ps -aux. Kemudian membuat folder FolderProses sesuai indeks(1 atau 2), dan juga membuat SimpanProses[1/2] untuk menyimpan hasil command. Kemudian pada thread zip, bertujuan untuk mengkompres file, dan pada unzip untuk mengekstraknya kembali. 
# soal5

# game

Langkah pertama membuat variabel foodstock yang di share dengan program shop. Awalnya stok bernilai 5. Kemudian inisiasi variabel player yang berupa struct monster dengan data member: nama, health, hygiene, hunger. Inisiasi variabel enemy, awalnya memiliki health 100. Kemudian buat 3 thread: thread pertama berfungsi menampilkan menu saat ini, thread kedua berfungsi menangkap keypress sebagai input kemudian memprosesnya, thread ketiga berfungsi meng-update status (hunger, hygiene, health) dan cooldown bath, dan tidak akan berjalan ketika game sedang dalam mode battle. Program menggunakan global variabel status untuk memberitahu thread status game sekarang. Status bernilai 5 jika game sedang dalam mode standby, bernilai 3 jika sedang dalam mode battle, dan bernilai 4 jika sedang dalam mode shop.

# shop

Langkah pertama membuat variabel foodstock yang di share dengan program game. Kemudian buat 2 thread: thread pertama berfungsi untuk mencetak menu shop, thread kedua berfungsi untuk menangkap keypress sebagai input kemudian memprosesnya. Jika input berupa 1, maka thread akan menambah variabel stok dengan 1.
