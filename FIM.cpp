#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

int menu() {
    int choices;

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
    cout << "4. Delete a line from a file" << endl;
    cout << "5. Exit\n";
    cout << "Enter your choices . . .    ";
    cin >> choices;

    return choices;
}

struct Filenote {
    string line;
    Filenote* next;
};

Filenote *head =NULL , *tail = NULL, *cur, *newNode, *del, *nextNode;

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
        void addLine(string);
        void modifyLine(); // editLine berhubungan dengan edit line
        void editLine(string, int); // editLine membutuhkan parameter dari modifyLine
        void readFileEdit(int);
        void removeLine();
        void removeLinkedList(Filenote*&);
        void printLinkedList();
        ~TextEditor() {}
};

void TextEditor::addLine(string line){
    newNode = new Filenote();
    newNode->line = line;
    newNode->next = NULL;
    tail-> next = newNode; 
    head = newNode;
}

void TextEditor::modifyLine(){
    readFile();
    int ch;
    string editInput;
    cout << "Insert number of line to edit: ";
    cin >> ch;
    cout << "Insert sentence: ";
    cin >> editInput;
    readFileEdit(ch);
    editLine(editInput, ch);
    printLinkedList();
}

void TextEditor::readFileEdit(int posisi){
    int iterator = 1;
    string line;

    ifile.open(file_Name);

    while(iterator != posisi) {
        getline(ifile, line);
        addLine(line);
        cout << line << endl;
        iterator++;
    }
}

void TextEditor::editLine(string line, int posisi){
    if (line == "") {
        del = tail;
        cur = head;

        while (cur->next != tail) {
            cur = cur->next;
        }
        
        tail = cur;
        tail->next = NULL;
        delete del;
    } else {
        tail->line = line;
    }
}

// menghapus baris yang diinginkan
void TextEditor::removeLine() {
    readFile();
    int ch;
    cout << "Insert number of line to remove: ";
    cin >> ch;
}

// fungsi untuk mengprint linked list ke output
void TextEditor::printLinkedList(){
    string line;
    ofile.open(file_Name);
    cin.ignore();
    int i = 1; // untuk menghindari enter di akhir file output
    cur = head;
    while(line != "END.") {
        line = cur->line;
        if(line == "END.")
            break;

        if (i == 1){
            ofile << line;
            cur = cur->next;
            i++;
        } else 
            ofile << endl << line ;
            cur = cur->next;
    }
    ofile.close();
    // removeLinkedList();
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
                myText.modifyLine();
                break;
            }

            case 4:
            break;

            case 5:
                breakingPoint = false;
            break;

            default:                
                break;
        }
    }
    
    return 0;
}