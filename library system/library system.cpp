#include <iostream>
#include<string>
#include<stdlib.h>
using namespace std;
//creat doubly-Node with template
template<class T>
class Node
{
public:
    T item;
    Node* previous, * next;
};
//creat a new type of data has include  title & author & ISBN & genre
class Book
{
public:
    string title, author, ISBN, genre;
    bool available;
    Book(string title = "", string author = "", string ISBN = "", string genre = "", bool available = 1)
    {
        this->title = title;
        this->author = author;
        this->ISBN = ISBN;
        this->genre = genre;
        this->available = available;
    }
    bool operator<(const Book& other)const
    {
        return title < other.title;
    }
    bool operator==(const Book& other)const
    {
        return title == other.title;
    }
    bool operator>(const Book& other)const
    {
        return title > other.title;
    }
    friend ostream& operator <<(ostream& output, Book book) {
        output << "Book's title is " << book.title << endl;
        output << "Book's author is " << book.author << endl;
        output << "Book's ISBN is " << book.ISBN << endl;
        output << "Book's number of reservations is " << book.genre << endl;
        return output;
    }

};
//creat the doubly-Linked List with template
template<class t>
class LinkedList
{
private:
    //frist declare 2 pointers
    Node<t>* first;//for the head of the list
    Node<t>* last;//for the tail of the list
    int length;
public:
    LinkedList()
    {
        first = last = NULL;
        length = 0;
    }
    Node<t>* begin()//this to catch the head with begain
    {
        return first;
    }
    Node<t>* end()//this to catch the tail with end
    {
        return last;
    }

    void insertfirst(t element) //to insert the new books to the head   ( <--- )
    {
        Node<t>* newNode = new Node<t>;
        newNode->item = element;
        if (length == 0)
        {
            first = last = newNode;
            newNode->next = newNode->previous = NULL;
        }
        else
        {
            newNode->next = first;
            newNode->previous = NULL;
            first->previous = newNode;
            first = newNode;
        }
        length++;
    }
    void insertlast(t element) //to insert the new books to the tail   ( ---> )
    {
        Node<t>* newNode = new Node<t>;
        newNode->item = element;
        if (length == 0)
        {
            first = last = newNode;
            newNode->next = newNode->previous = NULL;
        }
        else
        {
            newNode->next = NULL;
            newNode->previous = last;
            last->next = newNode;
            last = newNode;
        }
        length++;
    }
    void insertAtPosition(int position, t element)
    {
        Node<t>* newNode = new Node<t>;
        newNode->item = element;
        if (position == 0)
        {
            insertfirst(element);
        }
        else if (position == length)
        {
            insertlast(element);
        }
        else
        {
            Node<t>* current = first;
            for (int i = 1; i < position; i++)
            {
                current = current->next;
            }
            newNode->next = current->next;
            newNode->previous = current;
            current->next->previous = newNode;
            current->next = newNode;
            length++;
        }

    }
    void removefirst()
    {
        if (length == 0)
        {
            cout << "Linked List is Empty can`t remove element" << endl;
        }
        else
        {
            Node<t>* current = first;
            first = first->next;
            first->previous = NULL;
            current->next = current->previous = NULL;
            delete current;
            length--;
        }
    }
    void removelast()
    {
        if (length == 0)
        {
            cout << "Linked List is Empty can`t remove element" << endl;
        }
        else
        {
            Node<t>* current = last;
            last = last->previous;
            last->next = NULL;
            current->next = current->previous = NULL;
            delete current;
            length--;
        }
    }
    //remove element
    void removeAtPosition(int position)
    {
        if (position == 0)
        {
            removefirst();
        }
        else if (position == length - 1)
        {
            removelast();
        }
        else
        {
            Node<t>* current = first;
            for (int i = 0; i < position; i++)
            {
                current = current->next;
            }
            current->next->previous = current->previous;
            current->previous->next = current->next;
            current->next = current->previous = NULL;
            delete current;
            length--;
        }
    }
    //search element
    int search(t element)
    {
        Node<t>* current = first;
        for (int i = 0; i < length; i++)
        {
            if (current->item == element)
            {
                return i;
            }
            current = current->next;

        }
        return -1;
    }
    //sort the list
    void sortList()
    {
        Node<t>* previous = first;
        Node<t>* current = NULL;
        while (previous != NULL)
        {
            current = previous->next;
            while (current != NULL)
            {
                if (previous->item > current->item)
                {
                    swap(previous->item, current->item);
                }
                current = current->next;
            }
            previous = previous->next;
        }

    }
    //reverse the list
    void reverse()
    {
        if (first == NULL)
        {
            cout << "Linked List is Empty " << endl;
        }
        else
        {
            Node<t>* previous = first;
            Node<t>* current = first->next;
            Node<t>* next = current->next;
            while (current != NULL)
            {
                if (previous->previous == NULL)
                {
                    previous->previous = current;
                    previous->next = NULL;
                    last = previous;
                }
                current->next = previous;
                current->previous = next;
                previous = current;
                current = next;
                if (next != NULL)
                {
                    next = next->next;
                }
            }
            first = previous;
        }
    }
    //print all items
    void print() //here we declare pointer to point on all the item to print it
    {
        Node<t>* curr = first;
        while (curr != NULL)
        {
            cout << curr->item << " ";
            cout << string(2, '\n');
            curr = curr->next;
        }
    }
};
//the library that inclde of the classes
class Library
{
private:
    LinkedList<Book> catalog;
    int numOfBooks, numOfBorrowedBooks, numOfavailableBooks;

public:
    void addBook(Book book)
    {
        numOfBooks++;
        numOfavailableBooks++;
        catalog.insertlast(book);
    }
    void returnBook(Book book)
    {
        numOfBorrowedBooks--;
        numOfavailableBooks++;
        catalog.insertlast(book);
    }
    void withdrawBook(Book book)
    {
        int bookIdx = catalog.search(book);
        if (bookIdx != -1)
        {
            numOfBorrowedBooks++;
            numOfavailableBooks--;
            catalog.removeAtPosition(bookIdx);
        }
    }
    void allowedBooks()
    {
        cout << "The available books are:" << string(2, '\n');
        catalog.print();
    }
    void displayStatistics()
    {
        cout << "Number of books in the library is " << numOfBooks << "\n";
        cout << "Number of borrowed books in the library is " << numOfBorrowedBooks << "\n";
        cout << "Number of available books in the library is " << numOfavailableBooks << "\n";
    }
    void sort()
    {
        catalog.sortList();
    }
    void reverse() {
        catalog.reverse();
    }

};
int main() {

    int selected;
    int stop = 2;
    Library library;
    do
    {
        cout << "1- Add Book\n2- Return Book\n3- Withdraw Book\n4- allowed Book\n5- sort\n6- reverse\n7- display statistics\n0- end" << endl << "\n==> ";
        cin >> selected;
        cin.ignore();

        switch (selected)
        {
        case 1:
        {
            system("CLS");
            string title, author, ISBN, genre;

            cout << "Enter The Title ==> ";
            getline(cin, title);

            cout << endl << "Enter The Author ==> ";
            getline(cin, author);

            cout << endl << "Enter The ISBN ==> ";
            getline(cin, ISBN);

            cout << endl << "Enter The Genre ==> ";
            getline(cin, genre);

            Book newBook(title, author, ISBN, genre, 1);
            library.addBook(newBook);
            system("CLS");

        }
        break;
        case 2:
        {
            system("CLS");
            string title, author, ISBN, genre;

            cout << "Enter The Title ==> ";
            getline(cin, title);

            cout << endl << "Enter The Author ==> ";
            getline(cin, author);

            cout << endl << "Enter The ISBN ==> ";
            getline(cin, ISBN);

            cout << endl << "Enter The Genre ==> ";
            getline(cin, genre);

            Book newBook(title, author, ISBN, genre, 1);
            library.returnBook(newBook);
            system("CLS");

        }
        break;
        case 3:
        {
            system("CLS");
            string title, author, ISBN, genre;

            cout << "Enter The Title ==> ";
            getline(cin, title);

            cout << endl << "Enter The Author ==> ";
            getline(cin, author);

            cout << endl << "Enter The ISBN ==> ";
            getline(cin, ISBN);

            cout << endl << "Enter The Genre ==> ";
            getline(cin, genre);

            Book newBook(title, author, ISBN, genre, 1);
            library.withdrawBook(newBook);
            system("CLS");

        }
        break;
        case 4:
        {
            system("CLS");
            library.allowedBooks();
            cout << endl;

        }
        break;
        case 5:
        {
            system("CLS");
            library.sort();
            cout << "==> sorted <==" << string(6, '\n');
        }
        break;
        case 6:
        {
            system("CLS");
            library.reverse();
            cout << "==> reversed <==" << string(6, '\n');
        }
        break;
        case 7:
        {
            system("CLS");
            library.displayStatistics();
            cout << string(6, '\n');
        }
        break;
        case 0:
        {
            stop = 0;
        }
        break;
        }
    } while (stop != 0);

    return 0;
}