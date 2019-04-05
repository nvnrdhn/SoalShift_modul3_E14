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
