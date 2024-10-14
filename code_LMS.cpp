#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Added for find()

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool isIssued;

    Book(int id, string title, string author) {
        this->id = id;
        this->title = title;
        this->author = author;
        this->isIssued = false;
    }
};

struct Member {
    int id;
    string name;
    vector<int> borrowedBooks;

    Member(int id, string name) {
        this->id = id;
        this->name = name;
    }
};

class Library {
    vector<Book> books;
    vector<Member> members;

public:
    void addBook(int id, string title, string author) {
        books.push_back(Book(id, title, author));
        cout << "Book added successfully!" << endl;
    }

    void viewBooks() {
        cout << "ID\tTitle\t\tAuthor\t\tStatus" << endl;
        for (const auto &book : books) {
            cout << book.id << "\t" << book.title << "\t\t" << book.author << "\t\t" 
                 << (book.isIssued ? "Issued" : "Available") << endl;
        }
    }

    void addMember(int id, string name) {
        members.push_back(Member(id, name));
        cout << "Member added successfully!" << endl;
    }

    void issueBook(int bookId, int memberId) {
        for (auto &book : books) {
            if (book.id == bookId) {
                if (book.isIssued) {
                    cout << "Book is already issued!" << endl;
                    return;
                } else {
                    book.isIssued = true;
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

    void returnBook(int bookId, int memberId) {
        for (auto &book : books) {
            if (book.id == bookId && book.isIssued) {
                book.isIssued = false;
                for (auto &member : members) {
                    if (member.id == memberId) {
                        auto it = find(member.borrowedBooks.begin(), member.borrowedBooks.end(), bookId);
                        if (it != member.borrowedBooks.end()) {
                            member.borrowedBooks.erase(it);
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

    void viewMemberBorrowedBooks(int memberId) {
        for (const auto &member : members) {
            if (member.id == memberId) {
                cout << "Member: " << member.name << endl;
                cout << "Borrowed Books: " << endl;
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
