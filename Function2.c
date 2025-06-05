
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
