#include "trie.h"

PrefixTrie::PrefixTrie() {
    head = std::make_shared<PrefixNode>("");
    current = head;
}

PrefixNode::PrefixNode(const char * name) {
    this->name = name;
}

std::shared_ptr<PrefixNode>& PrefixNode::get_prefix_node(int index) {return next_prefixes[index];}

void PrefixNode::print_all_local() {
    for (auto const& prefix_node : next_prefixes) {
        std::cout << '\t' << prefix_node->get_prefix_name() << (prefix_node->is_dir() ? "/" : "" );
    }
    std::cout << std::endl;
}

void PrefixNode::add_chunk(int index, std::shared_ptr<struct MemChunk>& mem_chunk) {
    chunks.push_back(std::make_unique<Chunk>(index, mem_chunk));
}

void PrefixNode::add_prefix(const char* name) {
    next_prefixes.push_back(std::make_shared<PrefixNode>(name));
}

const std::string& PrefixNode::get_prefix_name() const {return name;}

int PrefixNode::find_locally(std::string prefix) {
    std::cout << "Searching for a local prefix\n";
    for (std::size_t i = 0; i < next_prefixes.size(); i++) {
        if (next_prefixes[i]->get_prefix_name().compare(prefix) == 0 && next_prefixes[i]->is_dir()) {
            return i;
        }
    }
    std::cout << "Didn't find any matching prefix" << std::endl;
    return -1;
}

bool PrefixNode::is_dir() {return chunks.size() == 0;}

Chunk::Chunk(int index, std::shared_ptr<struct MemChunk>& mem_chunk) {
    this->index = index;
    this->next_chunk = mem_chunk;
}

MemChunk::MemChunk(int index, int size) {
    this->index = index;
    this->size = size;
}