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