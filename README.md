# Bank Management System

A Windows console-based bank management system built with **C++ and Object-Oriented Programming (OOP)**. It provides client management, banking transactions, user accounts and permissions, transfer history, and currency conversion.

This project was built as a practical way to apply OOP, work with classes, organize a multi-feature application, and handle persistent data using files.

> **Project status:** Educational project for learning and demonstration. It is not intended for real banking or financial activity.

## Features

### Client management
- Add new clients.
- List all clients and search by account number.
- Update client information.
- Delete client records.
- Store client details and account balances in a local file.

### Banking operations
- Deposit and withdraw money.
- Transfer money between two client accounts.
- View transaction-related screens and transfer records.
- Calculate the total balances of all clients.

### Users and permissions
- User login and logout.
- Add, update, search, list, and delete users.
- Assign permissions to application features.
- Check the current user's permissions before showing protected screens.
- Keep a login activity register.

### Currency exchange
- List and search currencies.
- Update stored exchange rates.
- Convert an amount between currencies.

## Technologies

- **C++**
- **Object-Oriented Programming**
- **STL** — including `vector` and `string`
- **File handling** — `fstream`
- **Visual Studio 2022**
- **MSVC v143**

The project uses MSVC-specific features such as `__declspec(property)` and Windows console commands, so it is configured for Windows and Visual Studio rather than a generic cross-platform compiler.

## Architecture and code organization

I organized the application around responsibilities instead of putting the whole program inside `main()`. The project is made up of small classes, with each group handling a particular part of the application.

The design is **inspired by the separation of concerns used in MVC**, but it is not a strict MVC implementation. Since this is a console application, some screen classes handle both user interaction and the flow between operations. The domain classes also handle file persistence directly; there is no separate repository or service layer yet.

### 1. Application entry point

`Bank system course10.cpp` is the starting point of the application. It starts the login flow and keeps returning to it until the user exits.

The entry point stays small. The menus, client operations, and user management are handled by their own classes.

### 2. Domain and data classes

These classes represent the main entities and the operations related to them:

| Class | Responsibility |
|---|---|
| `clsPerson` | Common personal information such as first name, last name, email, and phone |
| `clsBankClient` | Client account data, balance operations, searching, saving, and transfer-related operations |
| `clsUser` | User account data, login information, saving, and permission checks |
| `clsCurrency` | Currency information and stored exchange-rate data |

For example, `clsBankClient` contains operations such as `Find()`, `Save()`, `Deposit()`, `Withdraw()`, and `Transfer()`. This keeps client-related behavior close to the client data it operates on.

### 3. Inheritance and shared data

`clsBankClient` and `clsUser` both inherit from `clsPerson`.

This avoids repeating the same personal fields and methods in both classes. The base class keeps shared information in one place, while each derived class adds the data and behavior specific to its role.

### 4. Screen and presentation classes

The console interface is split into screen classes. Examples include:

- `clsScreen` — shared screen header and access-checking functionality.
- `clsMainScreen` — main menu and navigation to application features.
- `clsLoginScreen` and `clsLogin` — login flow.
- `clsClientListScreen` — displaying client records.
- `clsTransactionMenueScreen` and `clsTransfer` — transaction menus and transfer interaction.
- `clsManageUserScreen` — user-management screens.
- `clsCurrencyMainScreen` — currency exchange navigation.

Most screens focus on reading input, displaying information, confirming actions, and calling the relevant operations. Shared screen behavior is placed in `clsScreen` instead of being repeated across every screen.

### 5. Utilities and validation

Common helper functionality is kept in separate classes:

- `clsValidate` — reading and validating user input.
- `clsString` — string operations, including splitting stored records.
- `clsUtility` — general helper functions.
- `clsDate` — date and time operations.

This keeps repeated helper code out of the main screens and domain classes where possible.

### 6. Shared application state

`Global.h` contains the shared current-user state used by screens that need to know who is logged in. The current user is used when checking permissions and recording operations such as transfers.

This is a simple approach for a console learning project. A larger application would benefit from passing the authenticated user through clearer application-level interfaces instead of relying on global state.

## Object-Oriented Programming concepts

The project uses several OOP concepts in practical parts of the application.

### Encapsulation

Class fields are generally kept private, and public methods or getter/setter properties provide access to them.

For example, `clsPerson` stores personal information in private fields and exposes methods such as `GetFirstName()` and `SetFirstName()`. The account data in `clsBankClient` and user data in `clsUser` follow the same general idea.

### Inheritance

`clsBankClient` and `clsUser` inherit from `clsPerson`, reusing the common personal information while adding their own fields and operations.

### Abstraction

The rest of the application can use higher-level operations such as `Save()`, `Find()`, `Deposit()`, and `CheckAccessPermissions()` without needing to repeat the file-reading and record-conversion steps every time.

### Enums and controlled states

Enums are used to represent states and results, such as whether a client is being added or updated and whether a save operation succeeded or failed. Permission values are also represented as named enum constants, making checks easier to read than using unexplained numbers.

### STL

The application uses STL containers such as `vector` to load records, work with collections of clients and users, and save the updated data back to files.

> The project uses encapsulation, inheritance, and abstraction. It does not currently implement a formal polymorphic class hierarchy with virtual functions.

## Data storage

The application uses local text files instead of a database. Each class that manages persistent records is responsible for loading, converting, adding, updating, or deleting its records.

| File | Purpose |
|---|---|
| `Clients.txt` | Client and account records |
| `Users.txt` | Application user records |
| `Currencies.txt` | Currency data and exchange rates |
| `TransferLog.txt` | Transfer history |
| `LoginRegister.txt` | Login activity records |

Records are converted between text lines and C++ objects when they are loaded or saved. The project uses a separator between fields to keep the stored format simple.

This approach is suitable for a small educational application, but it does not provide the reliability, concurrency handling, or query capabilities of a database.

## Permissions

User permissions are represented with bit flags. Each permission has its own value, and the application checks whether the current user has the permission required for an operation.

The check is implemented in `clsUser::CheckAccessPermissions()`, while `clsScreen::CheckAccessRights()` is used by screens to deny access when the required permission is missing.

This keeps permission checks reusable instead of rewriting the same logic in every screen.

## Run the application

### Requirements

- Windows 10 or later
- Visual Studio 2022
- **Desktop development with C++** workload
- MSVC v143 build tools
- A Windows 10 SDK

### Steps

1. Clone the repository:

   ```bash
   git clone https://github.com/ghadeer351/Bank-system-cpp.git
   ```

2. Open `Bank system course10.sln` in Visual Studio 2022.
3. If Visual Studio asks to retarget the Windows SDK, select an installed Windows 10 SDK.
4. Select **Debug** and **x64** in the toolbar.
5. In Solution Explorer, right-click the project and select **Set as Startup Project**.
6. Build the solution using **Build → Build Solution** or `Ctrl+Shift+B`.
7. Run using **Debug → Start Without Debugging** or `Ctrl+F5`.

### Working directory

The application reads and writes its data files using relative paths. Set the project's working directory to the repository folder:

1. Right-click the project and open **Properties**.
2. Go to **Configuration Properties → Debugging**.
3. Set **Working Directory** to:

   ```text
   $(ProjectDir)
   ```

4. Apply the changes.

This allows the application to find the sample data files and write updates in the expected location.

## Demo login

The repository includes a sample administrator account:

| Field | Value |
|---|---|
| Username | `Admin` |
| Password | `Demo123` |

The included client records and account details are fictional and are intended only for testing the application locally.

## Quick walkthrough

After logging in, you can try the following:

1. Open **Show Client List** to view the sample accounts.
2. Use **Find Client** and search for account `A1001`.
3. Open **Transactions** and try a deposit or withdrawal.
4. Transfer an amount from `A1001` to `A1002`.
5. Open **Currency Exchange** and try a conversion.
6. Open **Manage Users** to explore user-management options.
7. Check the login register to view recorded login activity.

For a more detailed manual checklist, see [TESTING.md](TESTING.md).

## Current limitations and possible improvements

There are a few areas that could be improved if the project is extended:

- Replace text-file storage with a relational database.
- Move persistence code into separate repository classes.
- Separate screen interaction, application flow, and business logic more strictly.
- Use a proper password-hashing algorithm and protect sensitive account data.
- Use a fixed-precision decimal or integer representation for financial amounts instead of `float`.
- Add automated unit tests for client operations, transfers, and permission checks.
- Improve error handling for missing, malformed, or inaccessible data files.
- Replace global application state with explicit dependencies.

## Security note

This is an educational project, not a production banking system. Client PINs and financial records are stored in plain text. The password transformation used by the project is not secure password hashing. Do not use real personal information, credentials, or financial data with this application. Currency rates are sample values stored locally and are not live market rates.

## Author

**Ghadeer Debo** · [GitHub Profile](https://github.com/ghadeer351)
