/*

  Problem Statement - 
    You are given a grid where:

    Each cell can have one of three possible values:
      0: Represents an empty cell.
      1: Represents a fresh orange.
      2: Represents a rotten orange.
    Every minute, a rotten orange will rot all adjacent fresh oranges (up, down, left, right). 
    Your task is to determine the minimum time required to rot all the fresh oranges. 
    If it is impossible to rot all oranges, return -1.

  Input - 
    2 1 1
    1 1 0
    0 1 1

  Output - 
    Minimum time to rot all oranges: 4

*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Function to find the minimum time to rot all oranges
int orangesRotting(vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    queue<pair<pair<int, int>, int>> q; // {coordinates, time}
    int freshCount = 0;

    // Directions for moving up, down, left, right
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Initialize the queue with all rotten oranges
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 2) {
                q.push({{i, j}, 0}); // Rotten orange with time 0
            } else if (grid[i][j] == 1) {
                ++freshCount; // Count the fresh oranges
            }
        }
    }

    // If there are no fresh oranges, return 0
    if (freshCount == 0) {
        return 0;
    }

    int time = 0;

    // Perform BFS
    while (!q.empty()) {
        auto [cell, t] = q.front();
        auto [x, y] = cell;
        q.pop();

        // Update the time
        time = t;

        // Explore all 4 directions
        for (auto [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;

            // Check boundaries and whether the neighbor is a fresh orange
            if (nx >= 0 && ny >= 0 && nx < rows && ny < cols && grid[nx][ny] == 1) {
                grid[nx][ny] = 2; // Rot the fresh orange
                q.push({{nx, ny}, t + 1}); // Add to queue with updated time
                --freshCount; // Decrease the fresh orange count
            }
        }
    }

    // If there are still fresh oranges left, return -1
    return (freshCount == 0) ? time : -1;
}

int main() {
    vector<vector<int>> grid = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}
    };

    int result = orangesRotting(grid);
    if (result != -1) {
        cout << "Minimum time to rot all oranges: " << result << endl;
    } else {
        cout << "Not all oranges can be rotted." << endl;
    }

    return 0;
}
