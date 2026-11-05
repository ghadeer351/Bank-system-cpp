# Manual Testing Guide

Use this checklist after building and launching the application in Visual Studio 2022.

## Demo Credentials

- Username: `Admin`
- Password: `Demo123`

## Sample Client Accounts

| Account Number | PIN | Initial Balance |
|---|---:|---:|
| A1001 | 1234 | 7,000 |
| A1002 | 5678 | 5,000 |
| A1003 | 2468 | 900 |

All records are fictional and intended only for local testing.

## Test Scenarios

### 1. Authentication
- [ ] Log in with the demo administrator credentials.
- [ ] Try an incorrect password and confirm that login is rejected.
- [ ] Try three failed attempts and observe the lock message.

### 2. Client Management
- [ ] List all clients.
- [ ] Find account `A1001`.
- [ ] Add a new client with a unique account number.
- [ ] Update the new client's details.
- [ ] Delete the test client.
- [ ] List clients again and confirm the changes.

### 3. Transactions
- [ ] Deposit an amount into `A1001`.
- [ ] Withdraw an amount smaller than its balance.
- [ ] Attempt to withdraw more than the available balance.
- [ ] Transfer an amount from `A1001` to `A1002`.
- [ ] Open the transfer log and inspect the recorded transfer.

### 4. Users and Permissions
- [ ] Open the user-management menu.
- [ ] Review the demo administrator account.
- [ ] Create a separate test user with limited permissions, if desired.
- [ ] Verify that restricted menu actions are denied to that user.

### 5. Currency
- [ ] List available currencies.
- [ ] Search for USD.
- [ ] Search for a currency by country.
- [ ] Use the currency calculator with the sample rates.

## Resetting the Demo Data

The application writes changes to local text files. To restore the original sample data, discard local modifications to the tracked data files from the repository root:

```bash
git restore Users.txt Clients.txt TransferLog.txt LoginRegister.txt Currencies.txt
```

This discards changes made to those files and restores the committed demo dataset. Back up any work you want to keep before running the command.

## Notes

- Run the application with the repository root as its working directory so relative data-file paths resolve correctly.
- The project is Windows/MSVC-specific.
- These are manual functional checks; they are not an automated test suite.
