#include "blkd.h"
#include "trie.h"

class FS {
    Blkd block_device;
    PrefixTrie prefix_tree;
    std::vector<std::weak_ptr<struct MemChunk>> free_memory_list;
};