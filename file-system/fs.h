#include "blkd.h"
#include "trie.h"
#include <algorithm>

class FS {
    std::string path;
    std::unique_ptr<Blkd> block_device;
    std::unique_ptr<PrefixTrie> prefix_tree;
    std::vector<std::shared_ptr<MemChunk>> free_memory_list;
    int free_memory;
    public:
        FS(const char* name=BLK_FILE_DEFAULT_NAME, int size=BLK_FILE_DEFAULT_SIZE);
        bool make_file(const char* name, int data_size, const char* data);
        bool make_dir(const char* name);
        void print_current();
        void go_to_local(std::string prefix);
        void go_back();
};