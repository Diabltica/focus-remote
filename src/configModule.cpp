//
// Created by Diabltica on 02/09/2022.
//

#include "Headers/configModule.hpp"
#include <fstream>
#include <iostream>

void
config::loadConfig()
{
    std::ifstream f(PATH);
    json data = json::parse(f);
    std::cout << std::setw(4) << data << std::endl ;
}
