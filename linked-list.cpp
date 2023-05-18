#include <iostream>
#include <string>

using namespace std;

// deklarasi single linked list
struct Buku
{
    string judul, pengarang;
    int tahunTerbit;

    Buku *next;
};

Buku *head = NULL, *tail = NULL, *cur, *newNode, *del;

// create single linkedlist
void createSingleLinkedList(string judul, string pengarang, int tB)
{
    head = new Buku();
    head->judul = judul;
    head ->pengarang = pengarang;
    head->tahunTerbit = tB;
    head->next = NULL;
    tail = head;
}

void addFirst(string judul, string pengarang, int tB)
{
    newNode = new Buku();
    newNode->judul = judul;
    newNode ->pengarang = pengarang;
    newNode->tahunTerbit = tB;
    newNode->next = head;
    head = newNode;
}

void addLast(string judul, string pengarang, int tB)
{
    newNode = new Buku(); 
    newNode->judul = judul;
    newNode ->pengarang = pengarang;
    newNode->tahunTerbit = tB;
    newNode->next = NULL;
    tail-> next = newNode; 
    tail = newNode;
}

// tambah tengah single linked list
void addMidle(string judul, string pengarang, int tB, int posisi)
{
    newNode = new Buku(); 
    newNode->judul = judul;
    newNode ->pengarang = pengarang;
    newNode->tahunTerbit = tB;

    // transversing
    cur = head;
     
}

// remove first
void removeFirst()
{
    del = head;
    head = head->next;
    delete del;
}

void removeLast()
{
    del = tail;
    cur = head;
    while (cur->next != tail)
    {
        cur = cur->next;
    }
    tail = cur;
    tail->next = NULL;
    delete del;
}

void changeFirst(string judul, string pengarang, int tB)
{
    head->judul = judul;
    head->pengarang = pengarang;
    head->tahunTerbit = tB;
}

void changeLast(string judul, string pengarang, int tB)
{
    tail->judul = judul;
    tail->pengarang = pengarang;
    tail->tahunTerbit = tB;
}

void printSingleLinkedList()
{
    cur = head;
    int i = 1;
    while (cur != NULL)
    {
        
        cout << "Judul node "<< i << " : " << cur->judul <<endl; 
        cout << "Pengarang node "<< i <<  " : " << cur->pengarang <<endl; 
        cout << "Tahun terbit node "<< i << " : " << cur->tahunTerbit <<endl; 
        i++;
        cur = cur->next;
    }
}

int main()
{
    createSingleLinkedList("Mata", "Geez & aAn", 2018);
    printSingleLinkedList();
    cout << endl << endl << endl;
    addFirst("Mata", "Geez ", 2012);
    printSingleLinkedList();
    cout << endl << endl << endl;
    addLast("asata", "asdfasdf", 2013);
    printSingleLinkedList();
    cout << endl << endl << endl;
    removeFirst();
    printSingleLinkedList();
    // cout << endl << endl << endl;
    // addLast("asaasdfw24", "124231sadf", 201212);
    // printSingleLinkedList();
    // removeLast();
    // cout << endl << endl << endl;
    // printSingleLinkedList();
    // cout << endl << endl << endl;
    // changeFirst("Kastaadf", "gesadfooo", 2000);
    // printSingleLinkedList();

    return 0;
}   