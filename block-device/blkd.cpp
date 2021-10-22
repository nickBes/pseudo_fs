#include <iostream>
#include "blkd.h"

void Blkd::open_blk_file(const char* name, int size) {
    // (de)serialization are not implemented yet...
    blk_file.open(name, std::fstream::in | std::fstream::out | std::fstream::binary | std::fstream::app);
    if (blk_file.is_open()) {
        blk_file.seekg(0, blk_file.end);
        if (blk_file.tellg() == 0) {
            std::cout << "blk file isn't filled.\nStarting to fill it.\n";
            for (int i = 0; i < BLK_FILE_DEFAULT_SIZE; i++) {
                blk_file << 0b0;
            }
            std::cout << "blk file is filled out.\n";
            this->size=size;
            taken_space_size=0;

            // reopen in rw+ mode as a prevents from writing by index
            blk_file.close();
            blk_file.open(name, std::fstream::in | std::fstream::out | std::fstream::binary);
        }
    } else {
        std::cout << "Couldn't open blk file.\n";
    }
    this->size=size;
    std::cout << std::endl;
}

void Blkd::write(int index, int data_size, const char* data) {
    if (blk_file.is_open()) {
        if (size <= index || index < 0) {
            printf("Index %d out of bounds.\n", index); 
        } else {
            blk_file.seekp(index);
            // prevent from oveflowing the file
            blk_file.write(data, data_size);
            taken_space_size += data_size;
            std::cout << "Writing into the file." << std::endl;
        }
    } else {
        std::cout << "Can't write when there's no file opened." << std::endl;
    }
}
void Blkd::read(int index, int data_size,  char* buffer) {
    if (blk_file.is_open()) {
        if (size <= index || index < 0) {
            printf("Index %d out of bounds.\n", index); 
        } else {
            blk_file.seekg(index);
            blk_file.read(buffer, data_size);
            std::cout << "Reading the file." << std::endl;
        }
    } else {
        std::cout << "Can't read when there's no file opened." << std::endl;
    }
}

// closing the blk file if still open
Blkd::~Blkd() {
    if (blk_file.is_open()) {
        blk_file.close();
        std::cout << "Closed blk file." << std::endl;
    }
}
int Blkd::get_taken_space_size() {return taken_space_size;}