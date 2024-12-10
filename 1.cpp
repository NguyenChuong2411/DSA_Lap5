#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Node class representing a file or directory
class FileSystemNode
{
public:
    string name;
    bool isDirectory;
    vector<FileSystemNode *> children;

    FileSystemNode(string name, bool isDirectory)
        : name(name), isDirectory(isDirectory) {}

    ~FileSystemNode()
    {
        for (auto child : children)
        {
            delete child;
        }
    }
};

// FileSystem class to represent the tree structure
class FileSystem
{
private:
    FileSystemNode *root;

public:
    FileSystem()
    {
        // Creating a root node representing the "root" directory
        root = new FileSystemNode("/", true);
    }

    ~FileSystem()
    {
        delete root;
    }

    // Helper function to split path into parts
    vector<string> splitPath(const string &path)
    {
        vector<string> parts;
        stringstream ss(path);
        string part;

        while (getline(ss, part, '/'))
        {
            if (!part.empty())
            { // Ignore empty parts from leading slashes
                parts.push_back(part);
            }
        }

        return parts;
    }

    // Helper function to find a node by path
    FileSystemNode *findNode(FileSystemNode *current, const vector<string> &pathParts)
    {
        if (pathParts.empty())
            return current;

        for (auto &child : current->children)
        {
            if (child->name == pathParts[0])
            {
                if (pathParts.size() == 1)
                {
                    return child; // Found the target node
                }
                // Recurse into the subdirectory
                return findNode(child, vector<string>(pathParts.begin() + 1, pathParts.end()));
            }
        }

        return nullptr; // Not found
    }

    // Navigating through the file system (simulated by printing the current directory's contents)
    void navigate(const string &path)
    {
        vector<string> pathParts = splitPath(path);
        FileSystemNode *currentNode = findNode(root, pathParts);

        if (currentNode && currentNode->isDirectory)
        {
            cout << "Contents of " << path << ":\n";
            for (const auto &child : currentNode->children)
            {
                cout << (child->isDirectory ? "[DIR] " : "[FILE] ") << child->name << "\n";
            }
        }
        else
        {
            cout << "Path not found or not a directory.\n";
        }
    }

    // Creating a new directory or file
    void create(const string &path, const string &name, bool isDirectory)
    {
        vector<string> pathParts = splitPath(path);
        FileSystemNode *currentNode = findNode(root, pathParts);

        if (currentNode && currentNode->isDirectory)
        {
            // Check if file/directory already exists
            bool exists = false;
            for (auto &child : currentNode->children)
            {
                if (child->name == name)
                {
                    exists = true;
                    break;
                }
            }
            if (exists)
            {
                cout << "Error: " << name << " already exists.\n";
                return;
            }
            // Create new node and add to current directory
            currentNode->children.push_back(new FileSystemNode(name, isDirectory));
            cout << (isDirectory ? "Directory " : "File ") << name << " created successfully.\n";
        }
        else
        {
            cout << "Invalid path or not a directory.\n";
        }
    }

    // Deleting a file or directory
    void deleteNode(const string &path, const string &name)
    {
        vector<string> pathParts = splitPath(path);
        FileSystemNode *currentNode = findNode(root, pathParts);

        if (currentNode && currentNode->isDirectory)
        {
            bool found = false;
            for (size_t i = 0; i < currentNode->children.size(); i++)
            {
                if (currentNode->children[i]->name == name)
                {
                    delete currentNode->children[i];
                    currentNode->children.erase(currentNode->children.begin() + i);
                    found = true;
                    cout << name << " deleted successfully.\n";
                    break;
                }
            }

            if (!found)
            {
                cout << "File/Directory not found.\n";
            }
        }
        else
        {
            cout << "Invalid path or not a directory.\n";
        }
    }

    // Display the entire file system (for visualization)
    void display()
    {
        displayRecursive(root, 0);
    }

private:
    void displayRecursive(FileSystemNode *node, int depth)
    {
        if (node == nullptr)
            return;

        // Print indentation based on depth
        for (int i = 0; i < depth; i++)
            cout << "  ";
        cout << (node->isDirectory ? "[DIR] " : "[FILE] ") << node->name << "\n";

        // Recursively display children if it's a directory
        if (node->isDirectory)
        {
            for (auto &child : node->children)
            {
                displayRecursive(child, depth + 1);
            }
        }
    }
};

int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name : Nguyen Chu Nguyen Chuong\n";
    cout << "Homework-Lap5\n";
    cout << "\n";
    FileSystem fs;

    // Sample operations
    fs.create("/", "Documents", true);                     // Create a directory in root
    fs.create("/Documents", "file1.txt", false);           // Create a file inside Documents
    fs.create("/Documents", "SubFolder", true);            // Create a subdirectory inside Documents
    fs.create("/Documents/SubFolder", "file2.txt", false); // Create a file inside SubFolder

    fs.navigate("/");                    // View contents of root directory
    fs.navigate("/Documents");           // View contents of Documents
    fs.navigate("/Documents/SubFolder"); // View contents of SubFolder

    fs.deleteNode("/Documents", "file1.txt");           // Delete a file
    fs.deleteNode("/Documents/SubFolder", "file2.txt"); // Delete a file from subfolder
    fs.deleteNode("/Documents", "SubFolder");           // Delete a subdirectory

    fs.display(); // Display entire file system structure
    system("pause");
    return 0;
}
