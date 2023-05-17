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

Filenote *head = NULL, *tail = NULL, *cur, *newNode, *del, *nextNode;

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
        void createLineLinkedList(string);
        void addFirstLine(string);
        void addLastLine(string);
        void modifyLine(); // editLine berhubungan dengan edit line
        void editLine(string, int); // editLine membutuhkan parameter dari modifyLine
        void readFileEdit();
        void removeLine();
        void removeLinkedList(Filenote*&);
        void printLinkedList();
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
    }}

void TextEditor::modifyLine(){
    readFile();
    int ch;
    readFileEdit();
    string editInput;
    cout << "Insert number of line to edit: ";
    cin >> ch;
    cout << "Insert sentence: ";
    cin >> editInput;
    // editLine(editInput, ch);
    system("pause");
    printLinkedList();
}

void TextEditor::readFileEdit(){
    cout << "ini tes readFileEdit dari file: " << file_Name << endl;
    int iterator = 1;
    string line;

    ifile.open(file_Name);

    if (ifile.is_open()) {
        cout << "openfile" << endl;
        while (getline(ifile, line)) {
            cout << "ini while" << endl;
            if (iterator == 1) {
                cout << line << endl;
                createLineLinkedList(line);
            } else if (iterator == 2) {
                cout << line << endl;
                addFirstLine(line);
            }
            else {
                cout << line << endl;
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
void TextEditor::printLinkedList() {
    ofile.open(file_Name);
    cout << "ini tes printLinkedList dari file: " << file_Name << endl;
    cin.ignore();
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
                system("pause");
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