#include <iostream>
#include "file-system/cli.h"
#include "file-system/fs.h"

int main (int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << '\n';
    }
    std::cout << std::endl;
    FS fs = FS();
    fs.print_current();
    Cli cli = Cli();
    cli.add_command("mkf", [&]() {
        std::cout << "Print file name: \t";
        std::string name = cli.get();

        std::cout << "Print data: \t";
        std::string data = cli.get();
        fs.make_file(name.c_str(), data.length() + 1, data.c_str());
        std::cout << std::endl;
    });
    cli.add_command("mkdir", [&]() {
        std::cout << "Print dir name: \t";
        std::string name = cli.get();
        fs.make_dir(name.c_str());
        std::cout << std::endl;
    });
    cli.add_command("show", [&]() {
        fs.print_current();
    });
    cli.add_command("print", [&]() {
        std::cout << "Print file name: \t";
        std::string name = cli.get();
        fs.show_content(name.c_str());
        std::cout << std::endl;
    });
    cli.add_command("goto", [&]() {
        std::cout << "Print dir name: \t";
        std::string name = cli.get();
        fs.go_to_local(name);
        std::cout << std::endl;
    });
    cli.add_command("back", [&]() {
        fs.go_back();
    });
    cli.listen();
}