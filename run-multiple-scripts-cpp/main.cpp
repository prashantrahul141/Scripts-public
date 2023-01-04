#include <thread>
#include <iostream>
#include "include/nlohmann/json.hpp"
#include <fstream>
#include <string>

using json = nlohmann::json;

void each_script(std::string _cmd)
{
    const char *_cmd_as_c = _cmd.c_str();
    system(_cmd_as_c);
}

int main()
{
    // parsing data
    std::ifstream data_file("data.json");
    json data = json::parse(data_file);
    auto scripts = data["SCRIPTS"];

    std::thread thread_objs[scripts.size()];

    // looping through scripts
    for (int i = 0; i < scripts.size(); i++)
    {
        std::string _cmd = "";
        auto _each = scripts[i];

        // adding prefix args
        // for (int j = 0; j < _each["PREFIX_ARGS"].size(); j++)
        // {
        //     _cmd.append(_each["PREFIX_ARGS"][j]);

        //     _cmd.append(" && ");
        // }

        // adding location
        _cmd.append("cd ");
        _cmd.append(_each["LOCATION"]);
        _cmd.append(" && ");

        // adding final command
        _cmd.append(_each["SCRIPT"]);

        // printing some info
        std::cout << "starting " << _each["NAME"] << std::endl;
        std::cout << "with " << _cmd << std::endl;
        std::cout << std::endl;

        // making threads and adding to threads pool
        thread_objs[i] = std::thread(each_script, _cmd);
    }

    // joining threads
    // for (int i = 0; i < scripts.size(); i++)
    // {
    //     thread_objs[i].join();
    // }

    // taking input to avoid closing.
    // std::cin;

    return 0;
}

// compiling
// g++ -O -o binaries/main.exe include/nlohmann/json.hpp main.cpp  -std=c++11 && binaries\main.exe