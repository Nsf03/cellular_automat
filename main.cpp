#include <iostream>
#include <string>
#include "SFML_export.h"
#include "Grid.h"
#include <unistd.h>



int main() {
    //Grid_1c g("gun.txt");
    Grid_2c g("head.txt");
    //Grid_4c g("4.txt")
    std::cout << "If you want to see life in the console, press Y, else press anything";
    char console_char;
    std::cin >> console_char;
    bool console_flag = false;
    if (console_char == 'Y'){console_flag = true;};



    auto test_rectangles =  new sf::CircleShape[10];
    auto vis_params = make_window(g.x_size, g.y_size, x_max, y_max, cell_size_max);

    unsigned int steps = 100000;
    int step = 0;
    float cell_size=vis_params.size;
    sf::RenderWindow window(sf::VideoMode(vis_params.x, vis_params. y), "SFML Application");
    auto rectangles =  new sf::RectangleShape[g.y_size*g.x_size];
    for (int i = 0; i < g.y_size*g.x_size; ++i) {
        rectangles[i].setSize(sf::Vector2f(cell_size, cell_size));

    };

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //window.clear();
        for (int i = 0; i < g.y_size; i++) {
            for (int j = 0; j < g.x_size; j++) {
                rectangles[i * g.x_size + j].setPosition(float(j) * cell_size, float(i) * cell_size);
                rectangles[i * g.x_size + j].setFillColor(c[g.field[i * g.x_size + j].state]);
                window.draw(rectangles[i * g.x_size + j]);

            };
        };

        window.display();
        if (console_flag){std::cout << g;};
        step++;
        g.step();
        if (steps <= step){window.close();};
        usleep(100000);
    }
    delete[] rectangles;

    return 0;
}