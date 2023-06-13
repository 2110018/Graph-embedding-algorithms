#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>

using namespace std;

// Function to perform a random walk on the graph
vector<int> randomWalk(const unordered_map<int, vector<int>>& graph, int startNode, int numSteps) {
    vector<int> walk;
    int currentNode = startNode;

    for (int step = 0; step < numSteps; ++step) {
        walk.push_back(currentNode);

        // Check if the current node has any neighbors
        if (graph.find(currentNode) != graph.end() && !graph.at(currentNode).empty()) {
            // Choose a random neighbor
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, graph.at(currentNode).size() - 1);
            int randomIndex = dis(gen);
            currentNode = graph.at(currentNode)[randomIndex];
        }
        else {
            // No neighbors, terminate the walk
            break;
        }
    }

    return walk;
}

// Function to generate random walk sequences on the graph
vector<vector<int>> generateRandomWalks(const unordered_map<int, vector<int>>& graph, int numWalks, int numSteps) {
    vector<vector<int>> allWalks;

    // Perform random walks starting from each node
    for (const auto& node : graph) {
        int startNode = node.first;

        for (int walk = 0; walk < numWalks; ++walk) {
            vector<int> walkSequence = randomWalk(graph, startNode, numSteps);
            allWalks.push_back(walkSequence);
        }
    }

    return allWalks;
}

int main() {
    // Example graph represented as an adjacency list
    unordered_map<int, vector<int>> graph;
    graph[0] = { 1, 2 };
    graph[1] = { 0, 2 };
    graph[2] = { 0, 1, 3 };
    graph[3] = { 2 };

    int numWalks = 5;   // Number of random walks to perform from each node
    int numSteps = 10;  // Number of steps for each random walk

    // Generate random walks
    vector<vector<int>> randomWalks = generateRandomWalks(graph, numWalks, numSteps);

    // Print the random walks
    for (const auto& walk : randomWalks) {
        for (const auto& node : walk) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
