# Library Management System

**This repository contains a simple command-line Library Management System implemented in C. The system allows librarians and users to perform various tasks such as adding, viewing, and deleting books, as well as borrowing and returning books.**


**Librarian Functionality:**

* Add, view, search for, and delete books from the library
* Register new users
* View list of currently borrowed books

**User Functionality:**

* Login and search for books
* Borrow and return books

**Features:**

* Data structures for books, users, and librarians
* File based storage for book and user data (implemented later, not currently included)
* User authentication with username and password (secure password input with `_getch()`)
* Clear menu-driven interface

**To run the program:**

1. Compile the source code (`library.c`) using a C compiler.
2. Run the executable file.

**Additional Notes:**

* This is a basic implementation and can be further extended with features like:
    * Fine calculations for overdue books
    * User borrowing history
    * Different user roles with varying permissions
* Secure password storage is not implemented in this version and should be addressed for real-world usage.

**Feel free to contribute to this project by adding new features, improving the code, or fixing bugs. Pull requests are welcome!**

**For any questions or suggestions, please open an issue in this repository.**
