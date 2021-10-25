#include <iostream>
#include "file-system/fs.h"

int main (int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << '\n';
    }
    std::cout << std::endl;
    std::unique_ptr<FS> fs = std::make_unique<FS>();
    std::string a = "what's up guys it's me jermey.";
    fs->make_dir("jeff");
    fs->make_dir("jermey");
    fs->print_current();
    fs->go_to_local("jermey");
    fs->make_file("jermey_file", a.length() + 1, a.c_str());
    fs->print_current();
    fs->go_back();
    fs->go_to_local("jeff");
    a = "my name's jeff";
    fs->make_file("jeff_file", a.length() + 1, a.c_str());
    fs->make_dir("maya");
    fs->make_dir("alex");
    fs->print_current();
    fs->go_to_local("maya");
    fs->make_dir("oleg");
    fs->print_current();
    fs->make_dir("oleg");
    fs->print_current();
    fs->go_back();
    fs->print_current();
    // const char data[] = "abcde";
    // const int index = BLK_FILE_DEFAULT_SIZE - 1;
    // size_t data_size = sizeof(data);

    // Blkd b;
    // b.open_blk_file();
    // b.write(index, data_size, data);

    // char* data2 = new char[data_size];
    // b.read(index, data_size, data2);
    // std::cout << data2 << std::endl;
    // delete[] data2;
}