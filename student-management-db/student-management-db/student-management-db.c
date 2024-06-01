#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <mysql.h>
#include <windows.h>
#include "loading.h"
#include "displayMessage.h"

// Define ANSI escape codes for text colors
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// MySQL connection information
#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "student_management"

struct Mahasiswa {
    char* nama;
    int nim;
    char* jurusan;
    char* prodi;
    char* asal;
    char* tanggal_lahir;
    struct Mahasiswa* next; // Pointer ke next node
};

struct Mahasiswa* head = NULL; // Head dari linked list

struct user {
    char username[50];
    char password[50];
};

MYSQL* conn;

// Fungsi untuk menghubungkan ke database MySQL
void connectToDatabase() {
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        exit(1);
    }
}

void closeDatabaseConnection() {
    mysql_close(conn);
}

void getPassword(char* password) {
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
        }
        else {
            password[i++] = ch;
            printf("*");
        }
    }

    password[i] = '\0';  // Menambahkan karakter null di akhir string
}

void registerAccount() {
    struct user usr;

    system("cls");

    displayRegisterMessage();
    printf("\t\t\t\t\tEnter your username:\t");
    scanf("%s", usr.username);
    printf("\t\t\t\t\tEnter your new password:\t");
    getPassword(usr.password);

    connectToDatabase();

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')", usr.username, usr.password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        printf("\n\n\t\t\t\t\tUsername already exists. Please choose a different one.\n");
    }
    else {
        printf("\n\n\t\t\t\t\tAccount successfully registered");
    }

    closeDatabaseConnection();

    displayReturnMessage();
    loading(3);
    system("cls");
}

void loginAccount() {
    struct user usr;
    char username[50], password[50];

    system("cls");

    displayMenuLogin();
    printf("\n\t\t\t\t\t\t\t\t" ANSI_COLOR_RED "M E N U   L O G I N" ANSI_COLOR_RESET "\n");
    printf("\t\t\t\t\t\t" ANSI_COLOR_RED "S I L A H K A N  M A S U K K A N  A K U N  A N D A" ANSI_COLOR_RESET "\n\n");
    printf("\n\t\t\t\t\t\t\t\tUsername: ");
    scanf("%s", username);
    printf("\t\t\t\t\t\t\t\tPassword: ");
    getPassword(password);

    connectToDatabase();

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username='%s' AND password='%s'", username, password);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    else {
        MYSQL_RES* res = mysql_store_result(conn);
        if (res == NULL) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        }

        int num_rows = mysql_num_rows(res);
        if (num_rows > 0) {
            printf("\n\n\t\t\t\t\t\t\t\tWelcome %s", username);
        }
        else {
            printf("\n\n\t\t\t\t\t\t\tInvalid username or password.\n");
        }
        mysql_free_result(res);
    }

    closeDatabaseConnection();

    printf("\n\t\t\t\t\t\t\t\tContinue to the main menu");
    loading(3);
    system("cls");
}

// Fungsi untuk load data dari database
void loadData() {
    connectToDatabase();

    if (mysql_query(conn, "SELECT * FROM mahasiswa")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    int num_fields = mysql_num_fields(res);
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(res))) {
        struct Mahasiswa* newMahasiswa = (struct Mahasiswa*)malloc(sizeof(struct Mahasiswa));
        newMahasiswa->nama = strdup(row[1]);
        newMahasiswa->nim = atoi(row[2]);
        newMahasiswa->jurusan = strdup(row[3]);
        newMahasiswa->prodi = strdup(row[4]);
        newMahasiswa->asal = strdup(row[5]);
        newMahasiswa->tanggal_lahir = strdup(row[6]);
        newMahasiswa->next = NULL;

        if (head == NULL) {
            head = newMahasiswa;
        }
        else {
            struct Mahasiswa* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newMahasiswa;
        }
    }

    mysql_free_result(res);
    closeDatabaseConnection();

    printf("\t\t\t\t\t\t\tData mahasiswa berhasil dimuat dari database.\n");
}

// Fungsi untuk menyimpan data ke dalam database
void simpanKeDatabase() {
    connectToDatabase();

    struct Mahasiswa* current = head;
    while (current != NULL) {
        char query[512];
        snprintf(query, sizeof(query),
            "INSERT INTO mahasiswa (nama, nim, jurusan, prodi, asal, tanggal_lahir) VALUES ('%s', '%d', '%s', '%s', '%s', '%s')"
            "ON DUPLICATE KEY UPDATE nama='%s', jurusan='%s', prodi='%s', asal='%s', tanggal_lahir='%s'",
            current->nama, current->nim, current->jurusan, current->prodi, current->asal, current->tanggal_lahir,
            current->nama, current->jurusan, current->prodi, current->asal, current->tanggal_lahir);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        }
        current = current->next;
    }

    closeDatabaseConnection();
    printf("\t\t\t\t\t\t\tData telah tersimpan di database.\n");
}

void tambahMahasiswa() {
    struct Mahasiswa* newMahasiswa = (struct Mahasiswa*)malloc(sizeof(struct Mahasiswa));
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
    newMahasiswa->nama[strcspn(newMahasiswa->nama, "\n")] = '\0'; // Menghapus newline character dari input

    printf("\t\t\t\t\t\t\tNIM: ");
    scanf("%d", &newMahasiswa->nim);

    printf("\t\t\t\t\t\t\tJurusan: ");
    getchar(); // Membersihkan newline character yang tersisa di buffer
    fgets(newMahasiswa->jurusan, 100, stdin);
    newMahasiswa->jurusan[strcspn(newMahasiswa->jurusan, "\n")] = '\0'; // Menghapus newline character dari input

    printf("\t\t\t\t\t\t\tProdi: ");
    fgets(newMahasiswa->prodi, 100, stdin);
    newMahasiswa->prodi[strcspn(newMahasiswa->prodi, "\n")] = '\0'; // Menghapus newline character dari input

    printf("\t\t\t\t\t\t\tAsal: ");
    fgets(newMahasiswa->asal, 100, stdin);
    newMahasiswa->asal[strcspn(newMahasiswa->asal, "\n")] = '\0'; // Menghapus newline character dari input

    printf("\t\t\t\t\t\t\tTanggal Lahir (YYYY-MM-DD): ");
    fgets(newMahasiswa->tanggal_lahir, 20, stdin);
    newMahasiswa->tanggal_lahir[strcspn(newMahasiswa->tanggal_lahir, "\n")] = '\0'; // Menghapus newline character dari input

    if (head == NULL) {
        head = newMahasiswa;
    }
    else {
        struct Mahasiswa* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newMahasiswa;
    }

    printf("\t\t\t\t\t\t\tMahasiswa berhasil ditambahkan.\n");

    // Simpan data ke database
    simpanKeDatabase();
}

void hapusMahasiswa() {
    if (head == NULL) {
        printf("\t\t\t\t\t\t\tTidak ada data mahasiswa yang tersimpan.\n");
        return;
    }

    int nim;
    printf("\t\t\t\t\t\t\tMasukkan NIM mahasiswa yang akan dihapus: ");
    scanf("%d", &nim);

    struct Mahasiswa* current = head;
    struct Mahasiswa* previous = NULL;

    while (current != NULL && current->nim != nim) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("\t\t\t\t\t\t\tMahasiswa dengan NIM %d tidak ditemukan.\n", nim);
        return;
    }

    if (previous == NULL) {
        head = current->next;
    }
    else {
        previous->next = current->next;
    }

    connectToDatabase();
    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM mahasiswa WHERE nim='%d'", nim);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    closeDatabaseConnection();

    free(current->nama);
    free(current->jurusan);
    free(current->prodi);
    free(current->asal);
    free(current->tanggal_lahir);
    free(current);

    printf("\t\t\t\t\t\t\tMahasiswa berhasil dihapus.\n");
}

void tampilkanDataMahasiswa() {
    if (head == NULL) {
        printf("\t\t\t\t\t\t\tTidak ada data mahasiswa yang tersimpan.\n");
        return;
    }

    struct Mahasiswa* current = head;
    printf("\t\t\t\t\t\t\tData mahasiswa yang tersimpan:\n");
    while (current != NULL) {
        printf("\t\t\t\t\t\t\tNama: %s, NIM: %d, Jurusan: %s, Prodi: %s, Asal: %s, Tanggal Lahir: %s\n",
            current->nama, current->nim, current->jurusan, current->prodi, current->asal, current->tanggal_lahir);
        current = current->next;
    }
}

void simpanKeFile() {
    FILE* file = fopen("data_mahasiswa.txt", "w");
    if (file == NULL) {
        printf("\t\t\t\t\t\t\tGagal membuka file untuk menulis data.\n");
        return;
    }

    struct Mahasiswa* current = head;
    while (current != NULL) {
        fprintf(file, "%s\n%d\n%s\n%s\n%s\n%s\n", current->nama, current->nim, current->jurusan, current->prodi, current->asal, current->tanggal_lahir);
        current = current->next;
    }

    fclose(file);
    printf("\t\t\t\t\t\t\tData mahasiswa berhasil disimpan ke file.\n");
}

void loadDariFile() {
    FILE* file = fopen("data_mahasiswa.txt", "r");
    if (file == NULL) {
        printf("\t\t\t\t\t\t\tGagal membuka file untuk membaca data.\n");
        return;
    }

    while (!feof(file)) {
        struct Mahasiswa* newMahasiswa = (struct Mahasiswa*)malloc(sizeof(struct Mahasiswa));
        newMahasiswa->nama = malloc(100 * sizeof(char));
        newMahasiswa->jurusan = malloc(100 * sizeof(char));
        newMahasiswa->prodi = malloc(100 * sizeof(char));
        newMahasiswa->asal = malloc(100 * sizeof(char));
        newMahasiswa->tanggal_lahir = malloc(20 * sizeof(char));
        newMahasiswa->next = NULL;

        fscanf(file, "%[^\n]\n", newMahasiswa->nama);
        fscanf(file, "%d\n", &newMahasiswa->nim);
        fscanf(file, "%[^\n]\n", newMahasiswa->jurusan);
        fscanf(file, "%[^\n]\n", newMahasiswa->prodi);
        fscanf(file, "%[^\n]\n", newMahasiswa->asal);
        fscanf(file, "%[^\n]\n", newMahasiswa->tanggal_lahir);

        if (head == NULL) {
            head = newMahasiswa;
        }
        else {
            struct Mahasiswa* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newMahasiswa;
        }
    }

    fclose(file);
    printf("\t\t\t\t\t\t\tData mahasiswa berhasil dimuat dari file.\n");
}

int main() {
    int pilihan;

    while (1) {
        system("cls");

        displayMainMenu();
        printf("\t\t\t\t\t\t\tMENU UTAMA:\n");
        printf("\t\t\t\t\t\t\t1. Register Account\n");
        printf("\t\t\t\t\t\t\t2. Login Account\n");
        printf("\t\t\t\t\t\t\t3. Load Data dari Database\n");
        printf("\t\t\t\t\t\t\t4. Tambah Data Mahasiswa\n");
        printf("\t\t\t\t\t\t\t5. Hapus Data Mahasiswa\n");
        printf("\t\t\t\t\t\t\t6. Tampilkan Data Mahasiswa\n");
        printf("\t\t\t\t\t\t\t7. Simpan Data ke File\n");
        printf("\t\t\t\t\t\t\t8. Load Data dari File\n");
        printf("\t\t\t\t\t\t\t9. Keluar\n");
        printf("\t\t\t\t\t\t\tMasukkan pilihan Anda: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
        case 1:
            registerAccount();
            break;
        case 2:
            loginAccount();
            break;
        case 3:
            loadData();
            break;
        case 4:
            tambahMahasiswa();
            break;
        case 5:
            hapusMahasiswa();
            break;
        case 6:
            tampilkanDataMahasiswa();
            break;
        case 7:
            simpanKeFile();
            break;
        case 8:
            loadDariFile();
            break;
        case 9:
            exit(0);
        default:
            printf("\t\t\t\t\t\t\tPilihan tidak valid. Silakan coba lagi.\n");
            break;
        }

        printf("\n\n\t\t\t\t\t\t\tTekan sembarang tombol untuk kembali ke menu utama...");
        getch();
    }

    return 0;
}
