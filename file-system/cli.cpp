#include "cli.h"

Cli::Cli() {
    command_map.insert({"exit", [this]() mutable {
        this->is_listening = false;
    }});
}

void Cli::to_lower(std::string& str) {
    std::for_each(str.begin(), str.end(), [](char& c) {
        c = std::tolower(c);
    });
}

bool Cli::add_command(std::string command, std::function<void()> method) {
    Cli::to_lower(command);
    auto result = command_map.find(command);
    if (result == command_map.end()) {
        command_map.insert({command, method});
        return true;
    }
    std::cout << "Command already exists." << std::endl;
    return false;
}

void Cli::get_and_execute() {
    std::string command = this->get();
    auto result = command_map.find(command);
    if (result != command_map.end()) {
        result->second();
        return;
    }
    std::cout << "Command doesn't exists." << std::endl;
}

std::string Cli::get() {
    std::string command;
    std::getline(std::cin, command);
    Cli::to_lower(command);
    return command;
}
void Cli::listen() {
    is_listening = true;
    while(is_listening) {
        get_and_execute();
    }
}