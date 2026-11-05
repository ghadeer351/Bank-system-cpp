# Bank Management System

A Windows console-based bank management system developed in **C++** using object-oriented programming. The application provides client management, transactions, user permissions, transfer history, and currency conversion.

> **Project status:** Educational portfolio project. It is intended for learning and demonstration, not for real financial activity.

## Features

- User login and permission-based access
- Create, list, search, update, and delete bank clients
- Deposit and withdraw operations
- Transfer money between accounts
- Transaction and transfer history
- User management and access permissions
- Currency listing, lookup, rate updates, and conversion
- File-based data persistence

## Tech Stack

- C++
- Object-Oriented Programming
- STL
- File handling with `fstream`
- Visual Studio 2022 / MSVC v143

## Requirements

- Windows 10 or later
- Visual Studio 2022
- **Desktop development with C++** workload
- MSVC v143 build tools and a Windows 10 SDK

This project uses Visual Studio-specific features such as `__declspec(property)` and Windows console commands, so it is configured for the MSVC toolchain rather than a generic cross-platform compiler.

## Run the Application

1. Download the repository using **Code → Download ZIP**, or clone it:
   ```bash
   git clone https://github.com/ghadeer351/Bank-system-cpp.git
   ```
2. Open `Bank system course10.sln` in Visual Studio 2022.
3. If Visual Studio asks to retarget the Windows SDK, select an installed Windows 10 SDK.
4. In the toolbar, select **Debug** and **x64**.
5. In Solution Explorer, right-click the project and choose **Set as Startup Project**.
6. Build with **Build → Build Solution** (or `Ctrl+Shift+B`).
7. Run without the debugger using **Debug → Start Without Debugging** (or `Ctrl+F5`).

### Important: Working Directory

The program reads and writes its text data files using relative paths. Set the working directory to the repository folder:

1. Right-click the project → **Properties**.
2. Open **Configuration Properties → Debugging**.
3. Set **Working Directory** to:
   ```text
   $(ProjectDir)
   ```
4. Click **Apply**.

This ensures that the sample data files are found and that changes are written beside the project files.

## Demo Login

Use this sample administrator account to enter the application:

| Field | Value |
|---|---|
| Username | `Admin` |
| Password | `Demo123` |

The repository includes fictional sample client records to help you explore the menus. These credentials and records are for local demonstration only.

## Quick Test Walkthrough

After logging in:

1. Choose **1 — Show Client List** to view the sample accounts.
2. Choose **5 — Find Client** and search for account `A1001`.
3. Open **6 — Transactions** and try a deposit or withdrawal on a sample account.
4. Try a transfer from `A1001` to `A1002`.
5. Open **9 — Currency Exchange** to browse currencies and try a conversion.
6. Open **7 — Manage Users** to inspect user-management options.
7. Use **10 — Logout** to return to the login screen.

For a more detailed manual test checklist, see [TESTING.md](TESTING.md).

## Project Structure

- `Bank system course10.cpp` — application entry point
- `cls*.h` — domain classes, screens, validation, and application logic
- `Global.h` — shared current-user state
- `Users.txt` — demo user records
- `Clients.txt` — fictional demo client records
- `Currencies.txt` — currency data used by the application
- `TransferLog.txt` — transfer history
- `LoginRegister.txt` — login activity metadata (no passwords are recorded)

## Data and Security Notes

- The application stores data in local text files. Running it changes those files.
- The included people, contact details, account numbers, PINs, and credentials are fictional demo data.
- The password transformation in this educational code is **not secure password hashing**.
- Client PINs and financial records are stored in plain text. Do not enter real personal, account, or financial information.
- Currency rates are sample values stored locally; they are not live market rates.
- This project is not suitable for production banking or real transactions.

## Author

**Ghadeer Debo** · [GitHub Profile](https://github.com/ghadeer351)
