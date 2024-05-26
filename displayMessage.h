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
    printf("\t\t\t\t\t     *************************************************************\n\n");
}
