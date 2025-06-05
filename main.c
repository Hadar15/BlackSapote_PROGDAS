
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE "datakaryawan.txt"

// Struct untuk menyimpan data karyawan
typedef struct {
    char nama[50];
    int hariMasuk;         
    double gajiPokok;      
    double totalJamKerja;  
    double rata2JamKerja;  
    double totalJamLembur; 
    double tarifLembur;    
    double bonusKehadiran; 
    double gajiKotor;      
    double potonganPajak;  
    double potonganBPJS;   
    double gajiBersih;     
} Karyawan;

// Fungsi-fungsi yang akan digunakan
void loadData(Karyawan **karyawan, int *count, int *capacity);
void saveData(Karyawan *karyawan, int count);
void inputData(Karyawan **karyawan, int *count, int *capacity);
void viewData(Karyawan *karyawan, int count);
void deleteData(Karyawan *karyawan, int *count);
int getInt(const char *prompt, int min, int max);
double getDouble(const char *prompt, double min, double max);
void getString(const char *prompt, char *out, int maxLen);

int main() {
    Karyawan *karyawan = NULL;  // Inisialisasi array dinamis struct karyawan    
    int dataCount = 0;          // Inisialisasi jumlah data yang tersimpan
    int capacity = 0;           // Inisialisasi kapasitas array dinamis
    int choice;

    loadData(&karyawan, &dataCount, &capacity); // Memuat data karyawan

    do {
        system("cls");  // Bersihkan terminal agar program lebih rapi
        printf("===== Aplikasi Data Karyawan =====\n");
        printf("1. Input data karyawan\n");
        printf("2. Lihat data karyawan\n");
        printf("3. Hapus data karyawan\n");
        printf("4. Exit\n");
        choice = getInt("Pilih menu (1-4): ", 1, 4); // Meminta input user untuk pilihan menu

        // Pengkondisian menu
        switch (choice) { 
            case 1:
                system("cls"); // Bersihkan terminal
                inputData(&karyawan, &dataCount, &capacity); // Memanggil fungsi inputData
                saveData(karyawan, dataCount); // Memanggil fungsi saveData setelah menginput data
                printf("\033[5mTekan Enter untuk kembali ke menu...\033[0m"); // Menampilkan pesan dengan efek berkedip saat menekan Enter
                getchar();
                break; // Keluar dari switch case, kembali ke menu
            case 2:
                system("cls"); // Bersihkan terminal
                viewData(karyawan, dataCount); // Memanggil fungsi viewData
                printf("\033[5mTekan Enter untuk kembali ke menu...\033[0m"); // Menampilkan pesan dengan efek berkedip saat menekan Enter
                getchar();
                break; // Keluar dari switch case, kembali ke menu
            case 3:
                system("cls"); // Bersihkan terminal
                if (dataCount != 0) {
                    viewData(karyawan, dataCount); // Memanggil fungsi viewData
                }
                deleteData(karyawan, &dataCount);
                saveData(karyawan, dataCount);
                printf("\033[5mTekan Enter untuk kembali ke menu...\033[0m"); // Menampilkan pesan dengan efek berkedip saat menekan Enter
                getchar();
                break; // Keluar dari switch case, kembali ke menu
            case 4:
                system("cls"); // Bersihkan terminal
                printf("\e[0;32m\n\nData berhasil disimpan. Program selesai.\033[0m\n"); // Menampilkan pesan dengan efek berkedip saat menekan Enter
                break; // Keluar dari switch case, kembali ke menu
        }
    } while (choice != 4); // Tampilkan terus menu selama user belum menginput 4

    free(karyawan); // Membebaskan memori yang sudah dialokasikan
    return 0;
}

// Fungsi untuk menginput data karyawan
void inputData(Karyawan **karyawan, int *count, int *capacity) {
    // Periksa apakah perlu untuk menambah kapasitas
    if (*count >= *capacity) {
        *capacity *= 2; // Gandakan kapasitas 2 kali lipat
        *karyawan = realloc(*karyawan, (*capacity) * sizeof(Karyawan));
    }
    Karyawan *k = &(*karyawan)[*count]; // Membuat slot baru untuk data karyawan
    getString("Nama karyawan: ", k->nama, 50); // Input string nama karyawan
    k->hariMasuk       = getInt("Jumlah hari masuk (1-31 hari): ", 1, 31); // Input integer jumlah hari masuk
    k->gajiPokok       = getDouble("Gaji pokok per bulan (Rp): ", 0, 1e12); // Input double jumlah gaji pokok per bulan
    
    // Validasi total jam kerja: tidak boleh melebihi jumlah jam dalam hari kerja
    do {
        k->totalJamKerja = getDouble("Total jam kerja sebulan: ", 0, 1e6);
        if (k->totalJamKerja > k->hariMasuk * 24) {
            system("cls");
            printf("\033[1;31mInput invalid! Total jam kerja tidak boleh lebih dari %d jam.\033[0m\n", k->hariMasuk * 24);
        }
    } while (k->totalJamKerja > k->hariMasuk * 24);

    k->tarifLembur     = getDouble("Tarif lembur per jam (Rp): ", 0, 1e6); // Input double tarif lembur per jam
    k->bonusKehadiran  = getDouble("Bonus kehadiran (Rp): ", 0, 1e12);  // Input double bonus kehadiran

    k->rata2JamKerja  = k->totalJamKerja / k->hariMasuk; // Rata-rata jam kerja diperoleh dari membagi total jam kerja dengan jumlah hari masuk
    k->totalJamLembur = k->totalJamKerja - (8.0 * k->hariMasuk); // Jam lembur dihitung jika bekerja melebihi 8 jam dalam satu hari
    if (k->totalJamLembur < 0) k->totalJamLembur = 0; // Jika hasil jam lembur negatif, ubah jam lembur ke nol (tidak lembur)
    k->gajiKotor      = k->gajiPokok + (k->totalJamLembur * k->tarifLembur) + k->bonusKehadiran; // Gaji kotor diperoleh dari menjumlahkan gaji pokok, total bonus lembur dan bonus kehadiran

    k->potonganPajak  = 0.05 * k->gajiKotor; // Potongan pajak 5%
    k->potonganBPJS   = 0.02 * k->gajiKotor; // Potongan BPJS 2%
    k->gajiBersih     = k->gajiKotor - k->potonganPajak - k->potonganBPJS; // Gaji bersih diperoleh dari gaji kotor yang sudah dikurangi potongan pajak dan BPJS

    (*count)++; 
    printf("\n\033[0;32mKaryawan berhasil ditambahkan!\033[0m\n");
}

// Fungsi untuk hanya menginput tipe data integer
int getInt(const char *prompt, int min, int max) {
    char buf[128]; // Buffer input
    int val, ok;
    do {
        printf("%s", prompt); // Menampilkan pesan awal untuk input
        if (!fgets(buf, sizeof(buf), stdin)) exit(1); // Baca satu baris dari stdin ke buf; kalau gagal (EOF/error), keluar program
        ok = (sscanf(buf, "%d", &val) == 1); // Validasi input dengan cara parsing
        if (!ok || val < min || val > max) {
            system("cls");
            printf("\033[1;31mInput invalid! Masukkan angka antara %d dan %d.\033[0m\n", min, max);
            ok = 0;
        }
    } while (!ok); // Selama input belum sesuai, minta input ulang
    return val;
}

// Fungsi untuk hanya menginput tipe data double
double getDouble(const char *prompt, double min, double max) {
    char buf[128]; // Buffer input
    double val;
    int ok;
    do {
        printf("%s", prompt); // Menampilkan pesan awal untuk input
        if (!fgets(buf, sizeof(buf), stdin)) exit(1);
        ok = (sscanf(buf, "%lf", &val) == 1); // Validasi input dengan cara parsing
        if (!ok || val < min || val > max) {
            system("cls");
            printf("\033[1;31mInput invalid! Masukkan nilai antara %.2f dan %.2f.\033[0m\n", min, max);
            ok = 0;
        }
    } while (!ok); // Selama input belum sesuai, minta input ulang
    return val;
}

// Fungsi untuk hanya menginput tipe data string
void getString(const char *prompt, char *out, int maxLen) {
    char buf[256]; // Buffer input
    do {
        printf("%s", prompt); // menampilkan pesan awal untuk input
        if (!fgets(buf, sizeof(buf), stdin)) exit(1);
        buf[strcspn(buf, "\n")] = '\0';
        if (strlen(buf) == 0) {
            system("cls");
            printf("\033[1;31mInput invalid! Tidak boleh kosong.\033[0m\n");
        }
    } while (strlen(buf) == 0); // Selama input belum sesuai, minta input ulang
    strncpy(out, buf, maxLen);
    out[maxLen - 1] = '\0';
}

// Fungsi untuk memuat data karyawan
void loadData(Karyawan **karyawan, int *count, int *capacity) {
    FILE *file = fopen(DATA_FILE, "r"); // Buka file datakaryawan.txt dalam mode "read", hanya untuk membaca file
    if (!file) { // Jika file belum ada, inisialisasi array kosong secara dinamis
        *count = 0;
        *capacity = 10;
        *karyawan = malloc((*capacity) * sizeof(Karyawan));
        return;  // File belum ada, nanti akan dibuat saat sudah menyimpan data
    }

    *capacity = 10;
    *karyawan = malloc((*capacity) * sizeof(Karyawan));
    *count = 0; 
    while (!feof(file)) { // loop selama belum mencapai akhir dari file
        if (*count >= *capacity) {
            *capacity *= 2; // Menggandakan alokasi memori untuk data selanjutnya
            *karyawan = realloc(*karyawan, (*capacity) * sizeof(Karyawan)); // 
        }
        Karyawan *k = &(*karyawan)[*count];
        int ret = fscanf(file, " %49[^,],%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
            k->nama,
            &k->hariMasuk,
            &k->gajiPokok,
            &k->totalJamKerja,
            &k->rata2JamKerja,
            &k->totalJamLembur,
            &k->tarifLembur,
            &k->bonusKehadiran,
            &k->gajiKotor,
            &k->potonganPajak,
            &k->potonganBPJS
        ); // Parsing data dari file
        if (ret != 11) break; // Jika jumlah field yang berhasil dibaca tidak 11, hentikan loop
        k->gajiBersih = k->gajiKotor - k->potonganPajak - k->potonganBPJS; // Hitung ulang gaji bersih dari saat menyimpan file hanya disimpan sampai potongan BPJS
        (*count)++; // Pindah ke slot data berikutnya
    }
    fclose(file);
}

// Fungsi untuk menyimpan data karyawan
void saveData(Karyawan *karyawan, int count) {
    FILE *file = fopen(DATA_FILE, "w"); // Buka file datakaryawan.txt dalam mode "write", untuk menimpa file
    if (!file) {
        perror("\033[1;31mTidak dapat menyimpan file!\033[0m\n"); // Tampilkan pesan error jika tidak ada file
        return;
    }
    int i;
    for (i = 0; i < count; i++) { // Loop untuk menulis setiap data yang ada ke dalam file datakaryawan.txt
        Karyawan *k = &karyawan[i];
        fprintf(file, "%s,%d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
            k->nama,
            k->hariMasuk,
            k->gajiPokok,
            k->totalJamKerja,
            k->rata2JamKerja,
            k->totalJamLembur,
            k->tarifLembur,
            k->bonusKehadiran,
            k->gajiKotor,
            k->potonganPajak,
            k->potonganBPJS
        );
    }
    fclose(file);
}

