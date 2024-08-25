#include "matplotlibcpp.h"
#include <vector>
#include <generate_image.hpp>

namespace plt = matplotlibcpp;
using namespace std;


void generate_image(const vector<vector<int>> &grid) 
{
    int width = grid.size();
    int height = grid[0].size();

    // Convert the grid to a 1D vector
    std::vector<float> img(width*height);
    int index = 0;
    for(int i = 0; i<width; i++)
    {
        for(int j = 0; j<height; j++)
        {
            img[index] = abs(grid[i][j]);

            // Assigning color values.
            if(img[index] == 0)
            {
                img[index] = 48;
            }
            else if(img[index] == 6)
            {
                img[index] = 50;
            }
            else if( img[index] == 4)
            {
                img[index] = 0;
            }
            else if (img[index] == 1)
            {
                img[index] = 20;
            }

            index++;
        }
    }

    // Display the image
    plt::imshow(&img[0], width, height, 1);
    plt::show();
}