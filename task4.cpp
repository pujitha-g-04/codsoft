#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

struct Book
{
    string title;
    string author;
    string isbn;
    bool available;

    Book(string t, string a, string i) : title(t), author(a), isbn(i), available(true) {}
};

struct Borrower
{
    string name;
    string borrowedISBN;
    time_t borrowDate;

    Borrower(string n, string isbn, time_t date) : name(n), borrowedISBN(isbn), borrowDate(date) {}
};

vector<Book> books;         // Stores all books
vector<Borrower> borrowers; // Stores borrowers' transactions

// Function declarations
void addBook();
void searchBook();
void checkoutBook();
void returnBook();
void calculateFine(Borrower borrower);
void displayMenu();
int daysBetween(time_t start, time_t end);

int main()
{
    int choice;

    do
    {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Clear the newline from the buffer

        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            searchBook();
            break;
        case 3:
            checkoutBook();
            break;
        case 4:
            returnBook();
            break;
        case 5:
            cout << "Exiting the system...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}

// Function to add a book to the library database
void addBook()
{
    string title, author, isbn;
    cout << "Enter book title: ";
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter book ISBN: ";
    getline(cin, isbn);
    books.push_back(Book(title, author, isbn));
    cout << "Book added successfully!\n";
}

// Function to search for a book by title, author, or ISBN
void searchBook()
{
    string query;
    cout << "Enter book title, author, or ISBN to search: ";
    getline(cin, query);

    bool found = false;
    for (const auto &book : books)
    {
        if (book.title == query || book.author == query || book.isbn == query)
        {
            cout << "Book Found: " << book.title << " by " << book.author << " (ISBN: " << book.isbn << ") ";
            cout << (book.available ? "[Available]\n" : "[Checked Out]\n");
            found = true;
        }
    }

    if (!found)
    {
        cout << "No book found with the given query.\n";
    }
}

// Function to check out a book to a borrower
void checkoutBook()
{
    string borrowerName, isbn;
    cout << "Enter borrower's name: ";
    getline(cin, borrowerName);
    cout << "Enter book ISBN: ";
    getline(cin, isbn);

    // Find the book by ISBN
    for (auto &book : books)
    {
        if (book.isbn == isbn)
        {
            if (!book.available)
            {
                cout << "This book is already checked out.\n";
                return;
            }

            // Mark the book as checked out
            book.available = false;
            time_t now = time(0);
            borrowers.push_back(Borrower(borrowerName, isbn, now));
            cout << "Book checked out to " << borrowerName << " on " << ctime(&now);
            return;
        }
    }

    cout << "Book with ISBN " << isbn << " not found.\n";
}

// Function to return a book and update its status
void returnBook()
{
    string isbn;
    cout << "Enter book ISBN to return: ";
    getline(cin, isbn);

    // Find the borrower and calculate fine
    for (auto it = borrowers.begin(); it != borrowers.end(); ++it)
    {
        if (it->borrowedISBN == isbn)
        {
            time_t now = time(0);
            calculateFine(*it);

            // Mark the book as available
            for (auto &book : books)
            {
                if (book.isbn == isbn)
                {
                    book.available = true;
                    break;
                }
            }

            // Remove the borrower from the list
            borrowers.erase(it);
            cout << "Book returned successfully on " << ctime(&now);
            return;
        }
    }

    cout << "No record of this book being checked out.\n";
}

// Function to calculate fine for overdue books
void calculateFine(Borrower borrower)
{
    time_t now = time(0);
    int daysLate = daysBetween(borrower.borrowDate, now) - 14; // 14 days borrowing period
    if (daysLate > 0)
    {
        double fine = daysLate * 1.0; // $1 fine per day
        cout << borrower.name << " has a fine of $" << fine << " for " << daysLate << " days late.\n";
    }
    else
    {
        cout << "No fine. Book returned on time.\n";
    }
}

// Function to display the main menu
void displayMenu()
{
    cout << "\nLibrary Management System\n";
    cout << "1. Add Book\n";
    cout << "2. Search Book\n";
    cout << "3. Checkout Book\n";
    cout << "4. Return Book\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

// Utility function to calculate the number of days between two time points
int daysBetween(time_t start, time_t end)
{
    return difftime(end, start) / (60 * 60 * 24);
}
