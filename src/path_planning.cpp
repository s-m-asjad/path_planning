#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <map>
#include <functional>
#include <path_planning.hpp>
#include <cassert>

using namespace std;

struct Node
{
    
    public:

    // values initialized with -1 to indicate that they are not yet set
    int x = -1;
    int y = -1;
    int g = -1;      // cost to reach the node
    int h = -1;      // cost to reach the goal from the node
    Node* parent;   // parent node
    bool visited = false;

    // Constructor for A*
    Node(int x, int y, int g, int h, Node* parent) : x(x), y(y), g(g), h(h), parent(parent) {}

    // Constructor for BFS/Djikstra (since cost is same for all nodes)
    Node(int x, int y, int g, Node* parent): x(x), y(y), g(g) ,parent(parent) {}

    // Default Constructor
    Node() {}

    
    int f() const { // f = g + h. Lower f value means higher priority
        return g + h;
    }

    
};

// Manhattan Distance Heuristic
int manhattanDistance(const vector<int> goal, int x, int y)
{
    return abs(goal[0] - x) + abs(goal[1] - y);
}


// A* Algorithm. Returns the optimal path from start to goal but uses a priority queue to explore the nodes.
// Priority Queue is sorted based on the f value of the nodes.
vector<vector<int>> a_star(const vector<vector<int>>& grid, const vector<int>& start, const vector<int>& goal, const vector<vector<vector<int>>>& previous_paths)
{

    map<pair<int, int>, Node> nodes;            // Hash Table to easily access nodes and their properties
    vector<Node*> node_priority_queue;          // Priority Queue to store the nodes to be explored. Sorts on insertion.
    vector<vector<int>> path;                   // Optimal Path to be returned (if present)

    // Create the start node and insert it in the queue
    nodes[{start[0], start[1]}] = Node(start[0], start[1], 0, manhattanDistance(goal, start[0], start[1]), nullptr);
    nodes[{start[0], start[1]}].visited = true;
    node_priority_queue.push_back(&nodes[{start[0], start[1]}]);

    // Loop until the priority queue is not empty or the goal node is reached
    while(!node_priority_queue.empty())
    {
        // Get the node with the lowest f value
        Node* current = node_priority_queue.front();
        node_priority_queue.erase(node_priority_queue.begin());

        // Check if the current node is the goal node
        if(current->x == goal[0] && current->y == goal[1])
        {
            // Reconstruct the path from the goal node to the start node
            Node* node = current;
            while(node != nullptr)
            {
                path.push_back({node->x, node->y});
                node = node->parent;
            }
            return path;
        }

        // Generate the neighboring nodes
        for(int dx = -1; dx <= 1; dx++)
        {
            
            for(int dy = -1; dy <= 1; dy++)
            {
                
                if((dx == 0 && dy == 0) || (abs(dx)  ==  abs(dy))) // Skip the current node and the diagonals
                {
                    continue;
                }
                int nx = current->x + dx;
                int ny = current->y + dy;

                // Check if the neighboring node is within the grid and is not an obstacle
                // Also check if the node is not already visited
                if(nx >= 0 && ny < grid.size() && ny >= 0 && nx < grid[0].size() && 
                grid[ny][nx] != 4 && 
                (!nodes[{nx, ny}].visited || nodes[{nx, ny}].g > current->g + 1))
                {
                    
                    bool collision = 0;

                    // Loop previous paths to check if the neighboring node is already being used by another agent for the current step
                    for(int p = 0; p < previous_paths.size(); p++)
                    {
                        // Check if previous path is smaller than the current path. If yes, then collision is not possible.
                        if(previous_paths[p].size()<current->g + 1)
                        {
                            continue;
                        }

                        // Check if the neighboring node is already being used.
                        vector<int> previous_path_cell = previous_paths[p][current->g];
                        if(previous_path_cell[0] == nx && previous_path_cell[1] == ny )
                        {
                            collision = 1;
                        }

                    }

                    if(collision == 0)
                    {
                        // Create the node and insert it in the queue
                        nodes[{nx, ny}] = Node(nx, ny, current->g + 1, manhattanDistance(goal, nx, ny), current);
                        node_priority_queue.push_back(&nodes[{nx, ny}]);
                        
                        // Update the priority queue based on the f value of the nodes.
                        // This allows the node with the lowest f value to be explored first.
                        sort(node_priority_queue.begin(), node_priority_queue.end(), [](const Node* a, const Node* b) {
                            return a->f() < b->f();
                        });

                        // Mark the node as visited
                        nodes[{nx, ny}].visited = true;
                    }

                    
                }
            }
        }
    }

    return path;


}


// Breadth First Search Algorithm (Equivalent to Djikstra's Algorithm since cost is same for all nodes)
vector<vector<int>> BFS(const vector<vector<int>>& grid, const vector<int>& start, const vector<int>& goal, const vector<vector<vector<int>>>& previous_paths)
{

    map<pair<int, int>, Node> nodes;            // Hash Table to easily access nodes and their properties
    queue<Node*> node_queue;                    // Simple Queue to store the nodes to be explored
    vector<vector<int>> path;                   // Optimal Path to be returned (if present)

    // Create the start node and insert it in the queue
    nodes[{start[0], start[1]}] = Node(start[0], start[1], 0, nullptr);
    nodes[{start[0], start[1]}].visited = true;
    node_queue.push(&nodes[{start[0], start[1]}]);

    
    while(!node_queue.empty())
    {
        // Get the node in the front of the queue
        Node* current = node_queue.front();
        node_queue.pop();

        // Check if the current node is the goal node
        if(current->x == goal[0] && current->y == goal[1])
        {
            // Reconstruct the path from the goal node to the start node
            Node* node = current;
            while(node != nullptr)
            {
                path.push_back({node->x, node->y});
                node = node->parent;
            }
            return path;
        }

    
        // Generate the neighboring nodes
        for(int dx = -1; dx <= 1; dx++)
        {
            
            for(int dy = -1; dy <= 1; dy++)
            {
                
                if((dx == 0 && dy == 0) || (abs(dx)  ==  abs(dy))) // Skip the current node and the diagonals
                {
                    continue;
                }
                int nx = current->x + dx;
                int ny = current->y + dy;

                // Check if the neighboring node is within the grid and is not an obstacle
                // Also check if the node is not already visited
                if(nx >= 0 && ny < grid.size() && ny >= 0 && nx < grid[0].size() && grid[ny][nx] != 4 && !nodes[{nx, ny}].visited )
                {
                    
                    bool collision = 0;

                    // Check if the neighboring node is already being used by another agent for the current step
                    for(int p = 0; p < previous_paths.size(); p++)
                    {
                        if(previous_paths[p].size()<current->g + 1)
                        {
                            continue;
                        }

                        vector<int> previous_path_cell = previous_paths[p][current->g];
                        if(previous_path_cell[0] == nx && previous_path_cell[1] == ny )
                        {
                            collision = 1;
                        }

                    }

                    if(collision == 0)
                    {
                        // Create the node and insert it in the queue
                        nodes[{nx, ny}] = Node(nx, ny, current->g+1 ,current);
                        node_queue.push(&nodes[{nx, ny}]);
                        nodes[{nx, ny}].visited = true;
                    }
                    
                    
                }
            }
        }



    }

    return path;


}


