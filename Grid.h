//
// Created by nsf30 on 04.12.2022.
//

#ifndef CELLULAR_AUTOMATA_GRID_H
#define CELLULAR_AUTOMATA_GRID_H

#include <utility>
#include "Config_Import.h"
#include "Cell.h"

struct Grid {

    unsigned int x_size;
    unsigned int y_size;
    Cell* field;
    explicit
    Grid(int x_size, int y_size, int state = 0) : x_size(x_size), y_size(y_size) {
        field = new Cell[x_size*y_size];
        for (int i = 0; i < x_size*y_size; i++) {field[i] = Cell(state);}
    };

    Grid() {};

    Grid(std::string path) {
        int* file = Config_Import::file(path);
        x_size = Config_Import::x_size(file);
        y_size = Config_Import::y_size(file);
        int* data =  Config_Import::data(file);
        field = new Cell[x_size*y_size];
        for (int i = 0; i < x_size*y_size; i++) {
            field[i] = Cell(data[i]);
        }
    }

    Grid(const Grid &g) {
        for (int i = 0; i < x_size*y_size; i++) {
            field[i] = g.field[i];
        }
    }
    Grid& operator=(const Grid &g) {
        if (this != &g) {
            for (int i = 0; i < x_size*y_size; i++) {
                field[i] = g.field[i];
            }
        }
        return *this;
    }

    Grid(Grid &&g) {
        if (this != &g) {
            Cell* tmp = g.field;
            g.field = nullptr;
            field = tmp;
        }
    }


    Grid& operator=(Grid &&g) {
        if (this == &g) {
            return *this;
        } else {
            Cell* tmp = g.field;
            g.field = nullptr;
            field = tmp;
            return *this;
        }
    };

    ~Grid() {
        delete [] field;
    };

    int x() {
        return x_size;
    };

    int y() {
        return y_size;
    }

    friend std::ostream& operator<<(std::ostream& out, const Grid& g) {


        for (int i = 0; i < g.y_size; i++) {
            for (int j = 0; j < g.x_size; j++) {
                if (g.field[i*g.x_size + j].state == 1) {out << "@" << " ";}
                if (g.field[i*g.x_size + j].state == 2) {out << "W" << " ";}
                if (g.field[i*g.x_size + j].state == 3) {out << "M" << " ";}
                if (g.field[i*g.x_size + j].state == 4) {out << "O" << " ";}
                else {out << "." << " ";}
                //out << g.field[i*g.x_size + j].state << " ";
            }
            out << std::endl;
        }
        out << std::endl;

        return out;
    };

    int* Grid_Import() {
        int* tmp = new int[x_size*y_size];
        for (int i = 0; i < x_size*y_size; i++) {
            tmp[i] = field[i].state;
        }
        return tmp;
    }

    void insert(int i, int j, int state) {
        field[i*x_size + j] = Cell(state);
    };

    Cell* operator[](int i) const {
        auto a = &this->field[i];
        return &this->field[i];
    };

    virtual int recalculate_cell_count(int i, int j, int state)  {return 0;};

    virtual void recalculate_field_count() {};

    virtual void recalculate_field_state() {};

    void step() {
        this->recalculate_field_count();
        this->recalculate_field_state();
    }
};

struct Grid_1c final: Grid{

    Grid_1c(int x_size, int y_size, int state = 0): Grid(x_size, y_size, 0){}

    Grid_1c(std::string path): Grid(std::move(path)){} //+

    ~Grid_1c() {
        delete [] field;
    };

    int recalculate_cell_count(int i, int j, int state) override {
        int count = 0;
        for (int p = -1; p < 2; p++) {
            for (int q = -1; q < 2; q++) {
                if ((0 <= (i + p) && (i + p) < y_size && 0 <= (j + q) && (j + q) < x_size && p+p + q*q != 0) &&
                    (field[(i + p)*x_size + (j + q)]).state == state) {
                    count++;
                }
            }
        }
        return count;
    };

    void recalculate_field_count() override{
        for (int i = 0; i < y_size; i++) {
            for (int j = 0; j < x_size; j++) {
                field[i*x_size + j].count_1 = recalculate_cell_count(i, j, 1);
            }
        }
    }

    void recalculate_field_state() override{
        for (int i = 0; i < y_size; i++) {
            for (int j = 0; j < x_size; j++) {
                int tmp_state = field[i*x_size + j].state;
                int tmp_count = field[i*x_size + j].count_1;
                if (tmp_state) {
                    if (tmp_count != 2 && tmp_count != 3) {field[i*x_size + j].state = 0;}
                } else {
                    if (tmp_count == 3) {field[i*x_size + j].state = 1;}
                }
            }
        }
    }
};

struct Grid_2c final: Grid{
    Grid_2c(int x_size, int y_size, int state = 0): Grid(x_size, y_size, 0){}

    Grid_2c(std::string path): Grid(std::move(path)){} //+

    ~Grid_2c() {
        delete [] field;
    };

    int recalculate_cell_count(int i, int j, int state) override {
        int count = 0;
        for (int p = -1; p < 2; p++) {
            for (int q = -1; q < 2; q++) {
                if ((0 <= (i + p) && (i + p) < y_size && 0 <= (j + q) && (j + q) < x_size && p+p + q*q != 0) &&
                    (field[(i + p)*x_size + (j + q)]).state == state) {
                    count++;
                }
            }
        }
        return count;
    };

    void recalculate_field_count() override{
        for (int i = 0; i < y_size; i++) {
            for (int j = 0; j < x_size; j++) {
                field[i*x_size + j].count_1 = recalculate_cell_count(i, j, 1);
                field[i*x_size + j].count_2 = recalculate_cell_count(i, j, 2);
            }
        }
    }

    void recalculate_field_state() override{
        for (int i = 0; i < y_size; i++) {
            for (int j = 0; j < x_size; j++) {
                int tmp_state = field[i*x_size + j].state;
                int tmp_count_1 = field[i*x_size + j].count_1;
                int tmp_count_2 = field[i*x_size + j].count_2;
                int tmp_count = tmp_count_1 + tmp_count_2;
                if (tmp_state) {
                    if (tmp_count != 2 && tmp_count != 3) {field[i*x_size + j].state = 0;}
                } else {
                    if (tmp_count == 3) {
                        if (tmp_count_1 > tmp_count_2){field[i*x_size + j].state = 1;}
                        else {field[i*x_size + j].state = 2;}


                    }
                }
            }
        }
    }


};

struct Grid_4c final: Grid{
    Grid_4c(int x_size, int y_size, int state = 0): Grid(x_size, y_size, 0){}

    Grid_4c(std::string path): Grid(std::move(path)){} //+

    ~Grid_4c() {
        delete [] field;
    };

    int recalculate_cell_count(int i, int j, int state) override {
        int count = 0;
        for (int p = -1; p < 2; p++) {
            for (int q = -1; q < 2; q++) {
                if ((0 <= (i + p) && (i + p) < y_size && 0 <= (j + q) && (j + q) < x_size && p+p + q*q != 0) &&
                    (field[(i + p)*x_size + (j + q)]).state == state) {
                    count++;
                }
            }
        }
        return count;
    };

    void recalculate_field_count() override{
        for (int i = 0; i < y_size; i++) {
            for (int j = 0; j < x_size; j++) {
                field[i*x_size + j].count_1 = recalculate_cell_count(i, j, 1);
                field[i*x_size + j].count_2 = recalculate_cell_count(i, j, 2);
                field[i*x_size + j].count_3 = recalculate_cell_count(i, j, 3);
                field[i*x_size + j].count_4 = recalculate_cell_count(i, j, 4);
            }
        }
    }

    void recalculate_field_state() override{
        for (int i = 0; i < y_size; i++) {
            for (int j = 0; j < x_size; j++) {
                int tmp_state = field[i*x_size + j].state;
                int tmp_count_1 = field[i*x_size + j].count_1;
                int tmp_count_2 = field[i*x_size + j].count_2;
                int tmp_count_3 = field[i*x_size + j].count_3;
                int tmp_count_4 = field[i*x_size + j].count_4;
                int tmp_count = tmp_count_1 + tmp_count_2 + tmp_count_3 + tmp_count_4;
                if (tmp_state) {
                    if (tmp_count != 2 && tmp_count != 3) {field[i*x_size + j].state = 0;}
                } else {
                    if (tmp_count == 3) {
                        if (tmp_count_1 ==2 || tmp_count_1 ==3 ){field[i*x_size + j].state = 1;}
                        else if  (tmp_count_2 ==2 || tmp_count_2 ==3 ){field[i*x_size + j].state = 2;}
                        else if  (tmp_count_3 ==2 || tmp_count_3 ==3 ){field[i*x_size + j].state = 3;}
                        else if  (tmp_count_4 ==2 || tmp_count_4 ==3 ){field[i*x_size + j].state = 4;}
                        else if (tmp_count_1 == 0){field[i*x_size + j].state = 1;}
                        else if (tmp_count_2 == 0){field[i*x_size + j].state = 2;}
                        else if (tmp_count_3 == 0){field[i*x_size + j].state = 3;}
                        else if (tmp_count_4 == 0){field[i*x_size + j].state = 4;}

                    }
                }
            }
        }
    }


};



#endif //CELLULAR_AUTOMATA_GRID_H
