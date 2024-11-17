


/*
  Problem Statement -
    Given an N x M grid, where:

    0 represents an empty cell you can move through.
    1 represents an obstacle you cannot pass through.
    You are tasked to find the shortest path from the top-left corner (0, 0) to the bottom-right corner (N-1, M-1). 
    You can move in 4 directions (up, down, left, right). If there is no valid path, return -1.

  Input - 
    0 0 1 0
    1 0 1 0
    0 0 0 0
    1 1 1 0

  Output - 
    (0, 0) → (0, 1) → (1, 1) → (2, 1) → (2, 2) → (2, 3) → (3, 3)

*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

// Function to find the shortest path
int shortestPath(vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    // If the starting or ending cell is blocked, return -1
    if (grid[0][0] == 1 || grid[rows - 1][cols - 1] == 1) {
        return -1;
    }

    // Directions for moving in 4 directions (up, down, left, right)
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    queue<pair<int, int>> q;

    // Start BFS from the top-left corner
    q.push({0, 0});
    grid[0][0] = 1; // Mark as visited by using the distance directly

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        // If we reach the bottom-right corner, return the distance
        if (x == rows - 1 && y == cols - 1) {
            return grid[x][y];
        }

        // Explore all 4 directions
        for (auto [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;

            // Check boundaries and obstacles
            if (nx >= 0 && ny >= 0 && nx < rows && ny < cols && grid[nx][ny] == 0) {
                grid[nx][ny] = grid[x][y] + 1; // Update distance
                q.push({nx, ny});
            }
        }
    }

    // If no path is found, return -1
    return -1;
}

int main() {
    vector<vector<int>> grid = {
        {0, 0, 1, 0},
        {1, 0, 1, 0},
        {0, 0, 0, 0},
        {1, 1, 1, 0}
    };

    int result = shortestPath(grid);
    if (result != -1) {
        cout << "Shortest Path Length: " << result << endl;
    } else {
        cout << "No valid path exists." << endl;
    }

    return 0;
}
