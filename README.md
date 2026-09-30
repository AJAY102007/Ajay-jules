# ATM Management System

A simple, beginner-friendly C application that simulates basic operations of a real ATM terminal. Designed to be clean, readable, and easy for a first-year engineering student to understand.

## Features
1. **PIN Login**: Secure authentication with hidden input masking when run interactively. Default PIN is `1234`. Terminates session if an incorrect PIN is provided.
2. **ATM Main Menu**: User-friendly menu loop with options to perform transactions.
3. **Check Balance**: Displays account balance initialized at `Rs. 10,000.00` formatted with 2 decimal places.
4. **Deposit Money**: Validates deposit amount (> 0) and updates total balance.
5. **Withdraw Money**: Validates withdrawal amount and ensures sufficient balance before cash disburse.
6. **Change PIN**: Validates and updates to a new 4-digit PIN for session security.
7. **Exit**: Safe program termination with a thank-you banner.

## File Structure
- `main.c`: Complete C source code containing ATM logic and interactive menu options.
- `Makefile`: Build configuration script for compiling `main.c`.
- `test_atm.py`: Automated Python test script verifying all 10 core test cases.
- `README.md`: Project documentation and setup guide.

## How to Compile & Run

### Prerequisites
- GCC Compiler (`gcc`)
- Make (`make`)

### Building the Project
Compile the program using `make`:
```bash
make
```

### Running the Application
Run the executable:
```bash
./atm_system
```

### Cleaning Build Artifacts
To remove compiled executables:
```bash
make clean
```

## Running Automated Tests
To verify all test cases automatically:
```bash
python3 test_atm.py
```
