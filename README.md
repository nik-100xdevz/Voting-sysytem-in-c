# Voting System

A simple command-line voting system written in C. This system allows administrators to set up elections and manage results, while students can cast their votes securely. 

---

## Features

### Admin Panel
- **Authenticate Admin**: Secure access using username and password.
- **Initiate New Election**: Configure valid user IDs, branch codes, total voters, and candidates for the election.
- **View Results**: Display vote counts for each candidate.

### Student Panel
- **Vote Casting**: Students can vote for their preferred candidate.
- **User Validation**: Validates student credentials based on the user ID format, year, and branch code.
- **Duplicate Vote Prevention**: Ensures students cannot vote more than once.

---

## How It Works

### User ID Format
The system validates student IDs based on the following format:  
`YYYYBRANCHXXXXX`  
- **YYYY**: Year of enrollment (e.g., 2023).
- **BRANCH**: Branch code (5 characters, e.g., `CSE01`).
- **XXXXX**: Unique roll number (5 digits, e.g., `00123`).

### Voting Process
1. Students log in using their user ID.
2. The system verifies eligibility based on the `year` and `branch` code.
3. Students select a candidate by entering the candidate's ID.
4. Votes are securely recorded, and the system ensures no duplicate voting.

---

## Code Overview

### File Structure
- **Voting Logic**: Contains functions for student authentication, vote casting, and results display.
- **Admin Functions**: Handles election setup and result management.

### Key Components
- `struct currentValidID`: Stores the parameters for valid user IDs.
- `typedef struct candidate`: Represents candidate details (ID, name, and votes).
- `studentVotes[]`: Tracks which students have already voted.
- Functions:
  - `extractYear`, `extractRollNo`, `checkBranchCode`: Parse and validate user IDs.
  - `authenticateAdmin`: Secures access to admin functions.
  - `initiateNewElection`: Configures election parameters.
  - `saveVote`: Records student votes.
  - `displayResults`: Displays vote counts for all candidates.

---

## Prerequisites

- **Compiler**: A C compiler (e.g., GCC).
- **Operating System**: Any OS that supports C compilation (Windows, macOS, Linux).

---

## Installation and Usage

### 1. Compile the Code
Use the following command to compile the code:
```bash
gcc -o voting_system voting_system.c
