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

// Define ANSI escape codes for text colors
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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

struct user {
    char username[50];
    char password[50];
};

void getPassword(char *password) {
    int i = 0;
    char ch;

    while (1) {
        ch = _getch(); 
        if (ch == 13)    // ASCII 13 adalah enter
            break;
        else if (ch == 8) {  // ASCII 8 adalah backspace
            if (i > 0) {
                i--;
                printf("\b \b");  // Menghapus karakter dan mundur satu langkah
            }
        } else {
            password[i++] = ch;
            printf("*");
        }
    }

    password[i] = '\0';  // Menambahkan karakter null di akhir string
}

void registerAccount() {
    struct user usr;
    FILE *fp;
    char filename[50];

    system("cls");

    displayRegisterMessage();
    printf("\t\t\t\t\tEnter your username:\t");
    scanf("%s", usr.username);
    printf("\t\t\t\t\tEnter your new password:\t");
    getPassword(usr.password);

    fp = fopen("users.txt", "a"); // Buka file untuk menambahkan data baru

    if (fp != NULL) {
        // Periksa apakah username sudah ada sebelumnya
        if (checkExistingUsername(usr.username)) {
            printf("\n\n\t\t\t\t\tUsername already exists. Please choose a different one.\n");
        } else {
            // Tulis informasi pengguna ke dalam file users.txt
            fprintf(fp, "%s|%s\n", usr.username, usr.password);
            printf("\n\n\t\t\t\t\tAccount successfully registered");
        }
        fclose(fp);
    } else {
        printf("\n\nSomething went wrong, please try again");
    }
    displayReturnMessage();
    loading(3);
    system("cls");
}

void displayMainMenu() {
	displayInitialMessage();
    printf("\n\t\t\t\t\t\t\t\tSilakan pilih:\n");
    printf("\t\t\t\t\t\t\t\t1. Registrasi\n");
    printf("\t\t\t\t\t\t\t\t2. Login\n");
    printf("\t\t\t\t\t\t\t\t0. Keluar\n");
    printf("\t\t\t\t\t\t\t\tMasukkan pilihan Anda: ");
}

void loginAccount() {
    struct user usr;
    FILE *fp;
    char username[50], password[50];
    char line[100]; // Menampung satu baris dari file
    char *token;

    system("cls");

    displayMenuLogin();
    printf("\n\t\t\t\t\t\t\t\t" ANSI_COLOR_RED "M E N U   L O G I N" ANSI_COLOR_RESET "\n");
    printf("\t\t\t\t\t\t" ANSI_COLOR_RED "S I L A H K A N  M A S U K K A N  A K U N  A N D A" ANSI_COLOR_RESET "\n\n");
    printf("\n\t\t\t\t\t\t\t\tUsername: ");
    scanf("%s", username);
    printf("\t\t\t\t\t\t\t\tPassword: ");
    getPassword(password);

    fp = fopen("users.txt", "r");

    if (fp == NULL) {
        printf("\n\t\t\t\t\t\tError opening file.\n");
    } else {
        int found = 0;
        while (fgets(line, sizeof(line), fp)) {
            // Menghilangkan karakter baru di akhir baris
            line[strcspn(line, "\n")] = '\0';
            
            // Memisahkan username dan password dari baris yang dibaca
            token = strtok(line, "|");
            strcpy(usr.username, token);
            token = strtok(NULL, "|");
            strcpy(usr.password, token);

            // Membandingkan username dan password dengan informasi dari file
            if (strcmp(username, usr.username) == 0 && strcmp(password, usr.password) == 0) {
                printf("\n\n\t\t\t\t\t\t\t\tWelcome %s", username);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("\n\n\t\t\t\t\t\t\tInvalid username or password.\n");
            printf("\n\t\t\t\t\t\t\tPress Enter to return to login menu");
            getchar(); // Menunggu input dari pengguna
            getchar(); // Menangkap karakter Enter
            fclose(fp);
            system("cls");
            displayMainMenu(); // Menampilkan menu awal setelah login gagal
            char input[10];
            scanf("%s", input);
            if (isdigit(input[0])) {
                int opt = atoi(input);  // Mengubah string menjadi integer
                switch (opt) {
                    case 1:
                        loading(2); // Loading after each option
                        registerAccount();
                        break;
                    case 2:
                        loading(2);
                        loginAccount();
                        break;
                    case 0:
                        loading(2);
                        displayThanksMessage();
                        printf("\n\n\t\t\t\t\tExiting the program. Thank you!\n\n\n\n");
                        exit(0);
                    default:
                        loading(2);
                        printf("\n\t\t\t\t\t\t      Invalid option\n");
                        displayReturnMessage();
                        // Meminta pengguna untuk memasukkan input lagi
                        loading(2);
                        break;
                }
            } else {
                loading(2);
                printf("\n\t\t\t\t\t    Invalid input. Please enter a number.\n");
                displayReturnMessage();
                // Meminta pengguna untuk memasukkan input lagi
                loading(2);
            }
            return;
        }
        fclose(fp);
    }
    printf("\n\t\t\t\t\t\t\t\tContinue to the main menu");
    loading(3);
    system("cls");
}

int checkExistingUsername(char *username) {
    FILE *fp;
    char line[100];
    char *token;

    fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("\n\t\t\t\t\tError opening file.\n");
        return 0; // Return false karena tidak bisa memeriksa
    }

    while (fgets(line, sizeof(line), fp)) {
        // Memisahkan username dari baris yang dibaca
        token = strtok(line, "|");
        if (strcmp(username, token) == 0) {
            fclose(fp);
            return 1; // Return true jika username sudah ada
        }
    }

    fclose(fp);
    return 0; // Return false jika username tidak ada
}


// Fungsi untuk load data dari file mahasiswa.txt
void loadData() {
    FILE *file = fopen("mahasiswa.txt", "r");
    if (file == NULL) {
        printf("\t\t\t\t\t\t\tGagal membuka file.\n");
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

    printf("\t\t\t\t\t\t\tData mahasiswa berhasil dimuat dari file.\n");
}

// Fungsi untuk menyimpan data ke dalam file mahasiswa.txt
void simpanKeFile() {
    FILE *file = fopen("mahasiswa.txt", "w");
    if (file == NULL) {
        printf("\t\t\t\t\t\t\tGagal membuka file.\n");
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
    printf("\t\t\t\t\t\t\tData telah tersimpan di file mahasiswa.txt.\n");
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

    printf("\t\t\t\t\t\t\tMasukkan data mahasiswa:\n");
    printf("\t\t\t\t\t\t\tNama: ");
    getchar(); // Membersihkan newline character yang tersisa di buffer
    fgets(newMahasiswa->nama, 100, stdin);
    newMahasiswa->nama[strcspn(newMahasiswa->nama, "\n")] = '\0'; // Remove newline character

    printf("\t\t\t\t\t\t\tNIM: ");
    scanf("%d", &newMahasiswa->nim);
    getchar(); // Membersihkan newline character yang tersisa di buffer

    printf("\t\t\t\t\t\t\tJurusan: ");
    fgets(newMahasiswa->jurusan, 100, stdin);
    newMahasiswa->jurusan[strcspn(newMahasiswa->jurusan, "\n")] = '\0';

    printf("\t\t\t\t\t\t\tProdi: ");
    fgets(newMahasiswa->prodi, 100, stdin);
    newMahasiswa->prodi[strcspn(newMahasiswa->prodi, "\n")] = '\0';

    printf("\t\t\t\t\t\t\tAsal: ");
    fgets(newMahasiswa->asal, 100, stdin);
    newMahasiswa->asal[strcspn(newMahasiswa->asal, "\n")] = '\0';

    printf("\t\t\t\t\t\t\tTanggal Lahir (DD/MM/YYYY): ");
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
    printf("\t\t\t\t\t\t\tData mahasiswa berhasil ditambahkan.\n");
}

// Fungsi untuk menampilkan data menjadi table
void tampilkanSemuaMahasiswa() {
    struct Mahasiswa *current = head;
    int nomorUrutan = 1; // Inisialisasi nomor urutan

    if (current == NULL) {
        printf("\t\t\t\t\t\t\tTidak ada data mahasiswa yang tersedia.\n");
        return;
    }
    printf("\t\t\t\t\t\t\t\n\nDaftar Mahasiswa:\n\n");
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
    printf("\t\t\t\t\t\t\tMasukkan NIM mahasiswa yang akan diedit: ");
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

            printf("\t\t\t\t\t\t\t\nMasukkan data baru:\n");

            char temp[100]; // Variabel temp digunakan untuk menyimpan input sementara

            printf("\t\t\t\t\t\t\tNama: ");
            fgets(temp, sizeof(temp), stdin);
            temp[strcspn(temp, "\n")] = '\0';
            free(current->nama);
            current->nama = strdup(temp);

            printf("\t\t\t\t\t\t\tJurusan: ");
            fgets(temp, sizeof(temp), stdin);
            temp[strcspn(temp, "\n")] = '\0';
            free(current->jurusan);
            current->jurusan = strdup(temp);

            printf("\t\t\t\t\t\t\tProdi: ");
            fgets(temp, sizeof(temp), stdin);
            temp[strcspn(temp, "\n")] = '\0';
            free(current->prodi);
            current->prodi = strdup(temp);

            printf("\t\t\t\t\t\t\tAsal: ");
            fgets(temp, sizeof(temp), stdin);
            temp[strcspn(temp, "\n")] = '\0';
            free(current->asal);
            current->asal = strdup(temp);

            printf("\t\t\t\t\t\t\tTanggal Lahir (DD/MM/YYYY): ");
            fgets(temp, sizeof(temp), stdin);
            temp[strcspn(temp, "\n")] = '\0';
            free(current->tanggal_lahir);
            current->tanggal_lahir = strdup(temp);

            printf("\t\t\t\t\t\t\tData mahasiswa berhasil diedit.\n");

            // Simpan perubahan ke dalam file
            simpanKeFile();

            return;
        }
        current = current->next;
    }
    printf("\t\t\t\t\t\t\tMahasiswa dengan NIM %d tidak ditemukan.\n", editNIM);
}


// Fungsi untuk menghapus data dari linked list
void hapusMahasiswa() {
    int hapusNIM;
    printf("\t\t\t\t\t\t\tMasukkan NIM mahasiswa yang akan dihapus: ");
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
        printf("\t\t\t\t\t\t\tData mahasiswa berhasil dihapus.\n");
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
        printf("\t\t\t\t\t\t\tMahasiswa dengan NIM %d tidak ditemukan.\n", hapusNIM);
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

    printf("\t\t\t\t\t\t\tData mahasiswa berhasil dihapus.\n");
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
            printf("%-5d | %-20s | %-10d | %-20s | %-10s | %-20s | %-15s\n", 
               nomorUrutan, current->nama, current->nim, current->jurusan, 
               current->prodi, current->asal, current->tanggal_lahir);
            found = 1;
            printf("\t\t\t\t\t\t\t\nData yang kamu cari terdapat pada baris ke %d.\n", nomorUrutan);
            break;
        }
        current = current->next;
        nomorUrutan++;
    }

    if (!found) {
        printf("\t\t\t\t\t\t\tMahasiswa dengan NIM %d tidak ditemukan.\n", cariNIM);
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
    printf("\n\n\t\t\t\t\tData mahasiswa berhasil diurutkan berdasarkan NIM.\n");
}


// Fungsi Utama
int main() {
    int pilihan;
    char input[10];
	char username[50];
    
    system("cls");
    
    displayWelcomeMessage();
    loading_bar(5); // Loading page at the start
    
    while (1) { // Loop utama
        // Menampilkan opsi untuk login atau registrasi
        displayMainMenu();
        scanf("%s", input);

        // Memeriksa apakah input berupa angka
        if (isdigit(input[0])) {
            int opt = atoi(input);  // Mengubah string menjadi integer
            switch (opt) {
                case 1:
                    loading(2); // Loading after each option
                    registerAccount();
                    break;
                case 2:
                    loading(2);
                    loginAccount();
                    // Setelah login berhasil, masuk ke menu utama
                    while (1) { // Loop untuk menu utama
                        system("cls"); 
                        displayMainMenuLogo();
                        printf("\n\n\t\t\t\t\t\t\t1. Muat data dari file\n");
                        printf("\t\t\t\t\t\t\t2. Tambah data mahasiswa\n");
                        printf("\t\t\t\t\t\t\t3. Cari data mahasiswa\n");
                        printf("\t\t\t\t\t\t\t4. Edit data mahasiswa\n");
                        printf("\t\t\t\t\t\t\t5. Hapus Data Mahasiswa\n");
                        printf("\t\t\t\t\t\t\t6. Tampilkan semua data mahasiswa\n");
                        printf("\t\t\t\t\t\t\t7. Simpan data ke file\n");
                        printf("\t\t\t\t\t\t\t8. Urutkan data mahasiswa berdasarkan NIM\n");
                        printf("\t\t\t\t\t\t\t0. Keluar\n");
                        printf("\n\t\t\t\t\t\t\tMasukkan pilihan Anda: ");
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
                                printf("\t\t\t\t\t\t\t\nMasukkan NIM yang akan dicari: ");
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
                                loading(2);
                   				 displayThanksMessage();
                    			printf("\n\n\t\t\t\t\tExiting the program. Thank you!\n\n\n\n");
                    			exit(0);
                            default:
                                printf("\t\t\t\t\t\t\tPilihan tidak valid. Silakan coba lagi.\n");
                        }
                        printf("\n\t\t\t\t\t\t\tTekan Enter untuk melanjutkan...");
                        getchar(); // Menunggu input dari pengguna
                        getchar(); // Menangkap karakter Enter
                    }
                    break; // Keluar dari loop menu utama
                case 0:
                    loading(2);
                    displayThanksMessage();
                    printf("\n\n\t\t\t\t\t\t\tExiting the program. Thank you!\n\n\n\n");
                    exit(0);
                default:
                    loading(2);
                    printf("\n\t\t\t\t\t\t      Invalid option\n");
                    displayReturnMessage();
                    // Meminta pengguna untuk memasukkan input lagi
                    loading(2);
                    break;
            }
        } else {
            loading(2);
            printf("\n\t\t\t\t\t    Invalid input. Please enter a number.\n");
            displayReturnMessage();
            // Meminta pengguna untuk memasukkan input lagi
            loading(2);
        }
    }
    
    return 0;
}

