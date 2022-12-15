#include <iostream>
#include <string>
#include "SFML_export.h"
#include "Grid.h"
#include <unistd.h>

int main(){
    Grid_1c g0("test0.txt");
    Grid_1c g1("test1.txt");
    Grid_1c g2("test2.txt");
    g0.step();

    for (int i = 0; i < g0.y_size*g0.y_size; ++i) {
        if (g0.field[i].state != g1.field[i].state){
            return -1;
        };
    };

    g0.step();
    for (int i = 0; i < g0.y_size*g0.y_size; ++i) {
        if (g0.field[i].state != g2.field[i].state){
            return -1;
        };
    };

    return 0;
}