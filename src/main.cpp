#include <vector>
#include <initialization.hpp>
#include <generate_image.hpp>
#include <path_planning.hpp>


using namespace std;

int main(int argc, char** argv) 
{ 
    
    vector<vector<int>> grid;
    vector<vector<int>> start_positions;
    vector<vector<int>> goal_positions;
    vector<vector<vector<int>> > paths;

    // Select what Path planner to use. A* is Default.
    bool BFS_FLAG = false;
    if(argc > 1 && string(argv[1]) == "BFS")
    {
        cout << "Using BFS for Path Planning." << endl;
        BFS_FLAG = true;
    }
    else
    {
        cout << "Using A* for Path Planning." << endl;
    }


    // Obtain the inputs from the user and generate the grid for the path planning problem
    // The text-based UI in the Terminal allows the user to either provide a JSON file or generate a random map
    obtain_inputs(grid, start_positions, goal_positions);

    

    
    // Solve the path planning problem using the A* algorithm
    for (int i=0; i< start_positions.size(); i++)
    {
        vector<vector<int>> path; 
        if(!BFS_FLAG)
        {
            path = a_star(grid, start_positions[i], goal_positions[i], paths);
        }
        else
        {
            path = BFS(grid, start_positions[i], goal_positions[i], paths);
        }

        if (path.size() == 0)
        {
            cout << "No Path Found for Agent " << i+1 << endl;
            continue;
        }

        for(auto p: path)
        {
            
            
            if(grid[p[1]][p[0]] == 0 || grid[p[1]][p[0]] == 6)
            {
                continue;
            }

        

            grid[p[1]][p[0]] = 60+(i*10);
        }

        path.pop_back();        // Remove the goal position from the path since multiple agents can have the same goal.
        paths.push_back(path);
    }
    
    
    // Display the grid, with start, goal positions and the path to be followed.
    generate_image(grid);


    return 0; 
}