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