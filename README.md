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
    
<br/>

#### b) Random Generation
- Simply press `Enter` when the terminal says


<br/>

    
    Enter the Local OR Global Path to the JSON file (Press Enter to Generate a Random Map):
    
<br/>

- A random map will be generated and stored in memory. The size will be 64x64. Each cell will have a 30% probability of being an elevated terrain. 

### 2. Deciding the Number of Units

### 3. Deciding the Start Position of Units

### 4. Viewing the Map and Units

### 5. Running the Path Finding Algorithm

### 6. Viewing the Final Path