#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <map>
#include <functional>

using namespace std;

vector<vector<int>> BFS(const vector<vector<int>>& grid, const vector<int>& start, const vector<int>& goal, const vector<vector<vector<int>>>& previous_paths);

vector<vector<int>> a_star(const vector<vector<int>>& grid, const vector<int>& start, const vector<int>& goal, const vector<vector<vector<int>>>& previous_paths);