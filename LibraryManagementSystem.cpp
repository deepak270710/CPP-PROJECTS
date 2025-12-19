#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class temp {
    string id, name, author, search;
    fstream file;

public:
    void addBook();
    void showAll();
    void extractBook();
    void deleteBook();
    void updateBook();
    void searchBook();
    void countBooks();
};

temp obj;

int main() {
    char choice;

    while (true) {
        cout << "\n----------------------------------\n";
        cout << "1 - Show All Books\n";
        cout << "2 - Extract Book (By ID)\n";
        cout << "3 - Add Book (ADMIN)\n";
        cout << "4 - Delete Book\n";
        cout << "5 - Update Book\n";
        cout << "6 - Search Book (Name/Author)\n";
        cout << "7 - Total Book Count\n";
        cout << "8 - Exit\n";
        cout << "----------------------------------\n";
        cout << "Enter Your Choice :: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case '1': obj.showAll(); break;
        case '2': obj.extractBook(); break;
        case '3': obj.addBook(); break;
        case '4': obj.deleteBook(); break;
        case '5': obj.updateBook(); break;
        case '6': obj.searchBook(); break;
        case '7': obj.countBooks(); break;
        case '8': return 0;
        default: cout << "Invalid Choice!\n";
        }
    }
}

// ----------- ADD BOOK -----------
void temp::addBook() {
    cout << "\nEnter Book ID :: ";
    getline(cin, id);
    cout << "Enter Book Name :: ";
    getline(cin, name);
    cout << "Enter Author Name :: ";
    getline(cin, author);

    file.open("bookData.txt", ios::out | ios::app);
    file << id << "*" << name << "*" << author << endl;
    file.close();

    cout << "Book Added Successfully!\n";
}

// -----------  SHOW ALL BOOKS -----------
void temp::showAll() {
    file.open("bookData.txt", ios::in);
    if (!file) {
        cout << "No Data Found!\n";
        return;
    }

    cout << "\nBook ID\t\tBook Name\t\tAuthor\n";
    cout << "-----------------------------------------------\n";

    while (getline(file, id, '*') &&
           getline(file, name, '*') &&
           getline(file, author)) {
        cout << id << "\t\t" << name << "\t\t" << author << endl;
    }
    file.close();
}

// ----------- EXTRACT BOOK -----------  
void temp::extractBook() {
    cout << "Enter Book ID :: ";
    getline(cin, search);

    file.open("bookData.txt", ios::in);
    bool found = false;

    cout << "\nBook ID\t\tBook Name\t\tAuthor\n";
    cout << "-----------------------------------------------\n";

    while (getline(file, id, '*') &&
           getline(file, name, '*') &&
           getline(file, author)) {
        if (id == search) {
            cout << id << "\t\t" << name << "\t\t" << author << endl;
            found = true;
            break;
        }
    }
    file.close();

    if (!found)
        cout << "Book Not Found!\n";
}

// ----------- DELETE BOOK -----------
void temp::deleteBook() {
    cout << "Enter Book ID to Delete :: ";
    getline(cin, search);

    fstream tempFile;
    file.open("bookData.txt", ios::in);
    tempFile.open("temp.txt", ios::out);

    bool found = false;

    while (getline(file, id, '*') &&
           getline(file, name, '*') &&
           getline(file, author)) {
        if (id != search) {
            tempFile << id << "*" << name << "*" << author << endl;
        } else {
            found = true;
        }
    }

    file.close();
    tempFile.close();

    remove("bookData.txt");
    rename("temp.txt", "bookData.txt");

    if (found)
        cout << "Book Deleted Successfully!\n";
    else
        cout << "Book ID Not Found!\n";
}

// -----------UPDATE BOOK -----------
void temp::updateBook() {
    cout << "Enter Book ID to Update :: ";
    getline(cin, search);

    fstream tempFile;
    file.open("bookData.txt", ios::in);
    tempFile.open("temp.txt", ios::out);

    bool found = false;

    while (getline(file, id, '*') &&
           getline(file, name, '*') &&
           getline(file, author)) {

        if (id == search) {
            cout << "Enter New Book Name :: ";
            getline(cin, name);
            cout << "Enter New Author Name :: ";
            getline(cin, author);
            found = true;
        }
        tempFile << id << "*" << name << "*" << author << endl;
    }

    file.close();
    tempFile.close();

    remove("bookData.txt");
    rename("temp.txt", "bookData.txt");

    if (found)
        cout << "Book Updated Successfully!\n";
    else
        cout << "Book ID Not Found!\n";
}

// ----------- SEARCH BOOK -----------
void temp::searchBook() {
    cout << "Enter Book Name or Author :: ";
    getline(cin, search);

    file.open("bookData.txt", ios::in);
    bool found = false;

    cout << "\nBook ID\t\tBook Name\t\tAuthor\n";
    cout << "-----------------------------------------------\n";

    while (getline(file, id, '*') &&
           getline(file, name, '*') &&
           getline(file, author)) {

        if (name == search || author == search) {
            cout << id << "\t\t" << name << "\t\t" << author << endl;
            found = true;
        }
    }
    file.close();

    if (!found)
        cout << "No Matching Book Found!\n";
}

// ----------- COUNT BOOKS -----------
void temp::countBooks() {
    int count = 0;
    file.open("bookData.txt", ios::in);

    while (getline(file, id, '*') &&
           getline(file, name, '*') &&
           getline(file, author)) {
        count++;
    }
    file.close();

    cout << "Total Books Available :: " << count << endl;
}
