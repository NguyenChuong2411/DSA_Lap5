#include <iostream>
#include <queue>
#include <cmath>
#include <cstring> // For memset

using namespace std;

// Directions for moving up, down, left, right (4 cardinal directions)
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

const int MAX_SIZE = 100; // Maximum grid size

// Node structure to hold the data for each cell
struct Node
{
    int x, y;     // Position of the node in the grid
    int g;        // Cost from start to this node
    int h;        // Heuristic cost (estimated distance to goal)
    int f;        // Total cost (f = g + h)
    Node *parent; // Pointer to the parent node to reconstruct the path

    // Constructor to initialize a node
    Node(int x = 0, int y = 0, int g = 0, int h = 0, Node *parent = nullptr)
        : x(x), y(y), g(g), h(h), parent(parent)
    {
        f = g + h;
    }

    // Comparison operator to make Node work in a priority queue (min-heap)
    bool operator>(const Node &other) const
    {
        return f > other.f; // We want the smallest f value at the top
    }
};

// A* algorithm to find the shortest path from start to goal
class AStar
{
public:
    AStar(int rows, int cols, int grid[MAX_SIZE][MAX_SIZE])
        : rows(rows), cols(cols)
    {
        // Copy grid data
        memcpy(this->grid, grid, sizeof(this->grid));
    }

    // Perform the A* search to find the shortest path
    Node *findPath(pair<int, int> start, pair<int, int> goal)
    {
        priority_queue<Node, deque<Node>, greater<Node>> openList;
        bool closedList[MAX_SIZE][MAX_SIZE] = {false};

        int startX = start.first, startY = start.second;
        int goalX = goal.first, goalY = goal.second;

        // Allocate nodes dynamically to avoid stack overflow for large grids
        Node *nodes[MAX_SIZE][MAX_SIZE];
        memset(nodes, 0, sizeof(nodes));

        // Create the starting node and push it into the open list
        nodes[startX][startY] = new Node(startX, startY, 0, heuristic(startX, startY, goalX, goalY));
        openList.push(*nodes[startX][startY]);

        while (!openList.empty())
        {
            Node current = openList.top();
            openList.pop();

            if (current.x == goalX && current.y == goalY)
            {
                // Goal reached
                return nodes[current.x][current.y];
            }

            closedList[current.x][current.y] = true;

            // Check all 4 possible directions (up, down, left, right)
            for (int i = 0; i < 4; ++i)
            {
                int newX = current.x + dx[i];
                int newY = current.y + dy[i];

                // Check if the new position is within bounds and not an obstacle
                if (isValid(newX, newY) && !closedList[newX][newY] && grid[newX][newY] == 0)
                {
                    int newG = current.g + 1; // Assuming all movements cost 1
                    int newH = heuristic(newX, newY, goalX, goalY);

                    // If the node does not exist, create it
                    if (!nodes[newX][newY])
                    {
                        nodes[newX][newY] = new Node(newX, newY, newG, newH, nodes[current.x][current.y]);
                        openList.push(*nodes[newX][newY]);
                    }
                    else if (newG < nodes[newX][newY]->g)
                    {
                        // Update node if a better path is found
                        nodes[newX][newY]->g = newG;
                        nodes[newX][newY]->f = newG + newH;
                        nodes[newX][newY]->parent = nodes[current.x][current.y];
                        openList.push(*nodes[newX][newY]);
                    }
                }
            }
        }

        // No path found
        return nullptr;
    }

    // Reconstruct the path by following parent nodes
    void reconstructPath(Node *goalNode)
    {
        if (!goalNode)
        {
            cout << "No path found!\n";
            return;
        }

        cout << "Path found:\n";
        Node *current = goalNode;
        while (current)
        {
            cout << "(" << current->x << ", " << current->y << ")\n";
            current = current->parent;
        }
    }

    // Print the grid layout
    void printGrid()
    {
        cout << "Grid layout:\n";
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (grid[i][j] == 1)
                {
                    cout << "X "; // Represents obstacle
                }
                else
                {
                    cout << ". "; // Represents free space
                }
            }
            cout << "\n";
        }
    }

private:
    int rows, cols;
    int grid[MAX_SIZE][MAX_SIZE]; // Grid representation (1 for obstacle, 0 for free space)

    // Heuristic function (Manhattan Distance)
    int heuristic(int x1, int y1, int x2, int y2)
    {
        return abs(x1 - x2) + abs(y1 - y2);
    }

    // Check if a position is within bounds of the grid
    bool isValid(int x, int y)
    {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }
};

int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name: Nguyen Chu Nguyen Chuong\n";
    cout << "Homework-Lap5\n";
    cout << "\n";
    // Grid representing the game environment (0 = free, 1 = obstacle)
    int grid[MAX_SIZE][MAX_SIZE] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 1},
        {0, 0, 0, 0, 0}};

    // Create A* instance with the grid
    AStar astar(5, 5, grid);

    // Print the grid layout before running the algorithm
    astar.printGrid();

    // Define the start and goal positions
    pair<int, int> start = {0, 0};
    pair<int, int> goal = {4, 4};

    // Find the path from start to goal
    Node *goalNode = astar.findPath(start, goal);

    // Output the path
    astar.reconstructPath(goalNode);
    system("pause");
    return 0;
}
