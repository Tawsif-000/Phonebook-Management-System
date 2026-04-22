#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact
{
    char name[50];
    char phone[20];
    char email[50];
    struct Contact *next;
    struct Contact *prev;
};

struct Contact *head = NULL;

/*========================================
            CREATE CONTACT
========================================*/
struct Contact* createContact()
{
    struct Contact *newNode = (struct Contact*)malloc(sizeof(struct Contact));

    printf("\nEnter Name  : ");
    scanf(" %[^\n]", newNode->name);

    printf("Enter Phone : ");
    scanf("%s", newNode->phone);

    printf("Enter Email : ");
    scanf("%s", newNode->email);

    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

/*========================================
              ADD CONTACT
========================================*/
void addContact()
{
    struct Contact *newNode = createContact();

    if(head == NULL)
    {
        head = newNode;
    }
    else
    {
        struct Contact *temp = head;

        while(temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
        newNode->prev = temp;
    }

    printf("\nContact Added Successfully!\n");
}

/*========================================
           DISPLAY CONTACTS
========================================*/
void displayContacts()
{
    struct Contact *temp = head;
    int count = 0;

    if(temp == NULL)
    {
        printf("\nNo Contacts Found.\n");
        return;
    }

    printf("\n=========== CONTACT LIST ===========\n");

    while(temp != NULL)
    {
        printf("Name  : %s\n", temp->name);
        printf("Phone : %s\n", temp->phone);
        printf("Email : %s\n", temp->email);
        printf("-----------------------------------\n");

        count++;
        temp = temp->next;
    }

    printf("Total Contacts : %d\n", count);
}

/*========================================
           DISPLAY REVERSE
========================================*/
void displayReverse()
{
    struct Contact *temp = head;

    if(temp == NULL)
    {
        printf("\nNo Contacts Found.\n");
        return;
    }

    while(temp->next != NULL)
        temp = temp->next;

    printf("\n======= CONTACT LIST REVERSE =======\n");

    while(temp != NULL)
    {
        printf("Name  : %s\n", temp->name);
        printf("Phone : %s\n", temp->phone);
        printf("Email : %s\n", temp->email);
        printf("-----------------------------------\n");

        temp = temp->prev;
    }
}

/*========================================
             SEARCH CONTACT (BY NAME)
========================================*/
void searchContact()
{
    char name[50];
    struct Contact *temp = head;

    if(temp == NULL)
    {
        printf("\nNo Contacts Found.\n");
        return;
    }

    printf("\nEnter Name To Search : ");
    scanf(" %[^\n]", name);

    while(temp != NULL)
    {
        if(strcmp(temp->name, name) == 0)
        {
            printf("\nContact Found!\n");
            printf("Name  : %s\n", temp->name);
            printf("Phone : %s\n", temp->phone);
            printf("Email : %s\n", temp->email);
            return;
        }
        temp = temp->next;
    }

    printf("\nContact Not Found.\n");
}

/*========================================
             UPDATE CONTACT
========================================*/
void updateContact()
{
    char phone[20];
    struct Contact *temp = head;

    printf("\nEnter Phone To Update : ");
    scanf("%s", phone);

    while(temp != NULL)
    {
        if(strcmp(temp->phone, phone) == 0)
        {
            printf("\nEnter New Name  : ");
            scanf(" %[^\n]", temp->name);

            printf("Enter New Phone : ");
            scanf("%s", temp->phone);

            printf("Enter New Email : ");
            scanf("%s", temp->email);

            printf("\nContact Updated Successfully!\n");
            return;
        }
        temp = temp->next;
    }

    printf("\nContact Not Found.\n");
}

/*========================================
             DELETE CONTACT
========================================*/
void deleteContact()
{
    char phone[20];
    struct Contact *temp = head;

    printf("\nEnter Phone To Delete : ");
    scanf("%s", phone);

    while(temp != NULL)
    {
        if(strcmp(temp->phone, phone) == 0)
        {
            if(temp == head)
            {
                head = temp->next;
                if(head != NULL)
                    head->prev = NULL;
            }
            else
            {
                if(temp->prev != NULL)
                    temp->prev->next = temp->next;

                if(temp->next != NULL)
                    temp->next->prev = temp->prev;
            }

            free(temp);
            printf("\nContact Deleted Successfully!\n");
            return;
        }

        temp = temp->next;
    }

    printf("\nContact Not Found.\n");
}

/*========================================
         DELETE ALL CONTACTS
========================================*/
void deleteAllContacts()
{
    struct Contact *temp = head;
    struct Contact *nextNode;

    if(head == NULL)
    {
        printf("\nNo Contacts Found.\n");
        return;
    }

    while(temp != NULL)
    {
        nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }

    head = NULL;

    printf("\nAll Contacts Deleted Successfully!\n");
}

/*========================================
              SAVE TO FILE
========================================*/
void saveToFile()
{
    FILE *fp = fopen("contacts.txt", "w");
    struct Contact *temp = head;

    if(fp == NULL)
    {
        printf("\nFile Cannot Be Opened.\n");
        return;
    }

    while(temp != NULL)
    {
        fprintf(fp, "%s %s %s\n",
                temp->name,
                temp->phone,
                temp->email);

        temp = temp->next;
    }

    fclose(fp);

    printf("\nContacts Saved To File.\n");
}

/*========================================
              LOAD FROM FILE
========================================*/
void loadFromFile()
{
    FILE *fp = fopen("contacts.txt", "r");

    if(fp == NULL)
    {
        printf("\nNo File Found.\n");
        return;
    }

    while(1)
    {
        struct Contact *newNode =
        (struct Contact*)malloc(sizeof(struct Contact));

        if(fscanf(fp, "%s %s %s",
                  newNode->name,
                  newNode->phone,
                  newNode->email) != 3)
        {
            free(newNode);
            break;
        }

        newNode->next = NULL;
        newNode->prev = NULL;

        if(head == NULL)
        {
            head = newNode;
        }
        else
        {
            struct Contact *temp = head;

            while(temp->next != NULL)
                temp = temp->next;

            temp->next = newNode;
            newNode->prev = temp;
        }
    }

    fclose(fp);

    printf("\nContacts Loaded From File.\n");
}

/*========================================
                 MENU
========================================*/
void menu()
{
    printf("\n=====================================\n");
    printf("         PHONEBOOK SYSTEM            \n");
    printf("=====================================\n");
    printf(" [1]  Add Contact\n");
    printf(" [2]  Display Contacts\n");
    printf(" [3]  Display Reverse\n");
    printf(" [4]  Search Contact (By Name)\n");
    printf(" [5]  Update Contact\n");
    printf(" [6]  Delete Contact\n");
    printf(" [7]  Delete All Contacts\n");
    printf(" [8]  Save To File\n");
    printf(" [9]  Load From File\n");
    printf(" [10] Exit\n");
    printf("=====================================\n");
    printf(" Enter Your Choice : ");
}

/*========================================
                 MAIN
========================================*/
int main()
{
    int choice;

    while(1)
    {
        menu();
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: addContact(); break;
            case 2: displayContacts(); break;
            case 3: displayReverse(); break;
            case 4: searchContact(); break;
            case 5: updateContact(); break;
            case 6: deleteContact(); break;
            case 7: deleteAllContacts(); break;
            case 8: saveToFile(); break;
            case 9: loadFromFile(); break;

            case 10:
                printf("\nThank You!\n");
                exit(0);

            default:
                printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}
