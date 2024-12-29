#include <iostream>
#include <iomanip> // For formatting output

using namespace std;

// Book struct to store book details
struct Book {
    string title, author, reader = "Available"; // Book details and reader status
    int year;
    float price;

    bool isAvailable() { return reader == "Available"; } // Check if the book is available
    void borrow(const string& name) { reader = name; } // Borrow the book
    void returnBook() { reader = "Available"; } // Return the book
};

// Category struct to hold books (max 5)
struct Category {
    string name;
    Book books[5];
    int count = 0; // Number of books in this category
};

// Function to display book details
void showBook(const Book& b) {
    cout << setw(20) << left << "Title: " << b.title << endl;
    cout << setw(20) << left << "Author: " << b.author << endl;
    cout << setw(20) << left << "Year: " << b.year << endl;
    cout << setw(20) << left << "Price: $" << fixed << setprecision(2) << b.price << endl;
    cout << setw(20) << left << "Status: " << (b.isAvailable() ? "Available" : "Borrowed by " + b.reader) << endl;
}

// Function to search for a book by title
bool findBook(Book b[], int n, const string& title) {
    for (int i = 0; i < n; i++) {
        if (b[i].title == title) return true; // Book found
    }
    return false; // Book not found
}

// Function to display the menu
void menu() {
    cout << "\n1. View Categories\n2. Borrow a Book\n3. Return a Book\n4. Exit\n";
}

int main() {
    int n;
    cout << "Enter number of categories: ";
    cin >> n;
    cin.ignore(); // Clear the input buffer

    Category cats[n]; // Array of categories

    // Input book details for each category
    for (int i = 0; i < n; i++) {
        cout << "Enter category name: ";
        getline(cin, cats[i].name);
        cout << "Enter number of books (max 5): ";
        int m;
        cin >> m;
        m = min(m, 5); // Limit to 5 books
        cin.ignore(); // Clear buffer

        for (int j = 0; j < m; j++) {
            Book b;
            cout << "Enter title: ";
            getline(cin, b.title);
            cout << "Enter author: ";
            getline(cin, b.author);
            cout << "Enter year: ";
            cin >> b.year;
            cout << "Enter price: ";
            cin >> b.price;
            cin.ignore(); // Clear buffer

            cats[i].books[cats[i].count++] = b; // Add book to category
        }
    }

    bool running = true;

    while (running) {
        menu(); // Show menu
        int choice;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // Clear buffer

        switch (choice) {
            case 1: {
                // View Categories and Books
                for (int i = 0; i < n; i++) {
                    cout << "\nCategory: " << cats[i].name << endl;
                    for (int j = 0; j < cats[i].count; j++) {
                        showBook(cats[i].books[j]); // Display each book
                    }
                }
                break;
            }
            case 2: {
                // Borrow a Book
                string title, borrower;
                cout << "Enter book title to borrow: ";
                getline(cin, title);
                cout << "Enter your name: ";
                getline(cin, borrower);

                bool found = false;
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < cats[i].count; j++) {
                        if (cats[i].books[j].title == title && cats[i].books[j].isAvailable()) {
                            cats[i].books[j].borrow(borrower);
                            cout << "Book borrowed successfully!\n";
                            found = true;
                            break;
                        }
                    }
                    if (found) break;
                }
                if (!found) cout << "Book not found or already borrowed.\n";
                break;
            }
            case 3: {
                // Return a Book
                string title, borrower;
                cout << "Enter book title to return: ";
                getline(cin, title);
                cout << "Enter your name: ";
                getline(cin, borrower);

                bool returned = false;
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < cats[i].count; j++) {
                        if (cats[i].books[j].title == title && !cats[i].books[j].isAvailable()) {
                            if (cats[i].books[j].reader == borrower) {
                                cats[i].books[j].returnBook();
                                cout << "Book returned successfully!\n";
                                returned = true;
                                break;
                            } else {
                                cout << "This book was borrowed by " << cats[i].books[j].reader << endl;
                                returned = true;
                                break;
                            }
                        }
                    }
                    if (returned) break;
                }
                if (!returned) cout << "Book not found or not borrowed by you.\n";
                break;
            }
            case 4: {
                cout << "Exiting...\n";
                running = false; // Exit the loop and the program
                break;
            }
            default: {
                cout << "Invalid choice. Try again.\n";
                break;
            }
        }
    }

    return 0;
}
