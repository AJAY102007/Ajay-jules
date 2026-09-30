#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/* Function declarations */
void displayWelcomeScreen(void);
void displayMainMenu(void);
int getPinInput(const char *prompt);
void checkBalance(double balance);
void depositMoney(double *balance);
void withdrawMoney(double *balance);
void changePin(int *currentPin);
void clearInputBuffer(void);

int main(void) {
    int pin = 1234;            /* Default PIN */
    double balance = 10000.00; /* Initial balance in Rupees */
    int enteredPin;
    int choice;

    /* Display Welcome Screen */
    displayWelcomeScreen();

    /* PIN Authentication */
    enteredPin = getPinInput("Enter your 4-digit PIN: ");

    if (enteredPin != pin) {
        printf("\n====================================\n");
        printf("Incorrect PIN\n");
        printf("====================================\n");
        return 0; /* Terminate the session */
    }

    printf("\n====================================\n");
    printf("Login successful\n");
    printf("====================================\n");

    /* Main ATM Menu Loop */
    do {
        displayMainMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            /* Clear invalid input buffer safely */
            clearInputBuffer();
            printf("\nInvalid choice! Please enter a valid menu option.\n");
            continue;
        }

        switch (choice) {
            case 1:
                checkBalance(balance);
                break;
            case 2:
                depositMoney(&balance);
                break;
            case 3:
                withdrawMoney(&balance);
                break;
            case 4:
                changePin(&pin);
                break;
            case 5:
                printf("\n====================================\n");
                printf("Thank you for using the ATM!\n");
                printf("====================================\n");
                break;
            default:
                printf("\nInvalid choice! Please select an option between 1 and 5.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}

/* Display Welcome Banner */
void displayWelcomeScreen(void) {
    printf("====================================\n");
    printf("        WELCOME TO THE ATM          \n");
    printf("====================================\n");
}

/* Display Main Menu Options */
void displayMainMenu(void) {
    printf("\n====================================\n");
    printf("          ATM MANAGEMENT SYSTEM     \n");
    printf("====================================\n");
    printf("1. Check Balance\n");
    printf("2. Deposit Money\n");
    printf("3. Withdraw Money\n");
    printf("4. Change PIN\n");
    printf("5. Exit\n");
    printf("====================================\n");
}

/* Safely consume input buffer up to newline or EOF */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Securely get PIN input without echoing if in a terminal */
int getPinInput(const char *prompt) {
    int inputPin = 0;
    printf("%s", prompt);

    /* If stdin is a terminal, disable echoing for password input */
    if (isatty(STDIN_FILENO)) {
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        if (scanf("%d", &inputPin) != 1) {
            inputPin = -1;
            clearInputBuffer();
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        printf("\n");
    } else {
        if (scanf("%d", &inputPin) != 1) {
            inputPin = -1;
            clearInputBuffer();
        }
    }

    return inputPin;
}

/* Option 1: Display current balance formatted to two decimal places */
void checkBalance(double balance) {
    printf("\n====================================\n");
    printf("Current Balance = Rs. %.2f\n", balance);
    printf("====================================\n");
}

/* Option 2: Deposit money into the account */
void depositMoney(double *balance) {
    double amount;
    printf("\nEnter the amount to deposit: ");
    if (scanf("%lf", &amount) != 1) {
        clearInputBuffer();
        printf("\nInvalid deposit amount!\n");
        return;
    }

    if (amount <= 0) {
        printf("\nInvalid deposit amount! Amount must be greater than zero.\n");
    } else {
        *balance += amount;
        printf("\n====================================\n");
        printf("Deposit successful!\n");
        printf("Updated Balance = Rs. %.2f\n", *balance);
        printf("====================================\n");
    }
}

/* Option 3: Withdraw money from the account */
void withdrawMoney(double *balance) {
    double amount;
    printf("\nEnter the withdrawal amount: ");
    if (scanf("%lf", &amount) != 1) {
        clearInputBuffer();
        printf("\nInvalid withdrawal amount!\n");
        return;
    }

    if (amount <= 0) {
        printf("\nInvalid withdrawal amount! Amount must be greater than zero.\n");
    } else if (amount > *balance) {
        printf("\n====================================\n");
        printf("Insufficient balance!\n");
        printf("====================================\n");
    } else {
        *balance -= amount;
        printf("\n====================================\n");
        printf("Please collect your cash.\n");
        printf("Remaining Balance = Rs. %.2f\n", *balance);
        printf("====================================\n");
    }
}

/* Option 4: Change the 4-digit PIN */
void changePin(int *currentPin) {
    int newPin;
    newPin = getPinInput("\nEnter a new 4-digit PIN: ");

    /* Check if PIN is a valid 4-digit number (1000 to 9999) */
    if (newPin >= 1000 && newPin <= 9999) {
        *currentPin = newPin;
        printf("\n====================================\n");
        printf("PIN changed successfully!\n");
        printf("====================================\n");
    } else {
        printf("\n====================================\n");
        printf("Invalid PIN! PIN must be exactly 4 digits.\n");
        printf("====================================\n");
    }
}
