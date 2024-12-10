#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Class to represent the recommendation system
class RecommendationSystem
{
public:
    // User-Item Interaction Matrix (User-Item matrix, where rows represent users and columns represent items)
    vector<vector<int>> interactionMatrix;
    int numUsers;
    int numItems;

    RecommendationSystem(int users, int items) : numUsers(users), numItems(items)
    {
        interactionMatrix.resize(users, vector<int>(items, 0));
    }

    // Add user-item interaction (e.g., purchase or rating)
    void addInteraction(int user, int item, int interaction)
    {
        interactionMatrix[user][item] = interaction;
    }

    // Calculate the cosine similarity between two items
    double cosineSimilarity(int item1, int item2)
    {
        double dotProduct = 0;
        double normItem1 = 0;
        double normItem2 = 0;

        // Compute cosine similarity
        for (int user = 0; user < numUsers; ++user)
        {
            dotProduct += interactionMatrix[user][item1] * interactionMatrix[user][item2];
            normItem1 += interactionMatrix[user][item1] * interactionMatrix[user][item1];
            normItem2 += interactionMatrix[user][item2] * interactionMatrix[user][item2];
        }

        // Avoid division by zero
        if (normItem1 == 0 || normItem2 == 0)
            return 0;

        return dotProduct / (sqrt(normItem1) * sqrt(normItem2));
    }

    // Build the item-item similarity matrix
    vector<vector<double>> buildItemSimilarityMatrix()
    {
        vector<vector<double>> similarityMatrix(numItems, vector<double>(numItems, 0));

        // Calculate pairwise item-item cosine similarity
        for (int i = 0; i < numItems; ++i)
        {
            for (int j = i + 1; j < numItems; ++j)
            {
                similarityMatrix[i][j] = cosineSimilarity(i, j);
                similarityMatrix[j][i] = similarityMatrix[i][j]; // Similarity is symmetric
            }
        }

        return similarityMatrix;
    }

    // Recommend items for a given user based on item-item similarity
    vector<int> recommendItems(int userId, int numRecommendations = 5)
    {
        vector<vector<double>> similarityMatrix = buildItemSimilarityMatrix();
        vector<pair<int, double>> itemScores(numItems, {0, 0}); // {item, score}

        // For each item the user has interacted with, calculate the weighted score for other items
        for (int item = 0; item < numItems; ++item)
        {
            if (interactionMatrix[userId][item] > 0)
            { // User has interacted with this item
                // Now recommend similar items
                for (int otherItem = 0; otherItem < numItems; ++otherItem)
                {
                    if (item != otherItem && interactionMatrix[userId][otherItem] == 0)
                    {
                        // Update score only if the user hasn't already interacted with this item
                        itemScores[otherItem].first = otherItem;
                        itemScores[otherItem].second += similarityMatrix[item][otherItem];
                    }
                }
            }
        }

        // Sort the items based on the calculated scores in descending order
        sort(itemScores.begin(), itemScores.end(), [](const pair<int, double> &a, const pair<int, double> &b)
             { return a.second > b.second; });

        // Return the top N recommended items (excluding items already interacted with)
        vector<int> recommendedItems;
        int recommendationsCount = 0;
        for (int i = 0; i < itemScores.size() && recommendationsCount < numRecommendations; ++i)
        {
            if (interactionMatrix[userId][itemScores[i].first] == 0)
            {
                recommendedItems.push_back(itemScores[i].first);
                recommendationsCount++;
            }
        }

        // In case there are not enough items to recommend, return as many as we can
        return recommendedItems;
    }

    // Display the user-item interaction matrix
    void displayInteractionMatrix()
    {
        cout << "User-Item Interaction Matrix:\n";
        for (int user = 0; user < numUsers; ++user)
        {
            for (int item = 0; item < numItems; ++item)
            {
                cout << interactionMatrix[user][item] << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    cout << "STT: 22520165\n";
    cout << "Full Name: Nguyen Chu Nguyen Chuong\n";
    cout << "Homework-Lap5\n";
    cout << "\n";
    // Create a recommendation system with 5 users and 6 items
    int numUsers = 5;
    int numItems = 6;
    RecommendationSystem recSystem(numUsers, numItems);

    // User input for interactions
    cout << "Enter interaction data for " << numUsers << " users and " << numItems << " items:\n";
    for (int user = 0; user < numUsers; ++user)
    {
        for (int item = 0; item < numItems; ++item)
        {
            int interaction;
            cout << "User " << user << " interaction with Item " << item << " (0 for no, 1 for yes): ";
            cin >> interaction;
            recSystem.addInteraction(user, item, interaction);
        }
    }

    // Display the interaction matrix
    recSystem.displayInteractionMatrix();

    // Ask which user to generate recommendations for
    int userId;
    cout << "Enter the user ID (0 to " << numUsers - 1 << ") for recommendations: ";
    cin >> userId;

    // Generate recommendations for the selected user
    vector<int> recommendedItems = recSystem.recommendItems(userId, 3);

    // Display recommended items
    cout << "Recommended items for User " << userId << ": ";
    for (int item : recommendedItems)
    {
        cout << item << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}
