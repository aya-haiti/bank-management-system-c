# Banking Management System in C

A console-based banking management application developed in **C**.

The project simulates the main operations of a banking system and provides separate interfaces for:

- Clients
- Employees
- Administrators

The application uses binary files for local data persistence and provides authentication, account management and transaction tracking.

---

## Project Overview

The objective of this project is to simulate the main operations of a banking information system using the C programming language.

The application includes three user roles:

### Client

Clients can authenticate using their personal identifier and code.

### Employee

Employees can access banking operations according to their permissions.

### Administrator

The administrator manages employees and accesses administrative features.

---

## Main Features

### Authentication

The application provides dedicated authentication systems for:

- Clients
- Employees
- Administrator

Passwords are entered using masked characters in the console.

---

## Client Management

The system stores information such as:

- Identifier
- First name
- Last name
- Phone number
- City
- Email
- Gender
- Account number
- RIB
- Date of birth
- Account balance

Client identifiers are validated and must contain exactly five digits.

---

## Account Management

The application manages bank accounts with:

- Unique account numbers
- Personal identifiers
- Account balance
- Banking RIB
- Personal access codes

Account numbers are validated before registration.

---

## Employee Management

The administrator can manage employee information including:

- Employee number
- First name
- Last name
- Date of birth
- Address
- Phone number
- Email
- Password

Employee numbers must be unique.

---

## Transaction Management

The system records banking transactions with information including:

- Client identifier
- Transaction amount
- New balance
- Transaction type
- Transaction date
- Transaction reason

Transactions are stored in a binary file.

---

## Transaction History

Users can search transaction history using a client identifier.

The system displays:

```text
Date | Amount | New Balance | Type | Reason


## Download (Windows)

Pre-built executables are attached to each [GitHub Release](https://github.com/aya-haiti/bank-management-system-c/releases/latest)
(built automatically by `.github/workflows/release.yml` when a `v*` tag is pushed).

1. Download `BankManagement-windows.zip` and extract it.
2. Copy `admin_credentials.example.txt` to `admin_credentials.txt` and set your own admin
   username (line 1) and password (line 2).
3. Run `BankManagement.exe` from that folder (data files `*.dat` are created next to it).

Build from source: `gcc -O2 -o BankManagement.exe main.c` (MinGW, Windows).
