#include <vector>
#include <memory>

struct MemChunk {
    int index;
    int size;
};

class Chunk {
    int index;
    std::shared_ptr<struct MemChunk> next_chunk;
};

class PrefixNode {
    // average character amount in a sentence is 115
    char name[115];
    std::vector<PrefixNode> next_prefixes;
    std::vector<Chunk> chunks;
};

class PrefixTrie {
    PrefixNode head;
};