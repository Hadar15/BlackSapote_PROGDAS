// Fungsi untuk melihat data karyawan
void viewData(Karyawan karyawan[], int count) {
    if (count == 0) { // Jika belum ada data, tampilkan pesan dan keluar
        printf("Belum ada data karyawan.\n");
        return;
    }
    printf("No | Nama                   | Hari | Gaji Pokok   | Jam Kerja | Lembur  | Bonus   | Gaji Bersih\n"); // Cetak header tabel
    printf("-----------------------------------------------------------------------------------------------\n"); // Garis pemisah
    int i;
    for (i = 0; i < count; i++) { // Cetak setiap data
        Karyawan *k = &karyawan[i];
        printf("%2d | %-22s | %4d | %12.2f | %9.2f | %7.2f | %7.2f | %11.2f\n",
            i + 1,
            k->nama,
            k->hariMasuk,
            k->gajiPokok,
            k->totalJamKerja,
            k->totalJamLembur,
            k->bonusKehadiran,
            k->gajiBersih
        );
    }
}

// Fungsi untuk menghapus data karyawan
void deleteData(Karyawan karyawan[], int *count) {
    if (*count == 0) { // Jika belum ada data, tampilkan pesan dan keluar
        printf("Belum ada data untuk dihapus.\n");
        return;
    }
    int id = getInt("Masukkan ID karyawan yang akan dihapus: ", 1, *count);
    int i;
    for (i = id - 1; i < *count - 1; i++) {
        karyawan[i] = karyawan[i + 1]; // Geser elemen setelah id-1 ke posisi sebelumnya, agar data tertimpa dan terhapus
    }
    (*count)--; // Jumlah data berkurang satu
    printf("\n\033[0;32mKaryawan dengan ID %d berhasil dihapus!\033[0m\n", id);
}