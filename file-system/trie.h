#include <iostream>
#include <vector>
#include <memory>
#include <string>

#define PREFIX_NAME_SIZE 115
#define DELIMITER "/"

struct MemChunk {
    int index;
    int size;

    MemChunk(int index, int size);
};

class Chunk {
    int index;
    std::shared_ptr<struct MemChunk> next_chunk;

    public:
        Chunk(int index, std::shared_ptr<struct MemChunk>& mem_chunk);
};

class PrefixNode {
    std::string name;
    std::vector<std::shared_ptr<PrefixNode>> next_prefixes;
    std::vector<std::unique_ptr<Chunk>> chunks;

    public:
        PrefixNode(const char* name);
        void add_chunk(int index, std::shared_ptr<struct MemChunk>& mem_chunk);
        void add_prefix(const char* name);
        int find_locally(std::string path);
        bool is_dir();
        const std::string& get_prefix_name() const;
        void print_all_local();
        std::shared_ptr<PrefixNode>& get_prefix_node(int index);
};

class PrefixTrie {
    std::shared_ptr<PrefixNode> head;
    public:
        PrefixTrie();
        std::weak_ptr<PrefixNode> current;
};