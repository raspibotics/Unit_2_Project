#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> read_file_into_vector(std::string filename) {
    std::vector<std::string> lines; 
    std::ifstream file(filename);
    std::string line;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    }
    return lines;
}
