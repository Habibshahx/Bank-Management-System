# Bank Management System (C)

## Introduction
The **Bank Management System** is a console-based application developed in **C** as part of the **Programming Fundamentals** course.  
This project simulates basic banking operations and demonstrates the practical use of **file handling**, **structures**, and **conditional logic** in C.

The system stores all records permanently using **binary files**, ensuring data is retained even after the program is closed.

---

## Objectives
- To understand and apply Programming Fundamentals concepts
- To implement file handling using binary files
- To design a menu-driven console application
- To simulate real-world banking operations

---

## Features
- Create and manage customer accounts
- Deposit money into customer accounts
- Withdraw money from customer accounts
- Transfer money between accounts
- Store and retrieve data using binary files (`.bin`)
- User-friendly, menu-driven interface

---

## Technologies Used
- **Programming Language:** C
- **Concepts Used:**
  - File Handling (Binary Files)
  - Structures
  - Functions
  - Conditional Statements
  - Loops

---

## Project Structure
Bank-Management-System-cpp/
├── src/
│ └── Code.cpp
├── data/
│ ├── Customer.bin
│ ├── Deposits.bin
│ ├── Withdrawals.bin
│ └── Transfers.bin
├── report/
│ └── PF Project report.docx
├── README.md
└── .gitignore

---

## ▶ How to Run the Project

### Step 1: Compile the Code
    gcc Code.c -o bank
### Step 2: Run the Program
    ./bank

---

## How the System Works
1. The user selects an option from the main menu  
2. The system performs the requested banking operation  
3. Data is saved or updated in binary files  
4. Records are retrieved when needed  
5. The program continues until the user exits  

---

## Data Storage
- Customer information is stored in `Customer.bin`
- Deposit records are stored in `Deposits.bin`
- Withdrawal records are stored in `Withdrawals.bin`
- Transfer records are stored in `Transfers.bin`

---

## Academic Information
- **Course Name:** Programming Fundamentals  
- **Project Type:** Semester Project  
- **Institution:** COMSATS University Islamabad  
- **Campus:** Abbottabad  

---

## Author
**Habib Shah**  
BS Software Engineering  

---

## Conclusion
This project demonstrates the effective application of Programming Fundamentals concepts in C.  
It provides a strong foundation for understanding file handling and building real-world console-based applications.
