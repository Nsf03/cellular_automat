//
// Created by nsf30 on 04.12.2022.
//

#ifndef CELLULAR_AUTOMATA_CONFIG_IMPORT_H
#define CELLULAR_AUTOMATA_CONFIG_IMPORT_H

#include <iostream>
#include <fstream>


void Error(){
    std::cout << "ERROR, WRONG FORMAT OF TXT FILE " << std::endl;
    std::exit(0);
}

class Config_Import {
private:
public:
    static int* file(std::string& path) {
        std::ifstream config(path);

        if (!config) {
            std::cout << "ERROR, NO FILE " << path << std::endl;
            std::exit(0);
            return nullptr;
        } else {
            int x;
            int y;
            if(!(config >> x)){Error();};
            if(!(config >> y)){Error();};
            int* file = new int[x*y + 2];
            file[0] = x;
            file[1] = y;
            for (int i = 0; i < x*y; i++) {
                int tmp;
                if(!(config >> tmp)){Error();};
                file[i + 2] = tmp;
            }
            return file;
        }
    }

    static int x_size(int* file) {
        return file[0];
    }

    static int y_size(int* file) {
        return file[1];
    }

    static void valid(std::string& path){
        std::ifstream config(path);
        bool file_is_ok = true;
        char32_t check;


}

    static int* data(int* file) {
        int size = x_size(file)* y_size(file);
        int* data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = file[i + 2];
        }
        return data;
    }
};


#endif //CELLULAR_AUTOMATA_CONFIG_IMPORT_H

//ЕСЛИ ВДРУГ МУСОР