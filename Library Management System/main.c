#include <stdio.h>
#include <string.h>
#include <conio.h>

// Define data structures for Book, User, and Librarian
typedef struct
{
    int book_id;
    char title[100];
    char author[100];
    int quantity;
    int available;
} Book;

typedef struct
{
    int user_id;
    char username[50];
    char password[50];
    int borrowed_books[10];
    int num_borrowed_books;
} User;

typedef struct
{
    int librarian_id;
    char username[50];
    char password[50];
} Librarian;

#define MAX_BOOKS 100
#define MAX_USERS 50
#define MAX_LIBRARIANS 5

Book library[MAX_BOOKS];
User users[MAX_USERS];
Librarian librarians[MAX_LIBRARIANS];

int numBooks = 0;
int numUsers = 0;
int numLibrarians = 0;
int currentUserID = -1;
int currentLibrarianID = -1;

// Function to add a new book to the library
void addBook()
{
    system("cls");
    printf("\n\n");
    printf("\t\t----------------------------Add Book Details----------------------------\n");
    printf("\n");
    if (numBooks >= MAX_BOOKS)
    {
        printf("The library is full. Cannot add more books.\n");
        return;
    }

    Book newBook;
    newBook.book_id = numBooks + 1; // Assign a unique ID
    printf("\t\tEnter the title of the book: ");
    scanf(" %[^\n]", newBook.title);
    printf("\t\tEnter the author of the book: ");
    scanf(" %[^\n]", newBook.author);
    printf("\t\tEnter the quantity available: ");
    scanf("%d", &newBook.quantity);
    newBook.available = newBook.quantity; // Initially, all are available

    library[numBooks] = newBook;
    numBooks++;
    printf("\t\tBook added successfully.\n");
    printf("\t\t----------------------------\n");
}

// Function to list all books in the library
void listBooks()
{
    system("cls");
    printf("\n\n");
    printf("\t\t----------------------------View Book Details----------------------------\n");
    printf("\n");
    if (numBooks == 0)
    {
        printf("\t\tThe library is empty.\n");
        return;
    }

    printf("\t\tList of Books in the Library:\n");
    for (int i = 0; i < numBooks; i++)
    {
        printf("\t\tBook ID: %d\n", library[i].book_id);
        printf("\t\tTitle: %s\n", library[i].title);
        printf("\t\tAuthor: %s\n", library[i].author);
        printf("\t\tQuantity available: %d\n", library[i].available);
        printf("\n");
    }
}

// Function to delete a book from the library
void deleteBook()
{
    system("cls");
    printf("\n\n");
    printf("\t\t----------------------------Delete Book----------------------------\n");
    printf("\n");
    if (numBooks == 0)
    {
        printf("\t\tThe library is empty.\n");
        return;
    }

    int bookID;
    printf("\t\tEnter the Book ID to delete: ");
    scanf("%d", &bookID);

    int foundIndex = -1;
    for (int i = 0; i < numBooks; i++)
    {
        if (library[i].book_id == bookID)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1)
    {
        printf("\t\tBook with ID %d not found.\n", bookID);
        return;
    }

    // Shift remaining books to cover the deleted book
    for (int i = foundIndex; i < numBooks - 1; i++)
    {
        library[i] = library[i + 1];
    }

    numBooks--;
    printf("\t\tBook deleted successfully.\n");
    printf("\t\t----------------------------\n");
}

// Function to search for a book by ID
void searchBook()
{
    system("cls");
    printf("\n\n");
    printf("\t\t----------------------------Search Book Details----------------------------\n");
    printf("\n");
    int bookID;
    printf("\t\tEnter the Book ID to search for: ");
    scanf("%d", &bookID);

    printf("\t\tSearch Results:\n");
    for (int i = 0; i < numBooks; i++)
    {
        if (library[i].book_id == bookID)
        {
            printf("\t\tBook ID: %d\n", library[i].book_id);
            printf("\t\tTitle: %s\n", library[i].title);
            printf("\t\tAuthor: %s\n", library[i].author);
            printf("\t\tQuantity available: %d\n", library[i].available);
            printf("\t\t----------------------------\n");
            return;  // Found the book, so no need to continue searching
        }
    }

    // If the function reaches here, the book was not found
    printf("\t\tBook with ID %d not found.\n", bookID);
}

// Function to borrow a book
void borrowBook()
{
    system("cls");
    printf("\n\n");
    printf("\t\t----------------------------Borrow Book Details----------------------------\n");
    printf("\n");
    if (currentUserID == -1)
    {
        printf("\t\tYou must be logged in to borrow a book.\n");
        return;
    }

    int bookID;
    printf("\t\tEnter the Book ID to borrow: ");
    scanf("%d", &bookID);

    if (bookID < 1 || bookID > numBooks)
    {
        printf("\t\tInvalid Book ID.\n");
        return;
    }

    Book *book = &library[bookID - 1];

    if (book->available <= 0)
    {
        printf("\t\tThis book is currently not available.\n");
        return;
    }

    User *user = &users[currentUserID];

    if (user->num_borrowed_books >= 10)
    {
        printf("\t\tYou have already borrowed the maximum number of books.\n");
        return;
    }

    // Check if the user has already borrowed a copy of this book
    for (int i = 0; i < user->num_borrowed_books; i++)
    {
        if (user->borrowed_books[i] == bookID)
        {
            printf("\t\tYou have already borrowed a copy of this book.\n");
            return;
        }
    }

    book->available--;
    user->borrowed_books[user->num_borrowed_books] = bookID;
    user->num_borrowed_books++;
    printf("\t\tBook borrowed successfully.\n");
    printf("\t\t----------------------------\n");
}

// Function to return a borrowed book
void returnBook()
{
    system("cls");
    printf("\n\n");
    printf("\t\t----------------------------Return Book Details----------------------------\n");
    printf("\n");
    if (currentUserID == -1)
    {
        printf("\t\tYou must be logged in to return a book.\n");
        return;
    }

    int bookID;
    printf("\n\n\n");
    printf("\t\tEnter the Book ID to return: ");
    scanf("%d", &bookID);

    if (bookID < 1 || bookID > numBooks)
    {
        printf("\t\tInvalid Book ID.\n");
        return;
    }

    Book *book = &library[bookID - 1];
    User *user = &users[currentUserID];

    int bookIndex = -1;

    for (int i = 0; i < user->num_borrowed_books; i++)
    {
        if (user->borrowed_books[i] == bookID)
        {
            bookIndex = i;
            break;
        }
    }

    if (bookIndex == -1)
    {
        printf("\t\tYou haven't borrowed this book.\n");
        return;
    }

    book->available++;
    for (int i = bookIndex; i < user->num_borrowed_books - 1; i++)
    {
        user->borrowed_books[i] = user->borrowed_books[i + 1];
    }
    user->num_borrowed_books--;

    printf("\t\tBook returned successfully.\n");
    printf("\t\t----------------------------\n");
}

// Function to find a user by username
int findUser(char *username)
{
    for (int i = 0; i < numUsers; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            return i;
        }
    }
    return -1; // User not found
}

// Function to register a new user
void registerUser()
{
    system("cls");
    printf("\n\n");
    if (currentUserID != -1)
    {
        char choice;
        printf("\t\tYou are already logged in. Do you want to log out and register a new user (y/n)? ");
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y')
        {
            currentUserID = -1; // Logout the current user
            printf("\t\tLogged out.\n\n");
        }
        else
        {
            printf("\t\tNot logging out.\n");
            printf("\t\t----------------------------\n");
            return; // Skip registration if the user chooses not to log out
        }
    }

    if (numUsers >= MAX_USERS)
    {
        printf("\t\tThe user database is full. Cannot register more users.\n");
        return;
    }

    User newUser;
    newUser.user_id = numUsers;
    printf("\t\tEnter a username: ");
    scanf(" %s", newUser.username);

    // Securely input password using _getch()
    printf("\t\tEnter a password: ");
    int i = 0;
    while (1)
    {
        char ch = _getch();
        if (ch == '\r') // Enter key
        {
            newUser.password[i] = '\0';
            break;
        }
        else if (ch == '\b' && i > 0) // Backspace key
        {
            i--;
            printf("\b \b");
        }
        else if (ch != '\b')
        {
            newUser.password[i++] = ch;
            printf("*");
        }
    }

    newUser.num_borrowed_books = 0;

    users[numUsers] = newUser;
    numUsers++;
    printf("\n\t\tUser registered successfully.\n");
    printf("\n\n");
}

// Function to find a librarian by username
int findLibrarian(char *username)
{
    for (int i = 0; i < numLibrarians; i++)
    {
        if (strcmp(librarians[i].username, username) == 0)
        {
            return i;
        }
    }
    return -1; // Librarian not found
}

// Function for librarian login
void librarianLogin()
{
    while (1)
    {
        char username[50];
        char password[50];

        printf("\n");
        printf("\t\tPlease log in as a librarian or enter 'exit' to go back.\n");
        printf("\t\tUsername: ");
        scanf(" %s", username);

        if (strcmp(username, "exit") == 0)
            break;

        int librarianIndex = findLibrarian(username);

        if (librarianIndex != -1)
        {
            printf("\t\tPassword: ");
            int i = 0;

            while (1)
            {
                char ch = _getch();

                if (ch == '\r') // Enter key
                {
                    password[i] = '\0';
                    break;
                }
                else if (ch == '\b' && i > 0) // Backspace key
                {
                    i--;
                    printf("\b \b");
                }
                else if (ch != '\b')
                {
                    password[i++] = ch;
                    printf("*");
                }
            }

            if (strcmp(librarians[librarianIndex].password, password) == 0)
            {
                currentLibrarianID = librarianIndex;
                printf("\n");
                printf("\t\tLogged in as %s (Librarian).\n", username);
                break;
            }
            else
            {
                printf("\n");
                printf("\t\tIncorrect password. Please try again or enter 'exit' to go back.\n");
            }
        }
        else
        {
            printf("\t\tLibrarian not found. Please try again or enter 'exit' to go back.\n");
        }
    }
}

// The main function
int main()
{
    // Manually add a user
    strcpy(users[numUsers].username, "user");
    strcpy(users[numUsers].password, "pass");
    users[numUsers].user_id = numUsers;
    users[numUsers].num_borrowed_books = 0;
    numUsers++;

    // Initialize a librarian for testing
    strcpy(librarians[numLibrarians].username, "librarian");
    strcpy(librarians[numLibrarians].password, "libpass");
    librarians[numLibrarians].librarian_id = numLibrarians;
    numLibrarians++;

    while (1)
    {
        int loginChoice;
        printf("\t\t=======================================================\n");
        printf("                <=  Welcome to the Library Management System  =>\n");
        printf("\t\t================================================\n\n");
        printf("\t\t1: Login as Librarian\n\t\t2: Login as User\n\t\t3: Exit\n\n");
        printf("  Enter an option: ");
        scanf("%d", &loginChoice);

        switch (loginChoice)
        {
        case 1:
            librarianLogin();
            // If librarian logged in, execute librarian options
            while (currentUserID != -1 || currentLibrarianID != -1)
            {
                int choice;
                printf("\n");
                printf("\t\t-----------------------------\n");
                printf("\t\t| Library Management System |\n");
                printf("\t\t-----------------------------\n");
                printf("\t\t1: Add Book\n\t\t2: View Book Details\n\t\t3: Delete Book\n\t\t4: Logout\n\t\t5: Exit\n\n");
                printf("  Enter an option: ");
                scanf("%d", &choice);
                printf("\n");
                system("cls");

                switch (choice)
                {
                case 1:
                    addBook();
                    break;
                case 2:
                    listBooks();  // Modified to show book details
                    break;
                case 3:
                    deleteBook();
                    break;
                case 4:
                    currentUserID = -1; // Logout user
                    currentLibrarianID = -1; // Logout librarian
                    printf("\n\n");
                    printf("\t\tLogged out.\n");
                    printf("\n\n");
                    break;
                case 5:
                    printf("\n\n\n");
                    printf("\t\tExiting the program.\n");
                    return 0;
                default:
                    printf("\t\tInvalid choice. Please try again.\n");
                }
            }
            break;

        case 2:
            while (1)
            {
                char username[50];
                char password[50];

                printf("\n");
                printf("\t\tPlease log in as a user or enter 'exit' to go back.\n\n");
                printf("\t\tUsername: ");
                scanf(" %s", username);

                if (strcmp(username, "exit") == 0)
                    break;

                int userIndex = findUser(username);

                if (userIndex != -1)
                {
                    printf("\t\tPassword: ");
                    int i = 0;

                    while (1)
                    {
                        char ch = _getch();

                        if (ch == '\r') // Enter key
                        {
                            password[i] = '\0';
                            break;
                        }
                        else if (ch == '\b' && i > 0) // Backspace key
                        {
                            i--;
                            printf("\b \b");
                        }
                        else if (ch != '\b')
                        {
                            password[i++] = ch;
                            printf("*");
                        }
                    }

                    if (strcmp(users[userIndex].password, password) == 0)
                    {
                        currentUserID = userIndex;
                        printf("\n");
                        printf("\t\tLogged in as %s.\n", username);
                        break;
                    }
                    else
                    {
                        printf("\n");
                        printf("\t\tIncorrect password. Please try again or enter 'exit' to go back.\n");
                    }
                }
                else
                {
                    printf("\t\tUser not found. Please try again or enter 'exit' to go back.\n");
                }
            }
            break;

        case 3:
            printf("\n\n\n");
            printf("\t\tExiting the program.\n");
            return 0;

        default:
            printf("\t\tInvalid choice. Please try again.\n");
        }

        while (currentUserID != -1 || currentLibrarianID != -1)
        {
            int choice;
            printf("\n");
            printf("\t\t-----------------------------\n");
            printf("\t\t| Library Management System |\n");
            printf("\t\t-----------------------------\n");
            printf("\t\t1: Search Books\n\t\t2: List Books\n\t\t3: Borrow Book\n\t\t4: Return Book\n");
            printf("\t\t5: Register\n\t\t6: Logout\n\t\t7: Exit\n\n");
            printf("  Enter an option: ");
            scanf("%d", &choice);
            printf("\n");
            system("cls");

            switch (choice)
            {
            case 1:
                searchBook();
                break;
            case 2:
                listBooks();
                break;
            case 3:
                borrowBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                registerUser();
                break;
            case 6:
                currentUserID = -1; // Logout user
                currentLibrarianID = -1; // Logout librarian
                printf("\n\n");
                printf("\t\tLogged out.\n");
                printf("\n\n");
                break;
            case 7:
                printf("\n\n\n");
                printf("\t\tExiting the program.\n");
                return 0;
            default:
                printf("\t\tInvalid choice. Please try again.\n");
            }
        }
    }
}
