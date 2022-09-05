//
// Created by Diabltica on 02/09/2022.
//

#ifndef FOCUS_REMOTE_CONFIGMODULE_HPP
#define FOCUS_REMOTE_CONFIGMODULE_HPP
#include "Headers/nlohmann/json.hpp"

using json = nlohmann::json;

#define PATH "../example.json"

class config
{
  public:
    char* findConfigFile();
//    void loadConfig(char* path);

    void loadConfig();
};

#endif // FOCUS_REMOTE_CONFIGMODULE_HPP
