/*
Nama Program: student_management.c
Deskripsi	: Program student management system (Tugas Besar Struktur Data)
Nama Author	: Zulvikar Kharisma Nur M.
NIM			: 4.33.23.2.26
Tanggal		: 27/05/2024
Github Repo : https://github.com/DycandX/Student-Management
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "loading.h"
#include "displayMessage.h"

struct Mahasiswa {
    char *nama;
    int nim;
    char *jurusan;
    char *prodi;
    char *asal;
    char *tanggal_lahir;
    struct Mahasiswa *next; // Pointer ke next node
};

struct Mahasiswa *head = NULL; // Head dari linked list

// Fungsi untuk load data dari file mahasiswa.txt
void loadData() {
    FILE *file = fopen("mahasiswa.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    char line[256];
    
    while (fgets(line, sizeof(line), file) != NULL) {
        // Membersihkan karakter newline jika ada
        line[strcspn(line, "\r\n")] = '\0';

        // Memecah baris berdasarkan delimiter "|"
        char *token = strtok(line, "|");

        // Membuat node baru untuk setiap mahasiswa
        struct Mahasiswa *newMahasiswa = (struct Mahasiswa*)malloc(sizeof(struct Mahasiswa));
        newMahasiswa->nama = strdup(token);
        token = strtok(NULL, "|");
        newMahasiswa->nim = atoi(token);
        token = strtok(NULL, "|");
        newMahasiswa->jurusan = strdup(token);
        token = strtok(NULL, "|");
        newMahasiswa->prodi = strdup(token);
        token = strtok(NULL, "|");
        newMahasiswa->asal = strdup(token);
        token = strtok(NULL, "|");
        newMahasiswa->tanggal_lahir = strdup(token);
        newMahasiswa->next = NULL;

        // Menambahkan node baru ke linked list
        if (head == NULL) {
            head = newMahasiswa;
        } else {
            struct Mahasiswa *temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newMahasiswa;
        }
    }
    fclose(file);

    printf("Data mahasiswa berhasil dimuat dari file.\n");
}

// Fungsi untuk menyimpan data ke dalam file mahasiswa.txt
void simpanKeFile() {
    FILE *file = fopen("mahasiswa.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    struct Mahasiswa *current = head;
    while (current != NULL) {
        // Memeriksa apakah semua atribut memiliki nilai sebelum menuliskannya
        if (current->nama != NULL && current->jurusan != NULL && current->prodi != NULL &&
            current->asal != NULL && current->tanggal_lahir != NULL) {
            fprintf(file, "%s|%d|%s|%s|%s|%s\n",
                    current->nama, current->nim, current->jurusan, 
                    current->prodi, current->asal, current->tanggal_lahir);
        } else {
            // Jika ada data yang kurang lengkap, tulis baris kosong
            fprintf(file, "\n");
        }
        current = current->next;
    }
    fclose(file);
}

// Fungsi untuk menambah data ke linked list
void tambahMahasiswa() {
    struct Mahasiswa *newMahasiswa = (struct Mahasiswa*)malloc(sizeof(struct Mahasiswa));
    newMahasiswa->nama = malloc(100 * sizeof(char));
    newMahasiswa->jurusan = malloc(100 * sizeof(char));
    newMahasiswa->prodi = malloc(100 * sizeof(char));
    newMahasiswa->asal = malloc(100 * sizeof(char));
    newMahasiswa->tanggal_lahir = malloc(20 * sizeof(char));
    newMahasiswa->next = NULL;

    printf("Masukkan data mahasiswa:\n");
    printf("Nama: ");
    getchar(); // Membersihkan newline character yang tersisa di buffer
    fgets(newMahasiswa->nama, 100, stdin);
    newMahasiswa->nama[strcspn(newMahasiswa->nama, "\n")] = '\0'; // Remove newline character

    printf("NIM: ");
    scanf("%d", &newMahasiswa->nim);
    getchar(); // Membersihkan newline character yang tersisa di buffer

    printf("Jurusan: ");
    fgets(newMahasiswa->jurusan, 100, stdin);
    newMahasiswa->jurusan[strcspn(newMahasiswa->jurusan, "\n")] = '\0';

    printf("Prodi: ");
    fgets(newMahasiswa->prodi, 100, stdin);
    newMahasiswa->prodi[strcspn(newMahasiswa->prodi, "\n")] = '\0';

    printf("Asal: ");
    fgets(newMahasiswa->asal, 100, stdin);
    newMahasiswa->asal[strcspn(newMahasiswa->asal, "\n")] = '\0';

    printf("Tanggal Lahir (DD/MM/YYYY): ");
    fgets(newMahasiswa->tanggal_lahir, 20, stdin);
    newMahasiswa->tanggal_lahir[strcspn(newMahasiswa->tanggal_lahir, "\n")] = '\0';

    if (head == NULL) {
        head = newMahasiswa;
    } else {
        struct Mahasiswa *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newMahasiswa;
    }

    simpanKeFile(); // Menyimpan data ke file setelah menambahkan data baru
    printf("Data mahasiswa berhasil ditambahkan.\n");
}

// Fungsi untuk menampilkan data menjadi table
void tampilkanSemuaMahasiswa() {
    struct Mahasiswa *current = head;
    int nomorUrutan = 1; // Inisialisasi nomor urutan

    if (current == NULL) {
        printf("Tidak ada data mahasiswa yang tersedia.\n");
        return;
    }
    printf("\nDaftar Mahasiswa:\n");
    printf("%-5s | %-20s | %-10s | %-20s | %-10s | %-20s | %-15s\n", 
           "No.", "Nama", "NIM", "Jurusan", "Prodi", "Asal", "Tanggal Lahir");
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    while (current != NULL) {
        printf("%-5d | %-20s | %-10d | %-20s | %-10s | %-20s | %-15s\n", 
               nomorUrutan, current->nama, current->nim, current->jurusan, 
               current->prodi, current->asal, current->tanggal_lahir);
        current = current->next;
        nomorUrutan++; // Menambah nomor urutan setiap kali iterasi
    }
}

// Fungsi untuk mengedit data
void editMahasiswa() {
    int editNIM;
    printf("Masukkan NIM mahasiswa yang akan diedit: ");
    scanf("%d", &editNIM);
    getchar(); // Membersihkan newline character yang tersisa di buffer

    struct Mahasiswa *current = head;
    while (current != NULL) {
        if (current->nim == editNIM) {
            printf("\nData lama mahasiswa:\n");
            printf("%-4s | %-20s | %-10s | %-20s | %-10s | %-20s | %-15s\n", 
                   "No.", "Nama", "NIM", "Jurusan", "Prodi", "Asal", "Tanggal Lahir");
            printf("------------------------------------------------------------------------------------------------------------------------------\n");
            // Tampilkan data lama mahasiswa
            printf("%-4d | %-20s | %-10d | %-20s | %-10s | %-20s | %-15s\n", 
                   1, current->nama, current->nim, current->jurusan, 
                   current->prodi, current->asal, current->tanggal_lahir);

            printf("\nMasukkan data baru:\n");

            char temp[100]; // Variabel temp digunakan untuk menyimpan input sementara

            printf("Nama: ");
            fgets(temp, sizeof(temp), stdin);
            temp[strcspn(temp, "\n")] = '\0';
            free(current->nama);
            current->nama = strdup(temp);

            printf("Jurusan: ");
            fgets(temp, sizeof(temp), stdin);
            temp[strcspn(temp, "\n")] = '\0';
            free(current->jurusan);
            current->jurusan = strdup(temp);

            printf("Prodi: ");
            fgets(temp, sizeof(temp), stdin);
            temp[strcspn(temp, "\n")] = '\0';
            free(current->prodi);
            current->prodi = strdup(temp);

            printf("Asal: ");
            fgets(temp, sizeof(temp), stdin);
            temp[strcspn(temp, "\n")] = '\0';
            free(current->asal);
            current->asal = strdup(temp);

            printf("Tanggal Lahir (DD/MM/YYYY): ");
            fgets(temp, sizeof(temp), stdin);
            temp[strcspn(temp, "\n")] = '\0';
            free(current->tanggal_lahir);
            current->tanggal_lahir = strdup(temp);

            printf("Data mahasiswa berhasil diedit.\n");

            // Simpan perubahan ke dalam file
            simpanKeFile();

            return;
        }
        current = current->next;
    }
    printf("Mahasiswa dengan NIM %d tidak ditemukan.\n", editNIM);
}


// Fungsi untuk menghapus data dari linked list
void hapusMahasiswa() {
    int hapusNIM;
    printf("Masukkan NIM mahasiswa yang akan dihapus: ");
    scanf("%d", &hapusNIM);
    getchar(); // Membersihkan newline character yang tersisa di buffer

    struct Mahasiswa *temp = head, *prev = NULL;

    // Jika head node itu sendiri yang perlu dihapus
    if (temp != NULL && temp->nim == hapusNIM) {
        head = temp->next; // Changed head
        free(temp->nama);
        free(temp->jurusan);
        free(temp->prodi);
        free(temp->asal);
        free(temp->tanggal_lahir);
        free(temp);
        printf("Data mahasiswa berhasil dihapus.\n");
        simpanKeFile();
        return;
    }

    // Cari node yang akan dihapus, simpan pointer ke node sebelumnya
    while (temp != NULL && temp->nim != hapusNIM) {
        prev = temp;
        temp = temp->next;
    }

    // Jika NIM tidak ditemukan
    if (temp == NULL) {
        printf("Mahasiswa dengan NIM %d tidak ditemukan.\n", hapusNIM);
        return;
    }

    // Hapus node
    prev->next = temp->next;
    free(temp->nama);
    free(temp->jurusan);
    free(temp->prodi);
    free(temp->asal);
    free(temp->tanggal_lahir);
    free(temp);

    printf("Data mahasiswa berhasil dihapus.\n");
    simpanKeFile();
}

// Fungsi untuk pencarian data menggunakan sequential search
void cariMahasiswa(int cariNIM) {
    struct Mahasiswa *current = head;
    int nomorUrutan = 1;
    int found = 0;
    printf("%-5s | %-20s | %-10s | %-20s | %-10s | %-20s | %-15s\n", 
           "No.", "Nama", "NIM", "Jurusan", "Prodi", "Asal", "Tanggal Lahir");
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    while (current != NULL) {
        if (current->nim == cariNIM) {
            printf("%-5d | %-20s | %-20d | %-10s | %-25s | %-20s | %-15s\n", 
               nomorUrutan, current->nama, current->nim, current->jurusan, 
               current->prodi, current->asal, current->tanggal_lahir);
            found = 1;
            printf("\nData yang kamu cari terdapat pada baris ke %d.\n", nomorUrutan);
            break;
        }
        current = current->next;
        nomorUrutan++;
    }

    if (!found) {
        printf("Mahasiswa dengan NIM %d tidak ditemukan.\n", cariNIM);
    }
}

// Fungsi untuk menyortir data pada linked list menggunakan insertion sort
void insertionSort() {
    if (head == NULL || head->next == NULL) {
        return; // Tidak perlu menyortir jika list kosong atau hanya satu elemen
    }

    struct Mahasiswa *sorted = NULL; // Membuat list kosong untuk sorted
    struct Mahasiswa *current = head;

    while (current != NULL) {
        struct Mahasiswa *next = current->next;

        if (sorted == NULL || sorted->nim >= current->nim) {
            current->next = sorted;
            sorted = current;
        } else {
            struct Mahasiswa *temp = sorted;
            while (temp->next != NULL && temp->next->nim < current->nim) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }

    head = sorted;
    printf("Data mahasiswa berhasil diurutkan berdasarkan NIM.\n");
}


// Fungsi Utama
int main() {
    int pilihan;
    
    system("cls");
    
    displayWelcomeMessage();
    loading_bar(5); // Loading page at the start
    
    while (1) {
        system("cls"); 
        printf("\nMenu:\n");
        printf("1. Muat data dari file\n");
        printf("2. Tambah data mahasiswa\n");
        printf("3. Cari data mahasiswa\n");
        printf("4. Edit data mahasiswa\n");
        printf("5. Hapus Data Mahasiswa\n");
        printf("6. Tampilkan semua data mahasiswa\n");
        printf("7. Simpan data ke file\n");
        printf("8. Urutkan data mahasiswa berdasarkan NIM\n"); // Tambahkan opsi ini
        printf("0. Keluar\n");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                loadData();
                break;
            case 2:
                tambahMahasiswa();
                break;
            case 3: {
                int cariNIM;
                tampilkanSemuaMahasiswa();
                printf("\nMasukkan NIM yang akan dicari: ");
                scanf("%d", &cariNIM);
                printf("\n");
                cariMahasiswa(cariNIM);
                break;
            }
            case 4:
                editMahasiswa();
                break;
            case 5:
                hapusMahasiswa();
                break;
            case 6:
                tampilkanSemuaMahasiswa();
                break;
            case 7:
                simpanKeFile();
                break;
            case 8:
                insertionSort();
                //simpanKeFile(); // Simpan perubahan setelah sorting
                break;
            case 0:
                exit(0);
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
        printf("\nTekan Enter untuk melanjutkan...");
        getchar(); // Menunggu input dari pengguna
        getchar(); // Menangkap karakter Enter
    }
    return 0;
}



