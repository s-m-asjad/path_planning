# Path Planning for Battle Strategy Game

## Setting Up

### Clone the Repository
```bash
git clone https://github.com/s-m-asjad/path_planning.git
```

### Clone the open-source libraries
```bash

git clone https://github.com/open-source-parsers/jsoncpp.git
git clone https://github.com/lava/matplotlib-cpp.git matplotlib_cpp
```

### Build the Project (Tested on Linux/Ubuntu and with WSL)
If your system is Windows/MacOS, please build with your prefferred tools. 
```bash
mkdir build
cd build
cmake ..
make
```

### Run the Build (Tested on Linux/Ubuntu and with WSL)
```bash
./PathPlanning
```
*The above method will use the A\* algorithm by default. If you wish to use Breadth First Search (BFS), please pass that as an argument.*
```bash
./PathPlanning BFS
```

<br/>
<br/>

## Using the User-Interface (UI)
### 1. Generating the Map
There are two ways to generate the map.
#### a) Through a JSON
- You will need a json file in the format given by `https://riskylab.com/tilemap`
- Elevated Terrain/Obstacles (valued 4) must be present in the *world* layer
- You may choose to give a global path or a local path from the `PathPlanning` file. In the latter case, if you have the json file called `map.json` in the same folder, your terminal should look like 

<br/>

    
    Enter the Local OR Global Path to the JSON file (Press Enter to Generate a Random Map): map.json


#### b) Random Generation
- Simply press `Enter` when the terminal says

<br/>

    Enter the Local OR Global Path to the JSON file (Press Enter to Generate a Random Map):

- A random map will be generated and stored in memory. The size will be 64x64. Each cell will have a 30% probability of being an elevated terrain. 

### 2. Deciding the Number of Units
There are again two cases for this
#### a) Through a JSON
-   If you have a start and goal position specified in your JSON, the interface will automatically use those and you will not have to enter the number of units manually. 
    
    *(Please note that if multiple units are specified, each unit shall be assigned a goal in sequence. For example, if there are two units, then the first goal position will be assigned to Unit 1 and the second goal to Unit 2.)*

#### a) Via the Terminal
-   If you do not have a start or goal position specified via the JSON or you chose to create a random map, you would be able to enter the number the number of units through the terminal.

### 3. Deciding the Start and Goal Position of Units
- For each unit that does not have a start and goal position, the UI will ask the desired x-position and y-position of the start and goal. A sample input case is shown below

    ```
    Using A* for Path Planning.
    Enter the Local OR Global Path to the JSON file (Press Enter to Generate a Random Map):
    Generating Random Map...
    Enter the number of Battle Units: 1
    Enter the starting x-co-ordinate of Battle Unit 1: 23
    Enter the starting y-co-ordinate of Battle Unit 1: 45
    Enter the goal x-co-ordinate of Battle Unit 1: 12
    Enter the goal y-co-ordinate of Battle Unit 1: 34
    ```

### 4. Viewing the Map and Units
- After the start and goal positions of the final unit are provided, the UI will create a visualization of the grid map. The darker areas are elevations in the map.

### 5. Running the Path Finding Algorithm
- The path finding algorithm runs automatically when the figure is closed.
### 6. Viewing the Final Path
- The final path of each unit is displayed automatically when the algorithm finishes its execution. If a path is not found, the terminal displays the agent's ID and mentions that a path was not found for the respective agent. 