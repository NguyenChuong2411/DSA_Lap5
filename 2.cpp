#include <iostream>
#include <string>

using namespace std;

const int MAX_CHILDREN = 10; // Max children per node (for simplicity)

// Function to check if a character is an alphabetic letter
bool isAlpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Node class to represent each element in the XML/HTML document
class Node
{
public:
    string tagName;                  // Tag name (e.g., "div", "p", etc.)
    string attrNames[MAX_CHILDREN];  // Names of the attributes
    string attrValues[MAX_CHILDREN]; // Values of the attributes
    int numAttributes;               // Number of attributes
    Node *children[MAX_CHILDREN];    // Array of children nodes
    int numChildren;                 // Number of children
    Node *parent;                    // Pointer to parent node

    Node(const string &name, Node *parentNode = nullptr) : tagName(name), numAttributes(0), numChildren(0), parent(parentNode) {}

    // Add a child node
    void addChild(Node *child)
    {
        if (numChildren < MAX_CHILDREN)
        {
            children[numChildren++] = child;
        }
    }

    // Add an attribute to the node
    void addAttribute(const string &name, const string &value)
    {
        if (numAttributes < MAX_CHILDREN)
        {
            attrNames[numAttributes] = name;
            attrValues[numAttributes] = value;
            numAttributes++;
        }
    }

    // Query an attribute by name
    string getAttribute(const string &name)
    {
        for (int i = 0; i < numAttributes; i++)
        {
            if (attrNames[i] == name)
            {
                return attrValues[i];
            }
        }
        return ""; // Attribute not found
    }
};

// Parser class to read the XML/HTML document and build the tree structure
class Parser
{
private:
    string document;
    Node *root;        // Root of the document tree
    Node *currentNode; // Current node being processed
    size_t pos;        // Position in the string

public:
    Parser(const string &doc) : document(doc), root(nullptr), currentNode(nullptr), pos(0) {}

    // Function to parse the document
    void parse()
    {
        while (pos < document.size())
        {
            parseTag();
        }
    }

    // Function to parse a tag in the document
    void parseTag()
    {
        skipWhitespace();

        if (pos >= document.size())
            return;

        if (document[pos] == '<')
        {
            pos++; // Skip '<'

            // Check for closing tag (e.g., </div>)
            if (document[pos] == '/')
            {
                pos++; // Skip '/'
                string tagName = readTagName();
                skipWhitespace();
                if (document[pos] == '>')
                {
                    pos++; // Skip '>'
                    if (currentNode && currentNode->tagName == tagName)
                    {
                        currentNode = currentNode->parent; // Move up to parent
                    }
                }
            }
            else
            { // Opening tag (e.g., <div>)
                string tagName = readTagName();
                Node *newNode = new Node(tagName, currentNode);

                if (!currentNode)
                {
                    root = newNode; // Root node
                }
                else
                {
                    currentNode->addChild(newNode); // Add as child
                }

                currentNode = newNode; // Move down to new node
                parseAttributes();
                skipWhitespace();

                if (document[pos] == '>')
                {
                    pos++; // Skip '>'
                }
            }
        }
    }

    // Read the tag name from the document
    string readTagName()
    {
        skipWhitespace();
        size_t start = pos;
        while (pos < document.size() && isAlpha(document[pos]))
        {
            pos++;
        }
        return document.substr(start, pos - start);
    }

    // Parse the attributes inside an opening tag
    void parseAttributes()
    {
        skipWhitespace();
        while (pos < document.size() && document[pos] != '>')
        {
            string attrName = readAttributeName();
            skipWhitespace();

            if (document[pos] == '=')
            {
                pos++; // Skip '='
                skipWhitespace();
                string attrValue = readAttributeValue();
                currentNode->addAttribute(attrName, attrValue);
            }

            skipWhitespace();
        }
    }

    // Read an attribute name
    string readAttributeName()
    {
        size_t start = pos;
        while (pos < document.size() && isAlpha(document[pos]))
        {
            pos++;
        }
        return document.substr(start, pos - start);
    }

    // Read an attribute value
    string readAttributeValue()
    {
        if (document[pos] == '"')
        {
            pos++; // Skip the opening quote
            size_t start = pos;
            while (pos < document.size() && document[pos] != '"')
            {
                pos++;
            }
            string value = document.substr(start, pos - start);
            pos++; // Skip closing quote
            return value;
        }
        return ""; // If no value found
    }

    // Skip whitespace characters
    void skipWhitespace()
    {
        while (pos < document.size() && (document[pos] == ' ' || document[pos] == '\n' || document[pos] == '\t'))
        {
            pos++;
        }
    }

    // Function to query for elements by tag name
    void queryByTagName(const string &tagName)
    {
        queryByTagNameHelper(root, tagName);
    }

    // Helper function to recursively search for elements by tag name
    void queryByTagNameHelper(Node *node, const string &tagName)
    {
        if (!node)
            return;
        if (node->tagName == tagName)
        {
            cout << "<" << node->tagName << ">" << endl;
        }

        for (int i = 0; i < node->numChildren; i++)
        {
            queryByTagNameHelper(node->children[i], tagName);
        }
    }

    // Function to query for elements by attribute name
    void queryByAttribute(const string &attrName)
    {
        queryByAttributeHelper(root, attrName);
    }

    // Helper function to recursively search for elements by attribute name
    void queryByAttributeHelper(Node *node, const string &attrName)
    {
        if (!node)
            return;
        for (int i = 0; i < node->numAttributes; i++)
        {
            if (node->attrNames[i] == attrName)
            {
                cout << "<" << node->tagName << "> has attribute " << attrName << "=" << node->getAttribute(attrName) << endl;
            }
        }

        for (int i = 0; i < node->numChildren; i++)
        {
            queryByAttributeHelper(node->children[i], attrName);
        }
    }

    // Function to print the document tree (for debugging purposes)
    void printTree()
    {
        printTreeHelper(root, 0);
    }

    // Helper function to print the tree structure
    void printTreeHelper(Node *node, int depth)
    {
        if (!node)
            return;
        for (int i = 0; i < depth; i++)
        {
            cout << "  "; // Indentation
        }
        cout << "<" << node->tagName << ">" << endl;
        for (int i = 0; i < node->numChildren; i++)
        {
            printTreeHelper(node->children[i], depth + 1);
        }
    }
};

// Sample usage
int main()
{
    // Sample XML/HTML string (minimal example)
    string document = R"(
    <html>
        <body>
            <div id="main" class="container">
                <p>Hello World!</p>
            </div>
        </body>
    </html>
    )";

    // Create the parser and parse the document
    Parser parser(document);
    parser.parse();

    // Print the document structure
    cout << "Document Tree:" << endl;
    parser.printTree();

    // Query elements by tag name
    cout << "\nElements with tag 'div':" << endl;
    parser.queryByTagName("div");

    // Query elements by attribute (e.g., 'id')
    cout << "\nElements with attribute 'id':" << endl;
    parser.queryByAttribute("id");
    system("pause");
    return 0;
}
