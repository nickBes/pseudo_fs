#include "blkd.h"
#include "trie.h"

class FS {
    std::string path;
    std::unique_ptr<Blkd> block_device;
    std::unique_ptr<PrefixTrie> prefix_tree;
    std::vector<std::shared_ptr<struct MemChunk>> free_memory_list;
    public:
        FS(const char* name=BLK_FILE_DEFAULT_NAME, int size=BLK_FILE_DEFAULT_SIZE);
        bool make_file(const char* name, const char* data);
        void make_dir(const char* name);
        void print_current();
        void go_to_local(std::string prefix);
        void go_back();
};