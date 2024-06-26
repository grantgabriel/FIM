/******************************************
*                                         * 
*    A C++, Terminal Based Text Editor    *
*                                         *
*              By Us, Group 1             *
*                                         *
******************************************/

// Group member = (Main Contributor) =>

// -> R Khairu Wahyutama (221402051)
// -> Grant Gabriel Tambunan (221402057)
// -> Khalil Ramzy (221402110)
// -> Jeremy Sharon (221402107)

/* For more documentation, please check out our github! */
// {{ https://github.com/grantgabriel/FIM }} 

// Feel free to make a pull request or ask for contribution, we'll be happy to check it out! 

// {{ Library, package and defining declaration start }}

#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <string>
using namespace std;
namespace fs = filesystem;

#define RESET_TEXT "\033[0m"	     // Reset special formatting (such as colour).
#define BLACK_TEXT "\033[30m"	     // Black text.
#define RED_TEXT "\033[31m"	         // Red text.
#define GREEN_TEXT "\033[32m"	     // Green text.
#define YELLOW_TEXT "\033[33m"	     // Yellow text.
#define BLUE_TEXT "\033[34m"	     // Blue text.
#define MAGENTA_TEXT "\033[35m"	     // Magenta text.
#define CYAN_TEXT "\033[36m"	     // Cyan text.
#define WHITE_TEXT "\033[37m"	     // White text.
#define WHITE_BACKGROUND "\033[47m"  // White background.
#define BLACK_BACKGROUND "\033[40m"  // Black background.

// {{ Library, package and defining declaration start }}

// {{ Public Function Start }}

// Menu function for UI
int menu() {
    int choice;

    system("CLS");
    cout << BLUE_TEXT;
    cout << "\t\t\t\t\t\t\t  FIM - Fi IMproved" << endl;
    cout << GREEN_TEXT;
    cout << "\t\t\t\t\t\t\t    Version 1.0.2\n" << endl;
    cout << YELLOW_TEXT;
    cout << "\t\t\t\t\t     FIM is open source and freely distributed." << endl;
    cout << "\t\t\t\t\t        Feel free to check our github repos!" << endl;
    cout << "\t\t\t\t\t            github.com\\grantgabriel\\FIM\n" << "\n" << endl;
    cout << WHITE_TEXT;
    cout << "0. Exit                                " << endl;
    cout << "1. Create a new file                   " << endl;
    cout << "2. Read and open from an existing file " << endl;
    cout << "3. Edit a line from a file             " << endl;
    cout << "4. Delete file                         " << endl;
    cout << "5. Compile code (C++)                  " << endl;
    cout << "6. Run an app file                     " << endl;
    cout << "7. Print out directory                 " << endl;
    cout << "8. Make new directory                  " << endl;
    cout << "9. Delete empty directory              " << endl;
    cout << "10. Edit an directory name             " << endl;
    cout << "11. Edit an file name                  " << endl;
    cout << "Enter your choice . . .                " << endl;
    cout << "$ ";
    cin >> choice;

    return choice;
}

// A menu function for choices around edit.
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

// Function to ask a file name.
string askFileName (string query) {
    string fileName;
    cout << "Enter the name file and its extension to " << query << " : ";
    cin.ignore();
    getline(cin, fileName);
    system("CLS");

    return fileName;
}

// {{ Public Function End }}

// {{ Linkedlist For Edit Start }}

struct Filenote {
    string line;
    Filenote* next;
};

Filenote *head = NULL, *tail = NULL, *cur, *newNode, *nextNode, *del;

// {{ Linkedlist For Edit End }}

class TextEditor {
    private:
        string file_Name;
        ofstream ofile;
        ifstream ifile;
        
    public: 
        TextEditor(string file_Name = "file.txt") {this->file_Name = file_Name;} // Constructor
        // Default function (Create and read)
            void writeFile();                       // Method for writing a file.                                       [[-> Khalil Ramzy]]
            bool readFile();                        // Method for read a file.                                          [[-> Jeremy Sharon]]

        // Edit function /w linkedlists
            void createLineLinkedList(string);      // Make the first node of linked list.                              [[-> R. Khairu]]
            void addFirstLine(string);              // Add the node to the first linked list, used for add line.        [[-> R. Khairu]]
            void addMiddleLine(string, int);        // Add the node at the position by the parameter.                   [[-> R. Khairu]]
            void addLastLine(string);               // Add the node at the last position of linked list.                [[-> R. Khairu]]
            void removeLinkedList(Filenote*&);      // Removing all node from linked list.                              [[-> R. Khairu]]
            void printLinkedList();                 // Print linked list to file.                                       [[-> R. Khairu]]
            int countLinkedList();                  // Count node in linked list.                                       [[-> R. Khairu]]
            
        // Modify (Edit and Delete) and run it.  
            void readFileEdit();                    // Read a file to add into linkedlist.                              [[-> Grant Gabriel]]
            void modifyFile();                      // A controller method for modifying file.                          [[-> Grant Gabriel]]
            void editLine(int);                     // Edit line at position passed by parameter.                       [[-> Grant Gabriel]]
            void addLine();                         // Menu controller for adding a line.                               [[-> Grant Gabriel]] 
            void removeLine();                      // Removing a line.                                                 [[-> Grant Gabriel]] 
            void deleteFile();                      // Method for deleting a file.                                      [[-> Khalil Ramzy]]
            void compileCode();                     // Method for compiling a C++ file.                                 [[-> Jeremy Sharon]]
        
        // File and directory management 
            void printDirectory();                  // Print the current directory.                                     [[-> Grant Gabriel]]
            void createDirectory();                 // Create a new directory.                                          [[-> Grant Gabriel]]
            void deleteAllEmptyDirectory();         // Delete all of the empty directory.                               [[-> Grant Gabriel]]
            void renameDirectory();                 // Rename a specific directory.                                     [[-> Grant Gabriel]]
            void renameFile();                      // Rename a specific filename.                                      [[-> Grant Gabriel]]

        ~TextEditor(){}; // Destructors
};

// Method to get a string and insert it into the first linkedlist.
void TextEditor::createLineLinkedList(string line) {
    head = new Filenote();
    head->line = line;
    head->next = NULL;
    tail = head;                    // Set tail to head, because this is the first node.
}

// To add node as the first node of the linkedlist.
void TextEditor::addFirstLine(string line) {
    newNode = new Filenote();
    newNode->line = line;
    newNode->next = head;           // Set next of "new node" to "head" because it's the first node.
    head = newNode;                 // Set head as the new node.
}

// To add a new line at the middle of a file.
void TextEditor::addMiddleLine(string line, int position) {
    newNode = new Filenote();
    newNode->line = line;
    cur = head;                     // Set current node as head.
    int count = 1;                  // Declare variable to counting loop until number of position passed.
    while (count < position - 1) { 
        cur = cur->next;            // Change current position to next position.
        count++;                    
    }

    newNode->next = cur->next;      // Set the new node "next" to current "next" that have been looped.
    cur->next = newNode;            // Set the next of current node as the new node.
}

// To add a line at the last line of the text.
void TextEditor::addLastLine(string line) {
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
int TextEditor::countLinkedList() {
    cur = head;
    int count = 1;
    while (cur->next != nullptr) {
        cur = cur->next;
        count++;
    }

    return count;
}

// Module to open an file and insert it into the linkedlist for editing.
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

// A menu controller function around modifying a file.
void TextEditor::modifyFile() {
    if (readFile()) {
        bool breakPoint = true;
        while (breakPoint) {
            readFileEdit();
            switch (editMenu()) {
                case 1:
                    addLine();
                    break;

                case 2:
                    cout << "Enter which line number you want to edit: ";
                    int line;
                    cin >> line;
                    editLine(line);
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

            if (breakPoint) {
                system("CLS");
                readFile();
            }
        }
    }
}

// A function to add a string into any line wanted.
void TextEditor::addLine() {
    readFileEdit();
    int ch;
    string newLine;
    cout << "Enter which line number you want to add: ";
    cin >> ch;
    cout << "Insert the new line: ";
    cin.ignore();
    getline(cin, newLine);

    if(ch == 1) 
        addFirstLine(newLine);
    else if(ch > 1 && ch < countLinkedList())
        addMiddleLine(newLine, ch);
    else if(ch == countLinkedList())
        addLastLine(newLine);
    else {
        cout << "Failed to add line, are you sure you add at valid line?" << endl;
        cout << "You can add line between 1-" << countLinkedList() << " only!";
        system("PAUSE");
    }

    printLinkedList();
}

void TextEditor::editLine(int ch) {
    cur = head;
    int count = 1;
    // To find the line we want to edit.
    while (cur != nullptr && count < ch) {
        cur = cur ->next;
        count++;
    }

    // If not found, it will exit by returning nothing.
    if (cur == nullptr) {
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

// Delete a selected line.
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


// Remove all linkedlist for saving memory.
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
    if (ifile.is_open()) {
        while(!ifile.eof()) {
            getline(ifile, line);
            cout << BLUE_TEXT << std::setw(3) << iterator << "| " << WHITE_TEXT << line << endl;
            iterator++;
        }
        
        ifile.close();
        system("PAUSE");
        return true;
    } else {
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
        
        if(line == "END.") break;

        if (i == 1) {
            ofile << line;
            i++;
        } else ofile << endl << line ;
    }
}

// Function to delete a file.
void TextEditor::deleteFile() {
    const char* c_filename = file_Name.c_str();

    // Remove the file using remove() function from <cstdio>.
    if (remove(c_filename) == 0)
        cout << "File '" << file_Name << "' deleted successfully.\n";
    else
        cout << "Failed to delete file '" << file_Name << "'.\n";
    
}

// Function to compile a C++ file.
void TextEditor::compileCode() {
    // Build the compilation command.
    string command = "g++ -o " + file_Name.substr(0, file_Name.find_last_of('.')) + " " + file_Name;

    // Execute the compilation command using system().
    int result = system(command.c_str());

    if (result == 0)
        cout << "Code compiled successfully.\n";
    else
        cout << "Compilation failed.\n";

    system("PAUSE");
}

void TextEditor::printDirectory() {
    string path = ".";

    try {
          if (fs::exists(path) && fs::is_directory(path)) {
              for (const auto& entry : fs::directory_iterator(path)) {
                  std::cout << entry.path().string() << std::endl;
              }
          } else {
              std::cerr << "Path does not exist or is not a directory." << std::endl;
          }
      } catch (const fs::filesystem_error& e) {
          std::cerr << "Filesystem error: " << e.what() << std::endl;
      } catch (const std::exception& e) {
          std::cerr << "General error: " << e.what() << std::endl;
      }
}

void TextEditor::createDirectory() {
    string path = file_Name;
    
    try {
        if (fs::exists(path)) {
            std::cerr << "Directory already exists." << std::endl;
        } else {
            if (fs::create_directory(path)) {
                std::cout << "Directory created: " << path << std::endl;
            } else {
                std::cerr << "Failed to create directory." << std::endl;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "General error: " << e.what() << std::endl;
    }
}

void TextEditor::deleteAllEmptyDirectory() {
    string path = ".";
    
    try {
        if (fs::exists(path) && fs::is_directory(path)) {
            for (const auto& entry : fs::directory_iterator(path)) {
                if (fs::is_directory(entry.status()) && fs::is_empty(entry.path())) {
                    fs::remove(entry.path());
                    std::cout << "Deleted empty directory: " << entry.path().string() << std::endl;
                }
            }
        } else {
            std::cerr << "Path does not exist or is not a directory." << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "General error: " << e.what() << std::endl;
    }
}

void TextEditor::renameDirectory() {
    string old_name = file_Name;
    cout << "Enter the new folder name: ";
    string new_name;

    getline(cin, new_name);
    try {
        if (fs::exists(old_name) && fs::is_directory(old_name)) {
            fs::rename(old_name, new_name);
            std::cout << "Renamed folder: " << old_name << " to " << new_name << std::endl;
        } else {
            std::cerr << "Folder does not exist or is not a folder: " << old_name << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "General error: " << e.what() << std::endl;
    }
}

void TextEditor::renameFile() {
    string old_name = file_Name;
    cout << "Enter the new file name: ";
    string new_name;

    getline(cin, new_name);
    try {
        if (fs::exists(old_name) && fs::is_regular_file(old_name)) {
            fs::rename(old_name, new_name);
            std::cout << "Renamed file: " << old_name << " to " << new_name << std::endl;
        } else {
            std::cerr << "File does not exist or is not a regular file: " << old_name << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "General error: " << e.what() << std::endl;
    }
}

int main() {
    bool breakingPoint = true;
    
    while(breakingPoint) {
        switch(menu()) {
            case 1: {
                string file_Name = askFileName("create");
                TextEditor myText(file_Name);
                myText.writeFile();
                break;
            }

            case 2: {
                string file_Name = askFileName("open");
                TextEditor myText(file_Name);
                myText.readFile();
                break;
            }

            case 3: {
                string file_Name = askFileName("open");
                TextEditor myText(file_Name);
                myText.modifyFile();
                break;
            }

            case 4: {
                string file_Name = askFileName("delete");
                TextEditor myText(file_Name);
                myText.deleteFile();
                system("PAUSE");
                break;
            }
            
            case 5: {
                string file_Name = askFileName("to compile (C++)");
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
                system(file_Name.c_str()); // Basically run the program into the system.
                cout << endl;
                system("PAUSE");
                break;
            }

            case 7: {
                system("CLS");
                TextEditor myText("bloop.txt");
                myText.printDirectory();
                system("PAUSE");
                break;
            }

            case 8: {
                string folder_name;
                cout << "Enter the directory name to create : ";
                cin.ignore();
                getline(cin, folder_name);
                TextEditor myText(folder_name);
                system("CLS");
                myText.createDirectory();
                system("PAUSE");
                break;
            }

            case 9: {
                TextEditor myText("bloop.txt");
                system("CLS");
                myText.deleteAllEmptyDirectory();
                system("PAUSE");
                break;
            }

            case 10: {
                string folder_name;
                cout << "Enter the folder name to rename : ";
                cin.ignore();
                getline(cin, folder_name);
                TextEditor myText(folder_name);
                system("CLS");
                myText.renameDirectory();
                system("PAUSE");
                break;
            }
            
            case 11: {
                string file_Name;
                cout << "Enter the file name to rename : ";
                cin.ignore();
                getline(cin, file_Name);
                TextEditor myText(file_Name);
                system("CLS");
                myText.renameFile();
                system("PAUSE");
                break;
            }

            case 0:
                breakingPoint = false; // Exit condition.
            break;

            default:                
                break;
        }
    }
    
    return 0;
}
