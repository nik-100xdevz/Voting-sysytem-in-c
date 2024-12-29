#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct currentValidID {
    int year;
    char branch[6];
    int totalVoters;
};

typedef struct candidate {
    int cid;
    char cname[20];
    int votes;
} CANDIDATE;

// GLOBALS --------------------------------------------------------
struct currentValidID currentValidID;  // Stores current valid user ID parameters
CANDIDATE candidateArray[20];         // Information of all candidates
int numberOfCandidates = 0;           // Total number of candidates
char studentVotes[200];               // Tracks votes given by students
//-----------------------------------------------------------------

// Extract year from userID
int extractYear(char userID[15]) {
    int year = 0;
    for (int i = 0; i < 4; i++) {
        year = (year * 10) + (userID[i] - '0');
    }
    return year;
}

// Extract roll number from userID
int extractRollNo(char userID[15]) {
    int rollno = 0;
    for (int i = 9; i < 14; i++) {
        rollno = (rollno * 10) + (userID[i] - '0');
    }
    return rollno;
}

// Check branch code
int checkBranchCode(char userID[15]) {
    char branchCode[6];
    for (int i = 4; i < 9; i++) {
        branchCode[i - 4] = userID[i];
    }
    branchCode[5] = '\0';  // Null-terminate the string
    return strcmp(branchCode, currentValidID.branch) == 0;
}

// Authenticate admin
int authenticateAdmin() {
    char username[15], password[6];

    printf("\nEnter username: ");
    scanf("%s", username);
    if (strcmp(username, "Admin") != 0) {
        return 0;
    }

    printf("Enter Password: ");
    for (int i = 0; i < 5; i++) {
        password[i] = getchar();
        printf("*");
    }
    password[5] = '\0';

    return strcmp(password, "admiN") == 0;
}

// Admin: Initiate new election
void initiateNewElection() {
    printf("\nEnter valid year (YYYY): ");
    scanf("%d", &currentValidID.year);

    printf("Enter valid branch code (5 characters): ");
    scanf("%s", currentValidID.branch);

    printf("Enter total number of voters: ");
    scanf("%d", &currentValidID.totalVoters);

    printf("Enter number of candidates: ");
    scanf("%d", &numberOfCandidates);

    for (int i = 0; i < numberOfCandidates; i++) {
        printf("\nEnter candidate ID for candidate %d: ", i + 1);
        scanf("%d", &candidateArray[i].cid);
        printf("Enter candidate name: ");
        scanf("%s", candidateArray[i].cname);
        candidateArray[i].votes = 0;
    }

    printf("\nElection setup complete!\n");
}

// Save vote
void saveVote(char userID[15], int candidateID) {
    if (studentVotes[extractRollNo(userID)] == '1') {
        printf("\nYou have already voted!\n");
        return;
    }

    for (int i = 0; i < numberOfCandidates; i++) {
        if (candidateArray[i].cid == candidateID) {
            candidateArray[i].votes++;
            studentVotes[extractRollNo(userID)] = '1';  // Mark as voted
            printf("\nVote successfully cast!\n");
            return;
        }
    }

    printf("\nInvalid candidate ID!\n");
}

// Display results
void displayResults() {
    printf("\n--- Election Results ---\n");
    for (int i = 0; i < numberOfCandidates; i++) {
        printf("Candidate ID: %d, Name: %s, Votes: %d\n",
               candidateArray[i].cid, candidateArray[i].cname, candidateArray[i].votes);
    }
}

// Main function
int main() {
    memset(studentVotes, '0', sizeof(studentVotes));  // Initialize votes array

    while (1) {
        int choice;
        printf("\n--- Voting System ---\n");
        printf("1. Admin Panel\n");
        printf("2. Student Panel\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (authenticateAdmin()) {
                    printf("\nWelcome to the Admin Panel!\n");
                    printf("1. Initiate New Election\n");
                    printf("2. View Results\n");
                    printf("Enter your choice: ");
                    int adminChoice;
                    scanf("%d", &adminChoice);

                    if (adminChoice == 1) {
                        initiateNewElection();
                    } else if (adminChoice == 2) {
                        displayResults();
                    } else {
                        printf("\nInvalid choice!\n");
                    }
                } else {
                    printf("\nInvalid Admin credentials!\n");
                }
                break;

            case 2: {
                char userID[15];
                int candidateID;

                printf("\nEnter your User ID: ");
                scanf("%s", userID);

                if (extractYear(userID) != currentValidID.year || !checkBranchCode(userID)) {
                    printf("\nInvalid User ID!\n");
                    break;
                }

                printf("\nCandidates:\n");
                for (int i = 0; i < numberOfCandidates; i++) {
                    printf("Candidate ID: %d, Name: %s\n",
                           candidateArray[i].cid, candidateArray[i].cname);
                }

                printf("\nEnter the Candidate ID to vote for: ");
                scanf("%d", &candidateID);
                saveVote(userID, candidateID);
                break;
            }

            case 3:
                printf("\nExiting the system...\n");
                exit(0);

            default:
                printf("\nInvalid choice, please try again.\n");
        }
    }

    return 0;
}
