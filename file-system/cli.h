#include <string>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <algorithm>

class Cli {
    std::unordered_map<std::string, std::function<void()>> command_map;
    bool is_listening;
    void get_and_execute();
    public:
        Cli();
        bool add_command(std::string command, std::function<void()> method);
        std::string get();
        static void to_lower(std::string& str);
        void listen();
};