/* 
Problem Statement:

You are given a 2D grid of '1's (land) and '0's (water). An island is a group of connected '1's (connected horizontally, vertically, or diagonally). 
Count the number of distinct islands in the grid.

Input: 
  1 1 0 0 0
  1 1 0 0 0
  0 0 1 0 0
  0 0 0 1 1

Output:
  Number of islands: 3
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// BFS to explore the island and mark all connected cells as visited
void bfs(vector<vector<char>>& grid, int x, int y) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Directions for moving in 8 possible ways (N, S, E, W, and diagonals)
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1},
                                         {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    queue<pair<int, int>> q;
    q.push({x, y});
    grid[x][y] = '0'; // Mark the starting cell as visited (convert '1' to '0')

    while (!q.empty()) {
        auto [cx, cy] = q.front();
        q.pop();

        for (auto [dx, dy] : directions) {
            int nx = cx + dx;
            int ny = cy + dy;

            // Check boundaries and ensure the neighbor is land ('1')
            if (nx >= 0 && ny >= 0 && nx < rows && ny < cols && grid[nx][ny] == '1') {
                grid[nx][ny] = '0'; // Mark as visited
                q.push({nx, ny});
            }
        }
    }
}

int numIslands(vector<vector<char>>& grid) {
    if (grid.empty()) return 0;

    int rows = grid.size();
    int cols = grid[0].size();
    int count = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == '1') {
                ++count;        // Found a new island
                bfs(grid, i, j); // Perform BFS to mark the entire island
            }
        }
    }

    return count;
}

int main() {
    vector<vector<char>> grid = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    };

    cout << "Number of islands: " << numIslands(grid) << endl;
    return 0;
}
