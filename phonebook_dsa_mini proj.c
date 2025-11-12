#include <stdio.h>
#include <string.h>

#define MAX 100

struct Contact {
    int id;
    char firstName[30];
    char lastName[30];
    char gender;
    char phone[15];
    char city[30];
};

struct Contact contacts[MAX];
int count = 0;

// Function declarations
void addContact();
void displayContacts();
void searchByName();
void searchByNumber();
void searchByCity();
void updateContact();
void deleteContact();
void deleteAllContacts();
void bubbleSortByName();
int linearSearchByPhone(char phone[]);

// Function to add a new contact
void addContact() {
    if (count == MAX) {
        printf("Phonebook full!\n");
        return;
    }

    struct Contact newContact;
    newContact.id = count + 1;

    printf("\n>>> Add New Contact <<<\n");
    printf("Enter the first name: ");
    scanf(" %[^\n]", newContact.firstName);
    printf("Enter the last name: ");
    scanf(" %[^\n]", newContact.lastName);
    printf("Enter the city name: ");
    scanf(" %[^\n]", newContact.city);
    printf("Enter the gender [M/F]: ");
    scanf(" %c", &newContact.gender);
    printf("Enter the phone number [+91]: ");
    scanf(" %s", newContact.phone);

    contacts[count++] = newContact;
    printf("\nSuccess: Contact details added.\n");
}

// Function to display all contacts
void displayContacts() {
    if (count == 0) {
        printf("No contacts to display.\n");
        return;
    }

    bubbleSortByName();
    printf("\n| ID | Name               | Gender | Phone        | City        |\n");
    printf("____________________________________________________________________\n");
    for (int i = 0; i < count; i++) {
        printf("| %-2d | %-17s | %-6c | %-12s | %-10s |\n", 
            contacts[i].id,
            strcat(strcat(contacts[i].firstName, " "), contacts[i].lastName),
            contacts[i].gender,
            contacts[i].phone,
            contacts[i].city);
    }
}

// Function to update a contact
void updateContact() {
    char phone[15];
    printf("\nEnter the phone number to update: [+91] ");
    scanf(" %s", phone);

    int index = linearSearchByPhone(phone);
    if (index == -1) {
        printf("Contact not found.\n");
        return;
    }

    printf("\nEditing Contact: %s %s\n", contacts[index].firstName, contacts[index].lastName);
    printf("Enter new city: ");
    scanf(" %[^\n]", contacts[index].city);
    printf("Enter new phone: ");
    scanf(" %s", contacts[index].phone);
    printf("Enter new gender [M/F]: ");
    scanf(" %c", &contacts[index].gender);

    printf("Contact updated successfully!\n");
}

// Function to search by name
void searchByName() {
    char name[30];
    printf("\nEnter the first or last name: ");
    scanf(" %[^\n]", name);

    printf("\n| ID | Name               | Gender | Phone        | City        |\n");
    printf("____________________________________________________________________\n");

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcasecmp(contacts[i].firstName, name) == 0 || strcasecmp(contacts[i].lastName, name) == 0) {
            printf("| %-2d | %-17s | %-6c | %-12s | %-10s |\n", 
                contacts[i].id,
                strcat(strcat(contacts[i].firstName, " "), contacts[i].lastName),
                contacts[i].gender,
                contacts[i].phone,
                contacts[i].city);
            found = 1;
        }
    }

    if (!found) printf("No matching contact found.\n");
}

// Function to search by phone number
void searchByNumber() {
    char phone[15];
    printf("\nEnter the phone number [+91]: ");
    scanf(" %s", phone);

    int index = linearSearchByPhone(phone);
    if (index == -1) {
        printf("No contact found with that number.\n");
        return;
    }

    printf("\n| ID |Name               | Gender | Phone        | City        |\n");
    printf("_______________________________________________________________________\n");
    printf("| %-2d | %-17s | %-6c | %-12s | %-10s |\n",
        contacts[index].id,
        strcat(strcat(contacts[index].firstName, " "), contacts[index].lastName),
        contacts[index].gender,
        contacts[index].phone,
        contacts[index].city);
}

// Function to search by city
void searchByCity() {
    char city[30];
    printf("\nEnter the city name: ");
    scanf(" %[^\n]", city);

    printf("\n| ID | Name               | Gender | Phone        | City        |\n");
    printf("____________________________________________________________________\n");

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcasecmp(contacts[i].city, city) == 0) {
            printf("| %-2d | %-17s | %-6c | %-12s | %-10s |\n",
                contacts[i].id,
                strcat(strcat(contacts[i].firstName, " "), contacts[i].lastName),
                contacts[i].gender,
                contacts[i].phone,
                contacts[i].city);
            found = 1;
        }
    }

    if (!found) printf("No contacts found in this city.\n");
}

// Function to delete a contact by phone number
void deleteContact() {
    char phone[15];
    printf("\nEnter the phone number to delete: [+91] ");
    scanf(" %s", phone);

    int index = linearSearchByPhone(phone);
    if (index == -1) {
        printf("Contact not found.\n");
        return;
    }

    printf("\nType 'CONFIRM' to delete this contact: ");
    char confirm[10];
    scanf(" %s", confirm);

    if (strcasecmp(confirm, "CONFIRM") == 0) {
        for (int i = index; i < count - 1; i++) {
            contacts[i] = contacts[i + 1];
        }
        count--;
        printf("Chosen contact deleted successfully.\n");
    } else {
        printf("Deletion cancelled.\n");
    }
}

// Function to delete all contacts
void deleteAllContacts() {
    count = 0;
    printf("All contacts deleted successfully.\n");
}

// Bubble sort by first name
void bubbleSortByName() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcasecmp(contacts[j].firstName, contacts[j + 1].firstName) > 0) {
                struct Contact temp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = temp;
            }
        }
    }
}

// Linear search by phone number
int linearSearchByPhone(char phone[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(contacts[i].phone, phone) == 0)
            return i;
    }
    return -1;
}

// MAIN MENU
int main() {
    int choice;

    while (1) {
        printf("\n>>> Admin Panel <<<\n");
        printf("_______________________________\n");
        printf("[1] Add New Contact.\n");
        printf("[2] Update Contact.\n");
        printf("[3] Display All Contacts.\n");
        printf("[4] Search By Name.\n");
        printf("[5] Search By Number.\n");
        printf("[6] Search By City.\n");
        printf("[7] Delete Contact.\n");
        printf("[8] Delete All Contacts.\n");
        printf("[9] Exit.\n");
        printf("=================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1: addContact(); break;
            case 2: updateContact(); break;
            case 3: displayContacts(); break;
            case 4: searchByName(); break;
            case 5: searchByNumber(); break;
            case 6: searchByCity(); break;
            case 7: deleteContact(); break;
            case 8: deleteAllContacts(); break;
            case 9: 
                printf("Exiting... Goodbye!\n");
                return 0;
            default: printf("Invalid choice! Try again.\n");
        }

        printf("\nPress any key to continue...\n");
        getchar(); // pause
    }
}
