#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <iostream>
#include <initialization.hpp>
#include <vector>
#include <generate_image.hpp>
#include <cassert>
#include <ctime>
#include <tuple>

using namespace std;


// Json from https://riskylab.com/tilemap/ gives a 1D array of the grid
// This function converts the 1D array to a 2D grid
void generate_grid(
    const int width,
    const int height,
    const vector<int> &serialized_grid,
    vector<vector<int>> &grid
    ) 
{
    
    grid.resize(width, vector<int>(height, 0));
    int index = 0;

    for (int i = 0; i<width; i++) 
    {
        for (int j = 0; j<height; j++) 
        {
            grid[i][j] = serialized_grid[index];
            index++;
        }
    }
}



// Obtain the inputs from the user and generate the grid for the path planning problem
// The user can either provide a JSON file or generate a random map
// The JSON file should be in the format provided by https://riskylab.com/tilemap/
// User would need to provide start and goal position if not already present in the JSON file.
void obtain_inputs(
    vector<vector<int>> &grid, 
    vector<vector<int>> &start_positions, 
    vector<vector<int>> &goal_positions)
{
    
    int width = 64;    // Minimum Width of the grid
    int height = 64;   // Minimum Height of the grid
    vector<int> serialized_grid(width*height, 0);   // 1D array of the grid
    
    
    // Obtain Map Source
    cout << "Enter the Local OR Global Path to the JSON file (Press Enter to Generate a Random Map): ";
    string path;
    getline(cin, path);

    if (path == "")
    {
        cout << "Generating Random Map..." << endl;
        // Generate Random Map
        srand(time(0));  // Initialize random seed
        
        //cell shall be an empty space with 70% probability
        vector<int> allowed_values{-1,-1,-1,-1,-1,-1,-1,4,4,4};

        for (int i = 0; i<width*height; i++)
        {
            //Randomly Select value from Index 0 to 9 of allowed values
            serialized_grid[i] = allowed_values[rand() % 10];
        }

        
    }
    else
    {
        cout << "Reading Map from " << path << "..." << endl;
        // Open the JSON file
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Failed to open the JSON file." << std::endl;
            assert(false);
        }

        // Read the JSON file into a string
        std::string jsonString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        // Parse the JSON string
        Json::Value root;
        Json::CharReaderBuilder builder;
        std::string parseErrors;
        std::istringstream jsonStream(jsonString);
        if (!Json::parseFromStream(builder, jsonStream, &root, &parseErrors)) {
            std::cerr << "Failed to parse the JSON file: " << parseErrors << std::endl;
            assert(false);
        }

        // // Access the JSON data
        int width = root["canvas"]["width"].asInt() /root["tilesets"][0]["tilewidth"].asInt();
        int height = root["canvas"]["height"].asInt() /root["tilesets"][0]["tileheight"].asInt();

        serialized_grid.resize(width*height, 0);

        // Read the serialized grid values from the JSON string
        for(int i = 0; i<width*height; i++)
        {
            serialized_grid[i] = root["layers"][1]["data"][i].asInt();

            if (serialized_grid[i] == 0)
            {
                start_positions.push_back({i%width, i/width});
            }
            else if (serialized_grid[i] == 6)
            {
                goal_positions.push_back({i%width, i/width});
            }

            
        }

        
        // Give a warning if multiple start and goal positions are detected as they may not be matched as intended.
        if (goal_positions.size() > 1)
        {
            cout<<"Multiple Start and Goal Positions Detected. If the goal positions are not the same, Unit 1 will move to the first goal position, Unit 2 will move to the second goal position, and so on."<<std::endl;
        }

        // Perform sanity check that the number of start positions is equal to the number of goal positions.
        if (start_positions.size() != goal_positions.size())
        {
            cout<<"Start Position is Missing a Goal Position"<<std::endl;
            assert(false);
        }

        

    }



    // Obtain the Start and Goal Positions of the Battle Units if not already present.
    if (start_positions.size() == 0)
    {
        cout << "Enter the number of Battle Units: ";
        int num_units;
        cin >> num_units;
        
        if(num_units <=0)
        {
            cout<<"Atleast One Unit is required."<<std::endl;
            assert(false);
        }

        for (int i = 0; i<num_units; i++)
        {
            cout << "Enter the starting x-co-ordinate of Battle Unit " << i+1 << ": ";
            int x, y;
            cin >> x;
            cout << "Enter the starting y-co-ordinate of Battle Unit " << i+1 << ": ";
            cin >> y;
            start_positions.push_back({x, y});

            if(x< 0 || x >= width || y < 0 || y >= height)
            {
                cout<<"Invalid Start Position."<<std::endl;
                assert(false);
            }

            // Update value in serialized grid
            serialized_grid[x + y*width] = 0;

            cout<<"Enter the goal x-co-ordinate of Battle Unit " << i+1 << ": ";
            cin >> x;
            cout<<"Enter the goal y-co-ordinate of Battle Unit " << i+1 << ": ";
            cin >> y;
            goal_positions.push_back({x, y});

            if(x< 0 || x >= width || y < 0 || y >= height)
            {
                cout<<"Invalid Goal Position."<<std::endl;
                assert(false);
            }

            // Update value in serialized grid
            serialized_grid[x + y*width] = 6;

            
        }
    }

    // Generate the grid
    generate_grid(width, height, serialized_grid, grid);
    
    
    // Display the grid, with start and goal positions
    generate_image(grid);

}