// Description: Handle input data from file.
#pragma once

#include <sstream>
#include <vector>
#include "file_handler.hpp"
#include <string>
#include <iostream>


void handle_input(const std::string file, std::vector<float>& input) {
    FileHandler fh;
    fh.open(file);
    auto res = fh.read();
    std::stringstream ss(res);
    float value;
    while (ss >> value) input.push_back(value);
    fh.close();
}