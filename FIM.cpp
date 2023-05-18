#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

int menu() {
    int choice;

    system("CLS");
    cout << "\033[34m";
    cout << "\t\t\t\t\t\t\t  FIM - Fi IMproved" << endl;
    cout << "\033[32m";
    cout << "\t\t\t\t\t\t\t    Version 1.0.0\n" << endl;
    cout << "\033[33m";
    cout << "\t\t\t\t\t     FIM is open source and freely distributed." << endl;
    cout << "\t\t\t\t\t        Feel free to check our github repos!\n" << "\n" << endl;
    cout << "\033[37m";
    cout << "1. Create a new file" << endl;
    cout << "2. Read and open from an existing file" << endl;
    cout << "3. Edit a line from a file" << endl;
    cout << "4. Delete file" << endl;
    cout << "0. Exit\n";
    cout << "Enter your choice . . .    ";
    cin >> choice;

    return choice;
}

int editMenu (){
    int choice;
    cout << "1. Add new line" << endl;
    cout << "2. Edit Line"  << endl;
    cout << "3. Remove Line"  << endl;
    cout << "0. Back to menu"  << endl;
    cout << "Enter your choices . . .    ";
    cin >> choice;
    
    return choice;
}

struct Filenote {
    string line;
    Filenote* next;
};

Filenote *head = NULL, *tail = NULL, *cur, *newNode, *nextNode, *del;

bool isTailPosition(Filenote* head, int position) {
    cur = head;
    int length = 0;

    // Menghitung panjang linked list
    while (cur != nullptr) {
        length++;
        cur = cur->next;
    }

    // Mengecek apakah posisi merupakan tail
    if (position == length - 1) {
        return true;
    } else {
        return false;
    }
}

class TextEditor {
    private:
        string file_Name;
        ofstream ofile;
        ifstream ifile;
        
    public: 
        TextEditor(string file_Name = "file.txt") {this->file_Name = file_Name;}
        void writeFile();
        void readFile();
        // linkedlist
            void createLineLinkedList(string); // untuk membaca baris pertama file, lalu memasukkannya sebagai linked list yang pertama dibuat
            void addFirstLine(string); // untuk menambahkan node sebagai node paling awal dari linkedlist
            void addLastLine(string); // untuk menambahkan node sebagai node yang paling terakhir dari linked list
            void removeLinkedList(Filenote*&); // untuk menghapus semua node linkedlist
            void printLinkedList(); // untuk output linkedlist setiap melakukan edit file
        // memodifikasi
            void modifyFile(); // editLine berhubungan dengan edit line
            void editLine(int); // editLine membutuhkan parameter dari modifyFile
            void readFileEdit(); //untuk membaca file lalu memasukkan barisnya ke dalam linked list
            void removeLine(); // untuk menghapus baris dari file yang diinginkan
        ~TextEditor(){};
};

void TextEditor::createLineLinkedList(string line) {
    head = new Filenote();
    head->line = line;
    head->next = NULL;
    tail = head;
}

void TextEditor::addFirstLine(string line){
    newNode = new Filenote();
    newNode->line = line;
    newNode->next = head;
    head = newNode;
}

void TextEditor::addLastLine(string line){
    newNode = new Filenote();
    newNode->line = line;
    newNode->next = nullptr;
    
    if (tail == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void TextEditor::modifyFile(){
    readFile();
    int ch, userChEdit = editMenu();
    /* 
        aku mau buat menu untuk modify line, yang mana isinya;
        mengedit line sesuai pilihan, remove line, tambah line
     */
    switch (userChEdit)
    {
        case 1:
            break;
        case 2:
            cout << "Insert line number to edit: ";
            cin >> ch;
            editLine(ch);
            break;
        case 3:
            removeLine();
            break;
        case 0:
            menu;
            return;
            break;
        default:
            break;
    }
    // printLinkedList();
    // system("pause");
}

void TextEditor::readFileEdit() {
    string line;

    ifile.open(file_Name);
    if (ifile.is_open()) {
        int iterator = 1;
        while (!ifile.eof()) {
            getline(ifile, line);
            if (iterator == 1) {
                createLineLinkedList(line);
            }
            else {
                addLastLine(line);
            }
            iterator++;
        }
        ifile.close();
    } else {
        cout << "Failed to open the file." << endl;
        return;
    }
}


void TextEditor::editLine(int ch){
    cur = head;
    int count = 1;
    // untuk mencari baris yang akan diedit
    while (cur != nullptr && count < ch){
        cur = cur ->next;
        count++;
    }
    // jika tidak ditemukan akan mereturn
    if (cur == nullptr){
        cout << "Line not found" << endl;
        return;
    }
    
    string newLine;
    cout << "Insert the new content: ";
    cin.ignore();
    getline(cin, newLine);
    cur->line = newLine;
    printLinkedList();
}

// menghapus baris yang diinginkan
void TextEditor::removeLine() {
    readFileEdit();
    int ch, count = 1;
    cout << "Enter the line number to remove: ";
    cin >> ch;

    cur = head;
    del = nullptr;
    bool found = false;
    if (ch == 1) {
        head = head->next;
        delete cur;
        found = true;
    } else {
        while (cur != nullptr && count < ch - 1) {
            cur = cur->next;
            count++;
        }

        if (cur != nullptr && cur->next != nullptr) {
            del = cur->next;
            cur->next = del->next;
            delete del;
            found = true;
        }
    }

    if (found) {
        // Tulis ulang isi file
        printLinkedList();
        cout << "Line successfully removed." << endl;
        readFile();
    } else {
        cout << "Line not found." << endl;
    }
}



// fungsi untuk mengprint linked list ke output
void TextEditor::printLinkedList() {
    ofile.open(file_Name);
    // cin.ignore();
    int i = 1; // untuk menghindari enter di akhir file output
    cur = head;
    while (cur != nullptr) {
        if (i == 1) {
            ofile << cur->line;
            cur = cur->next;
            i++;
        } else {
            ofile << endl << cur->line;
            cur = cur->next;
        }
    }    
    ofile.close();
    removeLinkedList(head);
    cout << endl;
}


// menghapus semua linkedlist
void TextEditor::removeLinkedList(Filenote*& head) {
    cur = head;
    nextNode = nullptr;

    while (cur != nullptr) {
        nextNode = cur->next;
        delete cur;
        cur = nextNode;
    }

    head = nullptr;
}

void TextEditor::readFile() {
    int iterator = 1;
    string line;

    ifile.open(file_Name);

    while(!ifile.eof()) {
        getline(ifile, line);
        cout << "\033[34m" << std::setw(3) << iterator << " " << "\033[37m" << line << endl;
        iterator++;
    }
    system("pause");
}

void TextEditor::writeFile() {
    string line;
    ofile.open(file_Name);

    cin.ignore();
    int i = 1; // Untuk menghindari enter enter pertama pada input txt
    while(line != "END.") {
        getline(cin, line);        
        
        if(line == "END.")
            break;

        if (i == 1){
            ofile << line;
            i++;
        } else 
            ofile << endl << line ;
    }
}

int main() {
    bool breakingPoint = true;
    
    while(breakingPoint) {
        int check = menu();
        
        switch(check) {
            case 1: {
                string file_Name;
                cout << "Enter a file name and its coresponding extension : ";
                cin >> file_Name;
                system("CLS");
                TextEditor myText(file_Name);
                myText.writeFile();
                break;
            };

            case 2: {
                string file_Name;
                cout << "Enter the name file and its extension to open : ";
                cin >> file_Name;
                system("CLS");
                TextEditor myText(file_Name);
                myText.readFile();
                break;
            }

            case 3: {
                string file_Name;
                cout << "Enter the name file and its extension to open : ";
                cin >> file_Name;
                system("CLS");
                TextEditor myText(file_Name);
                myText.readFileEdit();
                myText.modifyFile();
                // myText.printLinkedList();
                system("pause");
                break;
            }

            case 4: {
            }
            break;

            case 0:
                breakingPoint = false;
            break;

            default:                
                break;
        }
    }
    
    return 0;
}