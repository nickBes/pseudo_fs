#include <iostream>
#include <vector>
#include <memory>
#include <string>

#define PREFIX_NAME_SIZE 115
#define DELIMITER "/"
#define ROOT_PREFIX "💎"

struct MemChunk {
    int index;
    int size;

    MemChunk(int index, int size);
};

class Chunk {
    int index;
    std::shared_ptr<MemChunk> next_chunk;

    public:
        std::shared_ptr<MemChunk>& get_next_mem_chunk();
        int& get_index();
        Chunk(int index, std::shared_ptr<MemChunk>& mem_chunk);
};

class PrefixNode {
    std::string name;
    std::vector<std::shared_ptr<PrefixNode>> next_prefixes;
    std::vector<std::unique_ptr<Chunk>> chunks;
    std::weak_ptr<PrefixNode> parent;

    public:
        PrefixNode(const char* name, const std::shared_ptr<PrefixNode>& parent);
        void add_chunk(int index, std::shared_ptr<MemChunk>& mem_chunk);
        bool add_prefix(std::shared_ptr<PrefixNode>& prefix);

        void set_parent(const std::shared_ptr<PrefixNode>& parent);
        const std::weak_ptr<PrefixNode>& get_parent() const;

        int find_file_locally(std::string name);
        const std::vector<std::unique_ptr<Chunk>>&  get_chunks() const;

        int find_dir_locally(std::string path);
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
        bool is_head();
};