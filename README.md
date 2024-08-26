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
