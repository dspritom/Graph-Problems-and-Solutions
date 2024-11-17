/*

  Problem Statement - 
    You are given:

      A startWord.
      An endWord.
      A wordList containing valid intermediate words.
      Transform the startWord into the endWord by changing only one character at a time. Each transformed word must exist in the wordList.

      Your task is to find the minimum number of transformations required to reach the endWord from the startWord. If it is not possible, return 0.

  Input - 
    startWord = "hit"
    endWord = "cog"
    wordList = ["hot", "dot", "dog", "lot", "log", "cog"]

  Output - 
    Minimum transformations: 5
*/

/// Solution using BFS

#include <iostream>
#include <unordered_set>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// Function to find the shortest transformation sequence
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> wordSet(wordList.begin(), wordList.end());

    // If the endWord is not in the wordList, return 0
    if (wordSet.find(endWord) == wordSet.end()) {
        return 0;
    }

    // Initialize BFS
    queue<pair<string, int>> q; // {currentWord, transformations}
    q.push({beginWord, 1});

    while (!q.empty()) {
        auto [currentWord, steps] = q.front();
        q.pop();

        // If the current word is the endWord, return the steps
        if (currentWord == endWord) {
            return steps;
        }

        // Explore all possible transformations
        for (int i = 0; i < currentWord.size(); ++i) {
            string temp = currentWord;
            for (char c = 'a'; c <= 'z'; ++c) {
                temp[i] = c; // Change one character at position i

                // If the transformed word is valid and in the wordSet
                if (wordSet.find(temp) != wordSet.end()) {
                    q.push({temp, steps + 1});
                    wordSet.erase(temp); // Remove to prevent revisiting
                }
            }
        }
    }

    // If no transformation sequence is found, return 0
    return 0;
}

int main() {
    string startWord = "hit";
    string endWord = "cog";
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};

    int result = ladderLength(startWord, endWord, wordList);

    if (result > 0) {
        cout << "Minimum transformations: " << result << endl;
    } else {
        cout << "Transformation is not possible." << endl;
    }

    return 0;
}


/// Optimized Solution with Bidirectional BFS

#include <iostream>
#include <unordered_set>
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// Helper function to generate all possible transformations
vector<string> getNeighbors(const string& word, const unordered_set<string>& wordSet) {
    vector<string> neighbors;
    string temp = word;

    for (int i = 0; i < word.size(); ++i) {
        char originalChar = temp[i];
        for (char c = 'a'; c <= 'z'; ++c) {
            if (c == originalChar) continue;
            temp[i] = c;

            if (wordSet.find(temp) != wordSet.end()) {
                neighbors.push_back(temp);
            }
        }
        temp[i] = originalChar; // Restore original character
    }

    return neighbors;
}

// Bidirectional BFS to find the shortest transformation sequence
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> wordSet(wordList.begin(), wordList.end());

    // If the endWord is not in the wordList, return 0
    if (wordSet.find(endWord) == wordSet.end()) {
        return 0;
    }

    // Initialize the two BFS queues
    unordered_set<string> beginSet = {beginWord};
    unordered_set<string> endSet = {endWord};
    unordered_set<string> visited;

    int steps = 1;

    // Bidirectional BFS
    while (!beginSet.empty() && !endSet.empty()) {
        // Always expand the smaller set for efficiency
        if (beginSet.size() > endSet.size()) {
            swap(beginSet, endSet);
        }

        unordered_set<string> nextSet;

        for (const string& word : beginSet) {
            vector<string> neighbors = getNeighbors(word, wordSet);

            for (const string& neighbor : neighbors) {
                // If we meet the other search, return the steps
                if (endSet.find(neighbor) != endSet.end()) {
                    return steps + 1;
                }

                // If not visited, mark it and add to the next level
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    nextSet.insert(neighbor);
                }
            }
        }

        beginSet = nextSet;
        ++steps;
    }

    return 0; // If no connection is found
}

int main() {
    string startWord = "hit";
    string endWord = "cog";
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};

    int result = ladderLength(startWord, endWord, wordList);

    if (result > 0) {
        cout << "Minimum transformations: " << result << endl;
    } else {
        cout << "Transformation is not possible." << endl;
    }

    return 0;
}


