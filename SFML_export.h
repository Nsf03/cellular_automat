
#ifndef CELLULAR_AUTOMATA_SFML_EXPORT_H
#define CELLULAR_AUTOMATA_SFML_EXPORT_H

#include <SFML/Graphics.hpp>
//#include <include/SFML/Graphics.hpp>
//#include "Grid.h"


auto c0 = sf::Color(0, 0, 0);
auto c1 = sf::Color(255, 255, 255);
auto c2 = sf::Color(255, 30, 30);
auto c3 = sf::Color(49, 198, 212);
auto c4 = sf::Color(255, 255, 0);
sf::Color c[5] = {c0, c1, c2, c3, c4};



unsigned int x_max = 1800;
unsigned int y_max = 850;
float cell_size_max = 20;

struct Vis_params{
    unsigned int x;
    unsigned int y;
    float size;

    Vis_params(unsigned int x, unsigned int y, float size): x(x), y(y), size(size){}
};

Vis_params make_window(unsigned int x_size, unsigned int y_size, unsigned int x_max, unsigned int y_max, float cell_max_size){
    unsigned int x = x_size;
    unsigned int y = y_size;
    float cell_size = 1;

    while (( x+x_size <= x_max) && (y+y_size<=y_max) && ((cell_size+1) <= cell_size_max))  {
        x += x_size;
        y += y_size;
        cell_size ++;

    };

    if (x > x_max || y > y_max){
        if (float(x_max)/float(x_size) > float(y_max)/float(y_size)){
            cell_size = float(y_max)/float(y_size);
            x = int(cell_size*x_size)+1;
            y = y_max;
        }
        else{
            cell_size = float(x_max)/float(x_size);
            x = int(cell_size*y_size)+1;
            x = x_max;
        };
    };
    Vis_params vis_params(x, y, cell_size);

    return vis_params;
}




#endif //CELLULAR_AUTOMATA_SFML_EXPORT_H
