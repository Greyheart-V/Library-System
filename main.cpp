#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ==========================================
//           CLASS DEFINITIONS
// ==========================================

// Class for the Book objects
class Book {
private:
    int id;
    string title;
    string author;
    bool isAvailable;
    string condition; // Added this to track if book is "Good" or "Damaged"

public:
    // Constructor to set up a new book
    Book(int i, string t, string a) {
        id = i;
        title = t;
        author = a;
        isAvailable = true; // Books start as available
        condition = "Good"; // Default condition is good
    }

    // Getters to read private data
    int getId() { return id; }
    string getTitle() { return title; }
    bool checkAvailability() { return isAvailable; }

    // Helper to see the book's condition
    string getCondition() { return condition; }

    // Mark a book as damaged (Unique Feature)
    void reportDamage() {
        condition = "Damaged";
    }

    // Change status when borrowed/returned
    void borrowBook() { isAvailable = false; }
    void returnBook() { isAvailable = true; }
};

// Class for the Library Users
class User {
private:
    int id;
    string name;
    string userType; // Tracks if it's a "Student" or "Teacher"
    int booksBorrowed;

public:
    // Constructor: needs ID, Name, and Type (Student/Teacher)
    User(int i, string n, string type) {
        id = i;
        name = n;
        userType = type;
        booksBorrowed = 0;
    }

    int getId() { return id; }
    string getName() { return name; }

    // Check if user has reached their limit
    // Teachers get 5 books, Students get 3
    bool canBorrow() {
        int limit = 3; // Standard limit

        if (userType == "Teacher") {
            limit = 5; // Teachers get more
        }

        if (booksBorrowed < limit) {
            return true;
        } else {
            return false;
        }
    }

    // Update borrow count
    void increaseCount() { booksBorrowed++; }
    void decreaseCount() { booksBorrowed--; }
};

// Main System Class
class LibrarySystem {
private:
    vector<Book> books; // List of all books
    vector<User> users; // List of all users

public:
    // Add a new book to the system
    void addBook(int id, string title, string author) {
        Book newBook(id, title, author);
        books.push_back(newBook);
    }

    // Register a new user
    void registerUser(int id, string name, string type) {
        User newUser(id, name, type);
        users.push_back(newUser);
    }

    // Search for a book by title
    void searchBook(string titleToFind) {
        cout << "   [Search] Looking for: '" << titleToFind << "'..." << endl;
        bool found = false;

        // Loop through the list to find a match
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getTitle() == titleToFind) {
                cout << "   -> FOUND! ID: " << books[i].getId()
                     << " | Title: " << books[i].getTitle()
                     << " | Condition: " << books[i].getCondition() << endl;
                found = true;
            }
        }

        if (found == false) {
            cout << "   -> Not Found." << endl;
        }
    }

    // Admin function to mark a book as damaged
    void markBookDamaged(int id) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getId() == id) {
                books[i].reportDamage();
                cout << "   [Admin] Alert: Book ID " << id << " marked as DAMAGED." << endl;
                return;
            }
        }
        cout << "   [Admin] Error: Book not found." << endl;
    }

    // Remove a book from the library
    void removeBook(int idToRemove) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getId() == idToRemove) {
                // erase() removes the item at position 'i'
                books.erase(books.begin() + i);
                cout << "   [Admin] Book ID " << idToRemove << " removed from system." << endl;
                return;
            }
        }
        cout << "   [Admin] Error: Book ID not found." << endl;
    }

    // Main logic for borrowing a book
    void borrowBook(int userId, int bookId) {
        int userIndex = -1;
        int bookIndex = -1;

        // Find the User in our list
        for (int i = 0; i < users.size(); i++) {
            if (users[i].getId() == userId) userIndex = i;
        }
        // Find the Book in our list
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getId() == bookId) bookIndex = i;
        }

        // 1. Check if User or Book exists
        if (userIndex == -1) { cout << "   [Error] User not found." << endl; return; }
        if (bookIndex == -1) { cout << "   [Error] Book not found." << endl; return; }

        // 2. Check if book is already taken
        if (books[bookIndex].checkAvailability() == false) {
            cout << "   [Failed] Book is already borrowed." << endl;
            return;
        }

        // 3. Check Condition (Warn if damaged)
        if (books[bookIndex].getCondition() == "Damaged") {
            cout << "   [WARNING] You are borrowing a DAMAGED book. Handle with care." << endl;
        }

        // 4. Check User Limit (3 for students, 5 for teachers)
        if (users[userIndex].canBorrow() == false) {
            cout << "   [Failed] Borrow limit reached for this user type." << endl;
            return;
        }

        // If all checks pass, do the transaction
        books[bookIndex].borrowBook();
        users[userIndex].increaseCount();
        cout << "   [Success] " << users[userIndex].getName() << " borrowed '" << books[bookIndex].getTitle() << "'" << endl;
    }
};

// ==========================================
//           TESTING THE SYSTEM
// ==========================================
int main() {
    LibrarySystem myLib;

    cout << "==========================================" << endl;
    cout << "    LIBRARY SYSTEM - AUTOMATED TEST RUN   " << endl;
    cout << "==========================================" << endl;

    // --- 1. Setting up initial data ---
    cout << "\n[Step 1] Setting up Database..." << endl;
    myLib.addBook(101, "Intro to C++", "Bjarne S.");
    myLib.addBook(102, "Clean Code", "Robert M.");
    myLib.addBook(103, "The Hobbit", "Tolkien");
    myLib.addBook(104, "1984", "Orwell");
    myLib.addBook(105, "Art History", "Picasso");

    // Create a Student (Limit 3)
    myLib.registerUser(1, "John Doe", "Student");
    // Create a Teacher (Limit 5) - Testing the unique feature
    myLib.registerUser(2, "Prof. Smith", "Teacher");

    // --- 2. Positive Tests (Things that should work) ---
    cout << "\n[Step 2] Testing Normal Usage..." << endl;
    myLib.searchBook("The Hobbit");
    myLib.borrowBook(1, 101); // John borrows book 1
    myLib.borrowBook(1, 102); // John borrows book 2

    // --- 3. Negative Tests (Things that should fail) ---
    cout << "\n[Step 3] Testing Error Handling..." << endl;

    cout << "-> Scenario: Borrowing a book that is already taken" << endl;
    myLib.borrowBook(2, 101); // Prof Smith tries to take book 1, but John has it

    cout << "-> Scenario: Searching for a missing book" << endl;
    myLib.searchBook("Harry Potter");

    cout << "-> Scenario: Borrowing invalid ID" << endl;
    myLib.borrowBook(1, 999);

    // --- 4. Limit Tests (Boundary check) ---
    cout << "\n[Step 4] Testing Student Borrow Limit (Max 3)..." << endl;
    myLib.borrowBook(1, 103); // John borrows his 3rd book (Limit reached)

    cout << "-> Attempting to borrow 4th book (Should Fail)" << endl;
    myLib.borrowBook(1, 104); // Should error out

    // --- 5. Testing Unique Features ---
    cout << "\n[Step 5] Testing Unique Features..." << endl;

    // Feature A: Teacher Limit
    cout << "-> Testing Teacher Limit (Max 5)" << endl;
    myLib.borrowBook(2, 104); // Borrow 1
    myLib.borrowBook(2, 105); // Borrow 2 (No error, even though students are limited to 3)

    // Feature B: Damaged Books
    cout << "-> Testing Damaged Book Handling" << endl;
    myLib.markBookDamaged(105); // Mark "Art History" as damaged

    // Register Alice to test borrowing the damaged book
    myLib.registerUser(3, "Alice", "Student");
    myLib.searchBook("Art History"); // This should show "Condition: Damaged"

    // --- 6. Remove Functionality ---
    cout << "\n[Step 6] Testing Remove Functionality..." << endl;
    myLib.removeBook(104); // Remove "1984"
    myLib.borrowBook(3, 104); // Alice tries to borrow "1984" (Should fail now)

    cout << "\n==========================================" << endl;
    cout << "          ALL TESTS COMPLETED             " << endl;
    cout << "==========================================" << endl;

    return 0;
}