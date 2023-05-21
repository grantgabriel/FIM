/******************************************
*                                         *
*    A C++, Terminal Based Text Editor    *
*                                         *
*            By Us, the Group             *
*                                         *
******************************************/

// Group member = () =>

// -> Grant Gabriel Tambunan (221402057)
// -> R Khairu Wahyutama (221402051)
// -> Khalil Ramzy (221402110)
// -> Jeremy Sharon (221402107)

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

// {{ Public Function Start }}

// Menu function for UI
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
    cout << "5. Compile code (C++)" << endl;
    cout << "6. Run an app file" << endl;
    cout << "0. Exit\n";
    cout << "Enter your choice . . .    ";
    cin >> choice;

    return choice;
}

// A function for choices around edit.
int editMenu () {
    int choice;
    cout << "1. Add new line" << endl;
    cout << "2. Edit Line"  << endl;
    cout << "3. Remove Line"  << endl;
    cout << "0. Back to menu"  << endl;
    cout << "Enter your choices . . .    ";
    cin >> choice;
    
    return choice;
}

// {{ Public Function Start }}

// {{ Linkedlist For Edit Start }}
struct Filenote {
    string line;
    Filenote* next;
};

Filenote *head = NULL, *tail = NULL, *cur, *newNode, *nextNode, *del;

bool isTailPosition(Filenote* head, int position) {
    cur = head;
    int length = 0;

    // Count the length of the linkedlist
    while (cur != nullptr) {
        length++;
        cur = cur->next;
    }

    // Check whether the position is the tail.
    if (position == length - 1) 
        return true;
    else 
        return false;
    
}

// {{ Linkedlist For Edit End }}

class TextEditor {
    private:
        string file_Name;
        ofstream ofile;
        ifstream ifile;
        
    public: 
        TextEditor(string file_Name = "file.txt") {this->file_Name = file_Name;} // Constructor
        // Default function (Create and read)
            void writeFile();
            bool readFile();

        // Edit function /w linkedlists
            void createLineLinkedList(string); 
            void addFirstLine(string);
            void addMiddleLine(string, int);
            void addLastLine(string); 
            void removeLinkedList(Filenote*&);
            void printLinkedList();
            int countLinkedList();
            
        // Modify (Edit and Delete) and run it.
            void modifyFile(); 
            void editLine(int); 
            void readFileEdit(); 
            void addline();
            void removeLine(); 
            void deleteFile();
            void compileCode();
            void runCode(const std::string&);

        ~TextEditor(){}; // Destructors
};

// To read the first line of the file, and then insert it into the linkedlist.
void TextEditor::createLineLinkedList(string line) {
    head = new Filenote();
    head->line = line;
    head->next = NULL;
    tail = head;
}

// To add node as the first node of the linkedlist.
void TextEditor::addFirstLine(string line){
    newNode = new Filenote();
    newNode->line = line;
    newNode->next = head;
    head = newNode;
}

// To add a new line at the middle of a file.
void TextEditor::addMiddleLine(string line, int position) {
    newNode = new Filenote();
    newNode->line = line;
    cur = head;
    int count = 1;
    while (count < position - 1){
        cur = cur->next;
        count++;
    }
    newNode->next = cur->next;
    cur->next = newNode;
}

// To add a line at the last line of the text
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

// Just to count all the node on the linkedlist.
int TextEditor::countLinkedList(){
    cur = head;
    int count = 1;
    while (cur->next != nullptr){
        cur = cur->next;
        count++;
    }
    return count;
}

void TextEditor::modifyFile(){
    if (readFile()) {
        bool breakPoint = true;
        while (breakPoint){
            readFileEdit();
            int ch, userChEdit = editMenu();
            switch (userChEdit){
                case 1:
                    addline();
                    break;
                case 2:
                    cout << "Enter which line number you want to edit: ";
                    cin >> ch;
                    editLine(ch);
                    break;
                case 3:
                    removeLine();
                    break;
                case 0:
                    breakPoint = false;
                    break;
                default:
                    break;
            }
            if (breakPoint){
                system("CLS");
                readFile();
            }
            
        }
        system("PAUSE");
    }
}

void TextEditor::readFileEdit() {
    string line;

    ifile.open(file_Name);
    if (ifile.is_open()) {
        int iterator = 1;

        while (!ifile.eof()) {
            getline(ifile, line);
            if (iterator == 1) 
                createLineLinkedList(line);
            else 
                addLastLine(line);
            
            iterator++;
        }
        ifile.close();
    } else {
        cout << "Failed to open the file." << endl;
    }
}

void TextEditor::addline()
{
    readFileEdit();
    int ch;
    string newLine;
    cout << "Enter which line number you want to add: ";
    cin >> ch;
    cout << "Insert the new line: ";
    cin.ignore();
    getline(cin, newLine);

    if (ch == 1) 
        addFirstLine(newLine);
    else if (ch > 1 && ch < countLinkedList())
        addMiddleLine(newLine, ch);
    else if (ch == countLinkedList())
        addLastLine(newLine);
    else {
        cout << "Failed to add line, are you sure you add at valid line?" << endl;
        cout << "You can add line between 1-" << countLinkedList() << " only!";
        system("PAUSE");
    }

    printLinkedList();
}

void TextEditor::editLine(int ch){
    // cout << head->line << endl;
    cur = head;
    int count = 1;
    // To find the line we want to edit.
    while (cur != nullptr && count < ch){
        cur = cur ->next;
        count++;
    }
    // If not found, it will exit by returning nothing.
    if (cur == nullptr){
        cout << "Line not found" << endl;
        system("PAUSE");
        return;
    } else {
        string newLine;
        cout << "Insert the new content: ";
        cin.ignore();
        getline(cin, newLine);
        cur->line = newLine;
        printLinkedList();
        system("PAUSE");
    }
}

// Delete a selected line
void TextEditor::removeLine() {
    readFileEdit();
    int ch, count = 1;
    cout << "Enter the line number you want to remove: ";
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
        // Rewrite all the file.
        printLinkedList();
        cout << "Line successfully removed." << endl;
        system("PAUSE");
    } else {
        cout << "Line not found." << endl;
        system("PAUSE");
    }
}

// Function to print the linkedlist into the file.
void TextEditor::printLinkedList() {
    ofile.open(file_Name);
    int i = 1; // To prevent an unwanted <ENTER> at the last line.
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


// Remove all linkedlist
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

// Function to read all line in a file.
bool TextEditor::readFile() {
    int iterator = 1;
    string line;

    ifile.open(file_Name);
    if (ifile.is_open()){
        while(!ifile.eof()) {
            getline(ifile, line);
            cout << "\033[34m" << std::setw(3) << iterator << " " << "\033[37m" << line << endl;
            iterator++;
        }
        ifile.close();
        system("PAUSE");
        return true;
    }
    else {
        cout << "Failed to open the file." << endl;
        system("PAUSE");    
        return false;
    }
}

// Function to write a file.
void TextEditor::writeFile() {
    string line;
    ofile.open(file_Name);
    
    cout << "Write your file, end it with \"END.\"" << endl;
    int i = 1; // To prevent an unwanted <ENTER> in the first line of the file.
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

// Function to delete a file.
void TextEditor::deleteFile() {
    const char* c_filename = file_Name.c_str();

    // Remove the file using remove() function from <cstdio>
    if (remove(c_filename) == 0)
        cout << "File '" << file_Name << "' deleted successfully.\n";
    else
        cout << "Failed to delete file '" << file_Name << "'.\n";
    
}

// Function to compile a C++ file
void TextEditor::compileCode() {
    // Build the compilation command
    string command = "g++ -o " + file_Name.substr(0, file_Name.find_last_of('.')) + " " + file_Name;

    // Execute the compilation command using system()
    int result = system(command.c_str());

    if (result == 0)
        cout << "Code compiled successfully.\n";
    else
        cout << "Compilation failed.\n";
    system("PAUSE");
}

int main() {
    bool breakingPoint = true;
    
    while(breakingPoint) {
        int check = menu();
        
        switch(check) {
            case 1: {
                string file_Name;
                cout << "Enter a file name and its coresponding extension : ";
                cin.ignore();
                getline(cin, file_Name);
                system("CLS");
                TextEditor myText(file_Name);
                myText.writeFile();
                break;
            };

            case 2: {
                string file_Name;
                cout << "Enter the name file and its extension to open : ";
                cin.ignore();
                getline(cin, file_Name);
                system("CLS");
                TextEditor myText(file_Name);
                myText.readFile();
                break;
            }

            case 3: {
                string file_Name;
                cout << "Enter the name file and its extension to open : ";
                cin.ignore();
                getline(cin, file_Name);
                system("CLS");
                TextEditor myText(file_Name);
                myText.modifyFile();
                break;
            }

            case 4: {
                string file_Name;
                cout << "Enter the name file and its extension to delete : ";
                cin.ignore();
                getline(cin, file_Name);
                system("CLS");
                TextEditor myText(file_Name);
                myText.deleteFile();
                system("PAUSE");
                break;
            }
            
            case 5: {
                string file_Name;
                cout << "Enter the name file and its extension to compile (CPP only) : ";
                cin.ignore();
                getline(cin, file_Name);
                TextEditor myText(file_Name);
                myText.compileCode();
                break;
            }

            case 6: {
                string file_Name;
                cout << "Enter the app file name to run : ";
                cin.ignore();
                getline(cin, file_Name);
                system("CLS");
                system(file_Name.c_str());
                cout << endl;
                system("PAUSE");
                break;
            }

            case 0:
                breakingPoint = false;
            break;

            default:                
                break;
        }
    }
    
    return 0;
}