# SoalShift_modul3_E14

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
