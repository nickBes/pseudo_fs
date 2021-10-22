#include <fstream>
#include <sys/stat.h>

#define BLK_FILE_DEFAULT_NAME ".blkf"
#define BLK_FILE_DEFAULT_SIZE 1000000

class Blkd {
    std::fstream blk_file;
    int size;
    int taken_space_size; 
    public:
        void open_blk_file(const char* name=BLK_FILE_DEFAULT_NAME, int size=BLK_FILE_DEFAULT_SIZE);
        void write(int index, int data_size, const char* data);
        void read(int index, int data_size, char* buffer);
        int get_taken_space_size();
        ~Blkd();
};