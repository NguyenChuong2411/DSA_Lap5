#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

using namespace std;

// Function to calculate the PageRank values
vector<double> pagerank(const vector<vector<int>> &graph, double damping_factor = 0.85, int max_iterations = 100, double tol = 1.0e-6)
{
    int N = graph.size(); // Number of pages (nodes)

    // Initialize the PageRank vector (uniform distribution)
    vector<double> PR(N, 1.0 / N);

    // Create the transition matrix P
    vector<vector<double>> P(N, vector<double>(N, 0.0));

    for (int i = 0; i < N; ++i)
    {
        int outlinks = graph[i].size();
        if (outlinks > 0)
        {
            for (int j : graph[i])
            {
                P[j][i] = 1.0 / outlinks;
            }
        }
    }

    // PageRank computation (iterative method)
    for (int iteration = 0; iteration < max_iterations; ++iteration)
    {
        vector<double> new_PR(N, (1 - damping_factor) / N);

        // Compute the new PageRank values
        for (int i = 0; i < N; ++i)
        {
            for (int j : graph[i])
            {
                new_PR[i] += damping_factor * PR[j] * P[i][j];
            }
        }

        // Check for convergence
        double norm = 0.0;
        for (int i = 0; i < N; ++i)
        {
            norm += std::fabs(new_PR[i] - PR[i]);
        }

        if (norm < tol)
        {
            break;
        }

        PR = new_PR; // Update the PageRank vector
    }

    return PR;
}

int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name : Nguyen Chu Nguyen Chuong\n";
    cout << "Homework-Lap5\n";
    cout << "\n";
    cout << "Assuming that the directed graph has 4 pages\n";
    cout << "Page 0 links to pages 1 and 2\n";
    cout << "Page 1 links to page 2\n";
    cout << "Page 2 links to page 3\n";
    cout << "Page 3 links to pages 0 and 1\n";
    vector<vector<int>> graph = {
        {1, 2}, // Page 0 links to Page 1 and 2
        {2},    // Page 1 links to Page 2
        {3},    // Page 2 links to Page 3
        {0, 1}  // Page 3 links to Page 0 and 1
    };

    // Call pagerank function
    vector<double> page_ranks = pagerank(graph);

    // Output the PageRank values
    cout << "PageRank values:" << endl;
    for (int i = 0; i < page_ranks.size(); ++i)
    {
        cout << "Page " << i << ": " << page_ranks[i] << endl;
    }
    system("pause");
    return 0;
}
