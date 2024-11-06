#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Added for find()

using namespace std;

// Structure to represent a Book in the library
struct Book {
    int id;
    string title;
    string author;
    bool isIssued;

    // Constructor to initialize a book with given ID, title, and author
    Book(int id, string title, string author) {
        this->id = id;
        this->title = title;
        this->author = author;
        this->isIssued = false; // Book is initially not issued
    }
};

// Structure to represent a Library Member
struct Member {
    int id;
    string name;
    vector<int> borrowedBooks; // List of book IDs borrowed by the member

    // Constructor to initialize a member with ID and name
    Member(int id, string name) {
        this->id = id;
        this->name = name;
    }
};

// Library class managing books and members
class Library {
    vector<Book> books;       // Collection of books in the library
    vector<Member> members;   // Collection of library members

public:
    // Function to add a new book to the library
    void addBook(int id, string title, string author) {
        books.push_back(Book(id, title, author));
        cout << "Book added successfully!" << endl;
    }

    // Function to display all books in the library
    void viewBooks() {
        cout << "ID\tTitle\t\tAuthor\t\tStatus" << endl;
        for (const auto &book : books) {
            cout << book.id << "\t" << book.title << "\t\t" << book.author << "\t\t" 
                 << (book.isIssued ? "Issued" : "Available") << endl;
        }
    }

    // Function to add a new member to the library
    void addMember(int id, string name) {
        members.push_back(Member(id, name));
        cout << "Member added successfully!" << endl;
    }

    // Function to issue a book to a member
    void issueBook(int bookId, int memberId) {
        // Search for the book by its ID
        for (auto &book : books) {
            if (book.id == bookId) {
                if (book.isIssued) {
                    // If the book is already issued
                    cout << "Book is already issued!" << endl;
                    return;
                } else {
                    book.isIssued = true; // Mark the book as issued
                    // Find the member and add the book to their borrowed list
                    for (auto &member : members) {
                        if (member.id == memberId) {
                            member.borrowedBooks.push_back(bookId);
                            cout << "Book issued to member " << member.name << "!" << endl;
                            return;
                        }
                    }
                    cout << "Member not found!" << endl;
                    return;
                }
            }
        }
        cout << "Book not found!" << endl;
    }

    // Function to return a book by a member
    void returnBook(int bookId, int memberId) {
        // Search for the book by its ID and ensure it's issued
        for (auto &book : books) {
            if (book.id == bookId && book.isIssued) {
                book.isIssued = false; // Mark the book as returned
                // Find the member and remove the book from their borrowed list
                for (auto &member : members) {
                    if (member.id == memberId) {
                        auto it = find(member.borrowedBooks.begin(), member.borrowedBooks.end(), bookId);
                        if (it != member.borrowedBooks.end()) {
                            member.borrowedBooks.erase(it); // Remove book from borrowed list
                            cout << "Book returned by member " << member.name << "!" << endl;
                            return;
                        }
                    }
                }
                cout << "Member not found!" << endl;
                return;
            }
        }
        cout << "Book not found or not issued!" << endl;
    }

    // Function to view books borrowed by a specific member
    void viewMemberBorrowedBooks(int memberId) {
        // Search for the member by their ID
        for (const auto &member : members) {
            if (member.id == memberId) {
                cout << "Member: " << member.name << endl;
                cout << "Borrowed Books: " << endl;
                // Display each borrowed book's title and author
                for (int bookId : member.borrowedBooks) {
                    for (const auto &book : books) {
                        if (book.id == bookId) {
                            cout << book.title << " by " << book.author << endl;
                        }
                    }
                }
                return;
            }
        }
        cout << "Member not found!" << endl;
    }
};

int main() {
    Library library;

    int choice, bookId, memberId;
    string title, author, name;

    do {
        // Display menu options to the user
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Add Member\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. View Member Borrowed Books\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Execute the user's choice
        switch (choice) {
            case 1:
                cout << "Enter Book ID: ";
                cin >> bookId;
                cout << "Enter Book Title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter Book Author: ";
                getline(cin, author);
                library.addBook(bookId, title, author);
                break;

            case 2:
                library.viewBooks();
                break;

            case 3:
                cout << "Enter Member ID: ";
                cin >> memberId;
                cout << "Enter Member Name: ";
                cin.ignore();
                getline(cin, name);
                library.addMember(memberId, name);
                break;

            case 4:
                cout << "Enter Book ID to issue: ";
                cin >> bookId;
                cout << "Enter Member ID: ";
                cin >> memberId;
                library.issueBook(bookId, memberId);
                break;

            case 5:
                cout << "Enter Book ID to return: ";
                cin >> bookId;
                cout << "Enter Member ID: ";
                cin >> memberId;
                library.returnBook(bookId, memberId);
                break;

            case 6:
                cout << "Enter Member ID: ";
                cin >> memberId;
                library.viewMemberBorrowedBooks(memberId);
                break;

            case 0:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
