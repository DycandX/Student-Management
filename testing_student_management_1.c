#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur data untuk menyimpan informasi mahasiswa
struct Mahasiswa {
    char *nama;
    int nim;
    char *jurusan;
    char *prodi;
    char *asal;
    char *tanggal_lahir;
};

struct Mahasiswa mahasiswa[100]; // Maksimum 100 mahasiswa
int jumlahMahasiswa = 0;

// Fungsi untuk memuat data dari file
void muatDariFile() {
    FILE *file = fopen("mahasiswa.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    // Skip header
    char line[256];
    fgets(line, sizeof(line), file); // Header Nama, NIM, Jurusan, Prodi, Asal, Tanggal Lahir
    fgets(line, sizeof(line), file); // Garis pembatas

    while (fgets(line, sizeof(line), file) != NULL) {
        // Membersihkan karakter newline jika ada
        line[strcspn(line, "\r\n")] = '\0';

        // Memecah baris berdasarkan delimiter "|"
        char *token = strtok(line, "|");
        
        // Menyimpan setiap atribut ke dalam struktur mahasiswa
        mahasiswa[jumlahMahasiswa].nama = strdup(token);
        token = strtok(NULL, "|");
        mahasiswa[jumlahMahasiswa].nim = atoi(token);
        token = strtok(NULL, "|");
        mahasiswa[jumlahMahasiswa].jurusan = strdup(token);
        token = strtok(NULL, "|");
        mahasiswa[jumlahMahasiswa].prodi = strdup(token);
        token = strtok(NULL, "|");
        mahasiswa[jumlahMahasiswa].asal = strdup(token);
        token = strtok(NULL, "|");
        mahasiswa[jumlahMahasiswa].tanggal_lahir = strdup(token);

        jumlahMahasiswa++;
    }
    fclose(file);

    printf("Data mahasiswa berhasil dimuat dari file.\n");
}


// Fungsi untuk menampilkan data mahasiswa dalam format tabel
void tampilkanMahasiswa(struct Mahasiswa mhs) {
    printf("%-20s | %-10d | %-15s | %-25s | %-20s | %-15s\n", 
           mhs.nama, mhs.nim, mhs.jurusan, mhs.prodi, mhs.asal, mhs.tanggal_lahir);
}


// Fungsi untuk menambah data mahasiswa
void tambahMahasiswa() {
    if (jumlahMahasiswa >= 100) {
        printf("Kapasitas maksimum mahasiswa telah tercapai.\n");
        return;
    }

    mahasiswa[jumlahMahasiswa].nama = malloc(100 * sizeof(char));
    mahasiswa[jumlahMahasiswa].jurusan = malloc(100 * sizeof(char));
    mahasiswa[jumlahMahasiswa].prodi = malloc(100 * sizeof(char));
    mahasiswa[jumlahMahasiswa].asal = malloc(100 * sizeof(char));
    mahasiswa[jumlahMahasiswa].tanggal_lahir = malloc(20 * sizeof(char));

    printf("Masukkan data mahasiswa:\n");
    printf("Nama: ");
    getchar(); // Membersihkan newline character yang tersisa di buffer
    fgets(mahasiswa[jumlahMahasiswa].nama, 100, stdin);
    mahasiswa[jumlahMahasiswa].nama[strcspn(mahasiswa[jumlahMahasiswa].nama, "\n")] = '\0'; // Remove newline character

    printf("NIM: ");
    scanf("%d", &mahasiswa[jumlahMahasiswa].nim);
    getchar(); // Membersihkan newline character yang tersisa di buffer

    printf("Jurusan: ");
    fgets(mahasiswa[jumlahMahasiswa].jurusan, 100, stdin);
    mahasiswa[jumlahMahasiswa].jurusan[strcspn(mahasiswa[jumlahMahasiswa].jurusan, "\n")] = '\0';

    printf("Prodi: ");
    fgets(mahasiswa[jumlahMahasiswa].prodi, 100, stdin);
    mahasiswa[jumlahMahasiswa].prodi[strcspn(mahasiswa[jumlahMahasiswa].prodi, "\n")] = '\0';

    printf("Asal: ");
    fgets(mahasiswa[jumlahMahasiswa].asal, 100, stdin);
    mahasiswa[jumlahMahasiswa].asal[strcspn(mahasiswa[jumlahMahasiswa].asal, "\n")] = '\0';

    printf("Tanggal Lahir (DD/MM/YYYY): ");
    fgets(mahasiswa[jumlahMahasiswa].tanggal_lahir, 20, stdin);
    mahasiswa[jumlahMahasiswa].tanggal_lahir[strcspn(mahasiswa[jumlahMahasiswa].tanggal_lahir, "\n")] = '\0';

    jumlahMahasiswa++;

    // Menyimpan data mahasiswa ke dalam file
    FILE *file = fopen("mahasiswa.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    if (jumlahMahasiswa == 1) {
        fprintf(file, "%-20s | %-10s | %-15s | %-25s | %-20s | %-15s\n", 
                "Nama", "NIM", "Jurusan", "Prodi", "Asal", "Tanggal Lahir");
        fprintf(file, "----------------------------------------------------------------------------------------------------------------------\n");
    }
    fprintf(file, "%-20s | %-10d | %-15s | %-25s | %-20s | %-15s\n", 
            mahasiswa[jumlahMahasiswa-1].nama, mahasiswa[jumlahMahasiswa-1].nim,
            mahasiswa[jumlahMahasiswa-1].jurusan, mahasiswa[jumlahMahasiswa-1].prodi, mahasiswa[jumlahMahasiswa-1].asal,
            mahasiswa[jumlahMahasiswa-1].tanggal_lahir);
    fclose(file);

    printf("Data mahasiswa berhasil ditambahkan.\n");
}



// Fungsi untuk mencari data mahasiswa berdasarkan NIM menggunakan binary search
void cariMahasiswa(int cariNIM) {
    int low = 0;
    int high = jumlahMahasiswa - 1;
    int found = 0; // Penanda apakah data ditemukan atau tidak

    while (low <= high) {
        int mid = (low + high) / 2;
        if (mahasiswa[mid].nim == cariNIM) {
            printf("Data Mahasiswa Ditemukan:\n");
            printf("%-20s | %-10s | %-15s | %-25s | %-20s | %-15s\n", 
                   "Nama", "NIM", "Jurusan", "Prodi", "Asal", "Tanggal Lahir");
            printf("----------------------------------------------------------------------------------------------------------------------\n");
            tampilkanMahasiswa(mahasiswa[mid]);
            found = 1;
            break;
        } else if (mahasiswa[mid].nim < cariNIM) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (!found) {
        printf("Mahasiswa dengan NIM %d tidak ditemukan.\n", cariNIM);
    }
}


// Fungsi untuk mengedit data mahasiswa
void editMahasiswa() {
    int editNIM;
    char temp[100]; // Deklarasi variabel temp di sini
    printf("Masukkan NIM mahasiswa yang akan diedit: ");
    scanf("%d", &editNIM);
    getchar(); // Membersihkan newline character yang tersisa di buffer
    int i;
    for (i = 0; i < jumlahMahasiswa; i++) {
        if (mahasiswa[i].nim == editNIM) {
            printf("Data lama mahasiswa:\n");
            printf("%-20s | %-10s | %-15s | %-25s | %-20s | %-15s\n", 
                   "Nama", "NIM", "Jurusan", "Prodi", "Asal", "Tanggal Lahir");
            printf("----------------------------------------------------------------------------------------------------------------------\n");
            tampilkanMahasiswa(mahasiswa[i]);

            printf("Masukkan data baru:\n");

            printf("Nama: ");
            fgets(temp, sizeof(temp), stdin);
            temp[strcspn(temp, "\n")] = '\0';
            free(mahasiswa[i].nama);
            mahasiswa[i].nama = strdup(temp);

            printf("Jurusan: ");
            fgets(temp, sizeof(temp), stdin);
            temp[strcspn(temp, "\n")] = '\0';
            free(mahasiswa[i].jurusan);
            mahasiswa[i].jurusan = strdup(temp);

            printf("Prodi: ");
            fgets(temp, sizeof(temp), stdin);
            temp[strcspn(temp, "\n")] = '\0';
            free(mahasiswa[i].prodi);
            mahasiswa[i].prodi = strdup(temp);

            printf("Asal: ");
            fgets(temp, sizeof(temp), stdin);
            temp[strcspn(temp, "\n")] = '\0';
            free(mahasiswa[i].asal);
            mahasiswa[i].asal = strdup(temp);

            printf("Tanggal Lahir (DD/MM/YYYY): ");
            fgets(temp, sizeof(temp), stdin);
            temp[strcspn(temp, "\n")] = '\0';
            free(mahasiswa[i].tanggal_lahir);
            mahasiswa[i].tanggal_lahir = strdup(temp);

            FILE *file = fopen("mahasiswa.txt", "w");
            if (file == NULL) {
                printf("Gagal membuka file.\n");
                return;
            }
            fprintf(file, "%-20s | %-10s | %-15s | %-25s | %-20s | %-15s\n", 
                    "Nama", "NIM", "Jurusan", "Prodi", "Asal", "Tanggal Lahir");
            fprintf(file, "----------------------------------------------------------------------------------------------------------------------\n");
            int j;
            for (j = 0; j < jumlahMahasiswa; j++) {
                fprintf(file, "%-20s | %-10d | %-15s | %-25s | %-20s | %-15s\n", 
                        mahasiswa[j].nama, mahasiswa[j].nim, mahasiswa[j].jurusan, mahasiswa[j].prodi, mahasiswa[j].asal,
                        mahasiswa[j].tanggal_lahir);
            }
            fclose(file);

            printf("Data mahasiswa berhasil diedit.\n");
            return;
        }
    }
    printf("Mahasiswa dengan NIM %d tidak ditemukan.\n", editNIM);
}



// Fungsi untuk menghapus data mahasiswa berdasarkan NIM
void hapusMahasiswa() {
    int hapusNIM;
    printf("Masukkan NIM mahasiswa yang akan dihapus: ");
    scanf("%d", &hapusNIM);
    int i, j, ditemukan = 0;
    for (i = 0; i < jumlahMahasiswa; i++) {
        if (mahasiswa[i].nim == hapusNIM) {
            ditemukan = 1;
            free(mahasiswa[i].nama);
            free(mahasiswa[i].jurusan);
            free(mahasiswa[i].prodi);
            free(mahasiswa[i].asal);
            free(mahasiswa[i].tanggal_lahir);
            for (j = i; j < jumlahMahasiswa - 1; j++) {
                mahasiswa[j] = mahasiswa[j + 1];
            }
            jumlahMahasiswa--;
            break;
        }
    }
    if (!ditemukan) {
        printf("Mahasiswa dengan NIM %d tidak ditemukan.\n", hapusNIM);
        return;
    }

    // Memperbarui file mahasiswa.txt
    FILE *file = fopen("mahasiswa.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    fprintf(file, "%-20s | %-10s | %-15s | %-25s | %-20s | %-15s\n", 
            "Nama", "NIM", "Jurusan", "Prodi", "Asal", "Tanggal Lahir");
    fprintf(file, "----------------------------------------------------------------------------------------------------------------------\n");
    for (i = 0; i < jumlahMahasiswa; i++) {
        fprintf(file, "%-20s | %-10d | %-15s | %-25s | %-20s | %-15s\n", 
                mahasiswa[i].nama, mahasiswa[i].nim, mahasiswa[i].jurusan, mahasiswa[i].prodi, mahasiswa[i].asal,
                mahasiswa[i].tanggal_lahir);
    }
    fclose(file);

    printf("Data mahasiswa berhasil dihapus.\n");
}

void lihatMahasiswa() {
    if (jumlahMahasiswa == 0) {
        printf("Tidak ada data mahasiswa.\n");
        return;
    }

    printf("%-20s | %-10s | %-15s | %-25s | %-20s | %-15s\n", 
           "Nama", "NIM", "Jurusan", "Prodi", "Asal", "Tanggal Lahir");
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    int i;
    for (i = 0; i < jumlahMahasiswa; i++) {
        printf("%-20s | %-10d | %-15s | %-25s | %-20s | %-15s\n", 
               mahasiswa[i].nama, mahasiswa[i].nim, mahasiswa[i].jurusan, mahasiswa[i].prodi, mahasiswa[i].asal,
               mahasiswa[i].tanggal_lahir);
    }
}


// Fungsi untuk menyimpan semua data mahasiswa ke file
void simpanKeFile() {
    FILE *file = fopen("mahasiswa.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    fprintf(file, "%-20s | %-10s | %-15s | %-25s | %-20s | %-15s\n", 
            "Nama", "NIM", "Jurusan", "Prodi", "Asal", "Tanggal Lahir");
    fprintf(file, "----------------------------------------------------------------------------------------------------------------------\n");
    int i;
    for (i = 0; i < jumlahMahasiswa; i++) {
        fprintf(file, "%-20s | %-10d | %-15s | %-25s | %-20s | %-15s\n", 
                mahasiswa[i].nama, mahasiswa[i].nim, mahasiswa[i].jurusan, mahasiswa[i].prodi, mahasiswa[i].asal,
                mahasiswa[i].tanggal_lahir);
    }
    fclose(file);
    printf("Data mahasiswa berhasil disimpan ke file.\n");
}

int main() {
    muatDariFile();
    int pilihan;
    int cariNIM; // Deklarasi variabel dilakukan di sini
    do {
        printf("\nMenu Utama:\n");
        printf("1. Tambah Data Mahasiswa\n");
        printf("2. Cari Data Mahasiswa\n");
        printf("3. Edit Data Mahasiswa\n");
        printf("4. Lihat Data Mahasiswa\n");
        printf("5. Hapus Data Mahasiswa\n");
        printf("6. Simpan Data ke File\n");
        printf("7. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambahMahasiswa();
                break;
            case 2:
                printf("Masukkan NIM untuk mencari data mahasiswa: ");
                scanf("%d", &cariNIM); // Penugasan variabel dilakukan di sini
                cariMahasiswa(cariNIM);
                break;
            case 3:
                editMahasiswa();
                break;
            case 4:
                lihatMahasiswa();
                break;
            case 5:
                hapusMahasiswa();
                break;
            case 6:
                simpanKeFile();
                break;
            case 7:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 7);

    // Bebaskan memori yang telah dialokasikan
    int i;
    for (i = 0; i < jumlahMahasiswa; i++) {
        free(mahasiswa[i].nama);
        free(mahasiswa[i].jurusan);
        free(mahasiswa[i].prodi);
        free(mahasiswa[i].asal);
        free(mahasiswa[i].tanggal_lahir);
    }

    return 0;
}


