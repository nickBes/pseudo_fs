#include <iostream>
#include "file-system/fs.h"

int main (int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << '\n';
    }
    std::cout << std::endl;
    FS fs;
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