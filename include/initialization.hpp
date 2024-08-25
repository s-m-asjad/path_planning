#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <generate_image.hpp>
#include <tuple>

void obtain_inputs(
    std::vector<std::vector<int>> &grid, 
    std::vector<std::vector<int>> &start_positions, 
    std::vector<std::vector<int>> &goal_positions); 