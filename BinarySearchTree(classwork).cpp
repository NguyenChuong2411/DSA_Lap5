#include <iostream>
#include <queue>
#include <cmath> // For checking balance (sqrt)
using namespace std;

// Definition for a binary tree node
class Node
{
public:
    int data;
    Node *left;
    Node *right;

    // Constructor for creating a new node
    Node(int value)
    {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// Binary Search Tree (BST) Class
class BinarySearchTree
{
private:
    Node *root;

    // Helper method to insert a value
    Node *insert(Node *node, int value)
    {
        if (node == nullptr)
        {
            return new Node(value);
        }

        if (value < node->data)
        {
            node->left = insert(node->left, value);
        }
        else
        {
            node->right = insert(node->right, value);
        }

        return node;
    }

    // Helper method to find the minimum value node
    Node *findMin(Node *node)
    {
        while (node && node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    // Helper method to find the maximum value node
    Node *findMax(Node *node)
    {
        while (node && node->right != nullptr)
        {
            node = node->right;
        }
        return node;
    }

    // Helper method to calculate the height of the tree
    int height(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return 1 + max(leftHeight, rightHeight);
    }

    // Helper method to check if the tree is balanced
    bool isBalanced(Node *node)
    {
        if (node == nullptr)
        {
            return true;
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return abs(leftHeight - rightHeight) <= 1 && isBalanced(node->left) && isBalanced(node->right);
    }

    // Helper method to check if a value exists in the tree
    bool search(Node *node, int key)
    {
        if (node == nullptr)
        {
            return false;
        }

        if (node->data == key)
        {
            return true;
        }
        else if (key < node->data)
        {
            return search(node->left, key);
        }
        else
        {
            return search(node->right, key);
        }
    }

    // Helper method to perform pre-order traversal
    void preorder(Node *root)
    {
        if (root != nullptr)
        {
            cout << root->data << " ";
            preorder(root->left);
            preorder(root->right);
        }
    }

    // Helper method to perform in-order traversal
    void inorder(Node *root)
    {
        if (root != nullptr)
        {
            inorder(root->left);
            cout << root->data << " ";
            inorder(root->right);
        }
    }

    // Helper method to perform post-order traversal
    void postorder(Node *root)
    {
        if (root != nullptr)
        {
            postorder(root->left);
            postorder(root->right);
            cout << root->data << " ";
        }
    }

    // Helper method to perform level-order traversal
    void levelorder(Node *root)
    {
        if (root == nullptr)
            return;

        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            Node *current = q.front();
            cout << current->data << " ";
            q.pop();

            if (current->left != nullptr)
                q.push(current->left);
            if (current->right != nullptr)
                q.push(current->right);
        }
    }

    // Helper method to calculate the diameter of the tree
    int diameterHelper(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        int currentDiameter = leftHeight + rightHeight;

        int leftDiameter = diameterHelper(node->left);
        int rightDiameter = diameterHelper(node->right);

        return max(currentDiameter, max(leftDiameter, rightDiameter));
    }

    // Helper method to find the LCA of two nodes
    Node *findLCAHelper(Node *node, int n1, int n2)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (n1 < node->data && n2 < node->data)
        {
            return findLCAHelper(node->left, n1, n2);
        }

        if (n1 > node->data && n2 > node->data)
        {
            return findLCAHelper(node->right, n1, n2);
        }

        return node;
    }
    // Helper method to perform level-order traversal and return results in levels
    vector<vector<int>> levelOrder(Node *root)
    {
        vector<vector<int>> levels;
        if (root == nullptr)
            return levels;

        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            int levelSize = q.size();
            vector<int> currentLevel;

            for (int i = 0; i < levelSize; i++)
            {
                Node *current = q.front();
                q.pop();
                currentLevel.push_back(current->data);

                if (current->left != nullptr)
                    q.push(current->left);
                if (current->right != nullptr)
                    q.push(current->right);
            }

            levels.push_back(currentLevel);
        }

        return levels;
    }
    // Helper method to find the maximum path sum
    int maxPathSumHelper(Node *node, int &maxSum)
    {
        if (node == nullptr)
            return 0;

        // Recursively find the maximum sum in the left and right subtrees
        int leftSum = max(0, maxPathSumHelper(node->left, maxSum));   // Ignore negative sums
        int rightSum = max(0, maxPathSumHelper(node->right, maxSum)); // Ignore negative sums

        // Current path sum includes the node and both subtrees (if beneficial)
        int currentSum = node->data + leftSum + rightSum;

        // Update global maximum sum
        maxSum = max(maxSum, currentSum);

        // Return the maximum path sum that can be extended upwards
        return node->data + max(leftSum, rightSum);
    }

public:
    // Constructor to initialize the root to nullptr
    BinarySearchTree()
    {
        root = nullptr;
    }

    void insert(int value)
    {
        root = insert(root, value);
    }

    int findMin()
    {
        Node *minNode = findMin(root);
        return minNode ? minNode->data : -1;
    }

    int findMax()
    {
        Node *maxNode = findMax(root);
        return maxNode ? maxNode->data : -1;
    }

    int height()
    {
        return height(root);
    }

    bool isBalanced()
    {
        return isBalanced(root);
    }

    void preorder()
    {
        cout << "Pre-order traversal: ";
        preorder(root);
        cout << endl;
    }

    void inorder()
    {
        cout << "In-order traversal: ";
        inorder(root);
        cout << endl;
    }

    void postorder()
    {
        cout << "Post-order traversal: ";
        postorder(root);
        cout << endl;
    }

    void levelorder()
    {
        cout << "Level-order traversal: ";
        levelorder(root);
        cout << endl;
    }

    bool search(int value)
    {
        return search(root, value);
    }

    int diameter()
    {
        return diameterHelper(root);
    }

    Node *findLCA(int n1, int n2)
    {
        return findLCAHelper(root, n1, n2);
    }
    // Method to return the level-order traversal as a vector of vectors
    vector<vector<int>> getLevelOrder()
    {
        return levelOrder(root);
    }
    // Display level-order traversal
    void displayLevelOrder()
    {
        vector<vector<int>> levels = getLevelOrder();
        for (const auto &level : levels)
        {
            for (int value : level)
            {
                cout << value << " ";
            }
            cout << endl;
        }
    }
    // Method to find the maximum path sum in the binary tree
    int maxPathSum()
    {
        int maxSum = -(1 << 31); // Initialize the global maximum sum
        maxPathSumHelper(root, maxSum);
        return maxSum;
    }
};

void displayMenu()
{
    cout << "Binary Search Tree Operations:\n";
    cout << "1. Insert Node into Tree\n";
    cout << "2. Search for a Value\n";
    cout << "3. Display Level-order Traversal\n";
    cout << "4. Display Pre-order Traversal\n";
    cout << "5. Display In-order Traversal\n";
    cout << "6. Display Post-order Traversal\n";
    cout << "7. Display Level-order Traversal\n";
    cout << "8. Find Minimum Value\n";
    cout << "9. Find Maximum Value\n";
    cout << "10. Check if Tree is Balanced\n";
    cout << "11. Get Height of the Tree\n";
    cout << "12. Get Diameter of the Tree\n";
    cout << "13. Find Lowest Common Ancestor (LCA)\n";
    cout << "14. Find Maximum Path Sum\n";
    cout << "15. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name : Nguyen Chu Nguyen Chuong\n";
    cout << "Exercise-Lap5\n";
    cout << "\n";
    BinarySearchTree tree;
    int choice, value, n1, n2;

    while (true)
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            tree.insert(value);
            break;

        case 2:
            cout << "Enter value to search: ";
            cin >> value;
            if (tree.search(value))
                cout << value << " found in the tree.\n";
            else
                cout << value << " not found in the tree.\n";
            break;
        case 3:
            cout << "Level-order traversal:\n";
            tree.displayLevelOrder();
            break;
        case 4:
            tree.preorder();
            break;

        case 5:
            tree.inorder();
            break;

        case 6:
            tree.postorder();
            break;

        case 7:
            tree.levelorder();
            break;

        case 8:
            cout << "Minimum value: " << tree.findMin() << endl;
            break;

        case 9:
            cout << "Maximum value: " << tree.findMax() << endl;
            break;

        case 10:
            cout << "Is the tree balanced? " << (tree.isBalanced() ? "Yes" : "No") << endl;
            break;

        case 11:
            cout << "Height of the tree: " << tree.height() << endl;
            break;

        case 12:
            cout << "Diameter of the tree: " << tree.diameter() << endl;
            break;

        case 13:
        {
            cout << "Enter two values to find LCA: ";
            cin >> n1 >> n2;
            Node *lca = tree.findLCA(n1, n2);
            if (lca != nullptr)
                cout << "LCA of " << n1 << " and " << n2 << ": " << lca->data << endl;
            else
                cout << "LCA not found!" << endl;
            break;
        }
        case 14:
            cout << "Maximum path sum: " << tree.maxPathSum() << endl;
            break;
        case 15:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}
