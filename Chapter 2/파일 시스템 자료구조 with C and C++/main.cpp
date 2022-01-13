#include "SimpleFileSystemHeader.h"

void Search(FileTree* tree)
{
    std::string name = "";
    std::cout << "File Name : ";
    std::cin >> name;
    
    if(tree->Find(name))
        std::cout << "\nFile Exists" << '\n';
    else
        std::cout << "\nFile doesn't exist" << '\n';
}

void Change(FileTree* tree)
{
    std::string name = "";
    std::cout << "Directory Name : ";
    std::cin >> name;
    
    if(tree->ChangeWorkingDir(name))
        std::cout << "\nDirectory change succeeded..." << '\n';
    else
        std::cout << "\nDirectory change failed..." << '\n';
}

void Add(FileTree* tree)
{
    char input = 0;
    
    std::string name = "";
    std::cout << "File Name : ";
    std::cin >> name;
    
    std::cout << "Is it a regular file? (y / n) : ";
    std::cin >> input;
    switch(input)
    {
        case 'y':
            tree->AddFile(name,REGULAR);
            break;
        case 'n':
            tree->AddFile(name,DIRECTORY);
            break;
        default:
            std::cerr << "wrong input detected..." << '\n';
            break;
    }
}

void Print(FileTree* tree)
{
    std::string name = "";
    std::cout << "File Name : ";
    std::cin >> name;
    
    tree->Print(name);
}

int main(int argc,char* argv[])
{
    FileTree* root = new FileTree("/Users/choiyoungrim/Algorithm_C++",0);
    
    while(1)
    {
        int input = 0;
        
        std::cout << "Current Directory : ";
        root->PrintCurrentDirectory();
        
        std::cout << "\n1 : Search\n2 : Print\n3 : Add\n4 : Change\n5 : End\n";
        
        std::cout << "Input : ";
        std::cin >> input;
        
        switch(input)
        {
            case SEARCH:
                Search(root);
                break;
            case PRINT:
                Print(root);
                break;
            case ADD:
                Add(root);
                break;
            case CHANGE:
                Change(root);
                break;
            case END:
                delete root;
                return 0;
        }
    }
}
