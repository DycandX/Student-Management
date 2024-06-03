#include <stdio.h>

// Define ANSI escape codes for text colors
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void displayWelcomeMessage() {
    printf("\n\n\n");
    printf("\t\t   _____ _______ _    _ _____  ______ _   _ _______   __  __          _   _          _____ ______ __  __ ______ _   _ _______ \n");
    printf("\t\t  / ____|__   __| |  | |  __ \\|  ____| \\ | |__   __| |  \\/  |   /\\   | \\ | |   /\\   / ____|  ____|  \\/  |  ____| \\ | |__   __|\n");
    printf("\t\t | (___    | |  | |  | | |  | | |__  |  \\| |  | |    | \\  / |  /  \\  |  \\| |  /  \\ | |  __| |__  | \\  / | |__  |  \\| |  | |   \n");
    printf("\t\t  \\___ \\   | |  | |  | | |  | |  __| | . ` |  | |    | |\\/| | / /\\ \\ | . ` | / /\\ \\| | |_ |  __| | |\\/| |  __| | . ` |  | |   \n");
    printf("\t\t  ____) |  | |  | |__| | |__| | |____| |\\  |  | |    | |  | |/ ____ \\| |\\  |/ ____ \\ |__| | |____| |  | | |____| |\\  |  | |   \n");
    printf("\t\t |_____/   |_|   \\____/|_____/|______|_| \\_|  |_|    |_|  |_/_/    \\_\\_| \\_/_/    \\_\\_____|______|_|  |_|______|_| \\_|  |_|   \n");
    printf("\n");
    printf("\t\t\t\t\t     *************************************************************\n");
    printf("\t\t\t\t\t     ******** " ANSI_COLOR_RED  "Welcome to Simple Student Management System" ANSI_COLOR_RESET " ********\n" );
    printf("\t\t\t\t\t     ********************** " ANSI_COLOR_RED "By Zulvikar.exe" ANSI_COLOR_RESET " **********************\n");
    printf("\t\t\t\t\t     *************************** " ANSI_COLOR_RED "TI-1C" ANSI_COLOR_RESET " ***************************\n");
    printf("\t\t\t\t\t     *************************************************************\n");
    printf("\t\t\t\t\t     ******* " ANSI_COLOR_RED "https://github.com/DycandX/Student-Management" ANSI_COLOR_RESET " *******\n");
    printf("\t\t\t\t\t     *************************************************************\n\n");
    
}

void displayInitialMessage() {
    printf("\n\n\n");
    printf("\t\t   _____ _______ _    _ _____  ______ _   _ _______   __  __          _   _          _____ ______ __  __ ______ _   _ _______ \n");
    printf("\t\t  / ____|__   __| |  | |  __ \\|  ____| \\ | |__   __| |  \\/  |   /\\   | \\ | |   /\\   / ____|  ____|  \\/  |  ____| \\ | |__   __|\n");
    printf("\t\t | (___    | |  | |  | | |  | | |__  |  \\| |  | |    | \\  / |  /  \\  |  \\| |  /  \\ | |  __| |__  | \\  / | |__  |  \\| |  | |   \n");
    printf("\t\t  \\___ \\   | |  | |  | | |  | |  __| | . ` |  | |    | |\\/| | / /\\ \\ | . ` | / /\\ \\| | |_ |  __| | |\\/| |  __| | . ` |  | |   \n");
    printf("\t\t  ____) |  | |  | |__| | |__| | |____| |\\  |  | |    | |  | |/ ____ \\| |\\  |/ ____ \\ |__| | |____| |  | | |____| |\\  |  | |   \n");
    printf("\t\t |_____/   |_|   \\____/|_____/|______|_| \\_|  |_|    |_|  |_/_/    \\_\\_| \\_/_/    \\_\\_____|______|_|  |_|______|_| \\_|  |_|   \n");
    printf("\n");
    printf("\t\t\t\t\t     *************************************************************\n");
    printf("\t\t\t\t\t     ******** " ANSI_COLOR_RED  "Welcome to Simple Student Management System" ANSI_COLOR_RESET " ********\n" );
    printf("\t\t\t\t\t     ********************** " ANSI_COLOR_RED "By Zulvikar.exe" ANSI_COLOR_RESET " **********************\n");
    printf("\t\t\t\t\t     *************************** " ANSI_COLOR_RED "TI-1C" ANSI_COLOR_RESET " ***************************\n");
    printf("\t\t\t\t\t     *************************************************************\n");
    printf("\t\t\t\t\t     ******* " ANSI_COLOR_RED "https://github.com/DycandX/Student-Management" ANSI_COLOR_RESET " *******\n");
    printf("\t\t\t\t\t     *************************************************************\n\n");
}

//Fungsi untuk menampilkan Register message
void displayRegisterMessage() {
    printf("\n");
    printf("\t\t\t\t\t    ____   _____   ____  ___  ____   _____  _____  ____   \n");
    printf("\t\t\t\t\t   |  _ \\ | ____| / ___||_ _|/ ___| |_   _|| ____||  _ \\  \n");
    printf("\t\t\t\t\t   | |_) ||  _|  | |  _  | | \\___ \\   | |  |  _|  | |_) | \n");
    printf("\t\t\t\t\t   |  _ < | |___ | |_| | | |  ___) |  | |  | |___ |  _ <  \n");
    printf("\t\t\t\t\t   |_| \\_\\|_____| \\____||___||____/   |_|  |_____||_| \\_\\ \n\n");
    printf("\t\t\t\t\t************************************************************\n");
    printf("\t\t\t\t\t***************" ANSI_COLOR_RED " D A F T A R  A K U N  B A R U " ANSI_COLOR_RESET "**************\n");
    printf("\t\t\t\t\t************************************************************\n\n\n");
}

//Fungsi untuk menampilkan Menu Login
void displayMenuLogin() {
    printf("\n");
    printf("\t\t\t\t\t  __  __  _____  _   _  _   _   _       ___    ____  ___  _   _ \n");
    printf("\t\t\t\t\t |  \\/  || ____|| \\ | || | | | | |     / _ \\  / ___||_ _|| \\ | |\n");
    printf("\t\t\t\t\t | |\\/| ||  _|  |  \\| || | | | | |    | | | || |  _  | | |  \\| |\n");
    printf("\t\t\t\t\t | |  | || |___ | |\\  || |_| | | |___ | |_| || |_| | | | | |\\  |\n");
    printf("\t\t\t\t\t |_|  |_||_____||_| \\_| \\___/  |_____| \\___/  \\____||___||_| \\_|\n");
}

//Fungsi untuk menampilkan return message
void displayReturnMessage() {
    printf("\n\t\t\t\t\t\t\t  Return to the login menu\n");
}

void displayMainMenuLogo() {
    printf("\n");
    printf("\t\t\t\t\t\t  __  __          _____ _   _   __  __ ______ _   _ _    _ \n");
    printf("\t\t\t\t\t\t |  \\/  |   /\\   |_   _| \\ | | |  \\/  |  ____| \\ | | |  | |\n");
    printf("\t\t\t\t\t\t | \\  / |  /  \\    | | |  \\| | | \\  / | |__  |  \\| | |  | |\n");
    printf("\t\t\t\t\t\t | |\\/| | / /\\ \\   | | | . ` | | |\\/| |  __| | . ` | |  | |\n");
    printf("\t\t\t\t\t\t | |  | |/ ____ \\ _| |_| |\\  | | |  | | |____| |\\  | |__| |\n");
    printf("\t\t\t\t\t\t |_|  |_/_/    \\_\\_____|_| \\_| |_|  |_|______|_| \\_|\\____/ \n");
    printf("\n\t\t\t\t\t\t\t\t" ANSI_COLOR_RED "Student Management System" ANSI_COLOR_RESET "");
}


//Fungsi untuk menampilkan thanks message
void displayThanksMessage() {
    printf("\n\n");
    printf("\t\t\t\t\t _____  _   _     _     _   _  _  __ __   __  ___   _   _ \n");
    printf("\t\t\t\t\t|_   _|| | | |   / \\   | \\ | || |/ / \\ \\ / / / _ \\ | | | |\n");
    printf("\t\t\t\t\t  | |  | |_| |  / _ \\  |  \\| || ' /   \\ V / | | | || | | |\n");
    printf("\t\t\t\t\t  | |  |  _  | / ___ \\ | |\\  || . \\    | |  | |_| || |_| |\n");
    printf("\t\t\t\t\t  |_|  |_| |_|/_/   \\_\\|_| \\_||_|\\_\\   |_|   \\___/  \\___/ \n\n");
    printf("\t\t\t\t\t  **********************************************************\n");
    printf("\t\t\t\t\t  *************" ANSI_COLOR_RED " Thank you for using the program" ANSI_COLOR_RESET " ************\n");
    printf("\t\t\t\t\t  **********************************************************\n");
}
