#include "trie.h"

PrefixTrie::PrefixTrie() {
    head = std::make_shared<PrefixNode>(ROOT_PREFIX, nullptr);
    current = head;
    current.lock()->set_parent(head);
}

bool PrefixTrie::is_head() {
    if (!current.expired() && current.lock().get() == head.get()) {
        return true;
    }
    return false;
}

PrefixNode::PrefixNode(const char * name, const std::shared_ptr<PrefixNode>& parent) {
    this->name = name;
    this->set_parent(parent);
}

void PrefixNode::set_parent(const std::shared_ptr<PrefixNode>& parent) {
    if (parent) {
        this->parent = parent;
    }
}

const std::weak_ptr<PrefixNode>& PrefixNode::get_parent() const { return parent;}

std::shared_ptr<PrefixNode>& PrefixNode::get_prefix_node(int index) {return next_prefixes[index];}

void PrefixNode::print_all_local() {
    for (auto const& prefix_node : next_prefixes) {
        std::cout << '\t' << prefix_node->get_prefix_name() << (prefix_node->is_dir() ? "/" : "" );
    }
    std::cout << std::endl;
}

void PrefixNode::add_chunk(int index, std::shared_ptr<MemChunk>& mem_chunk) {
    chunks.push_back(std::make_unique<Chunk>(index, mem_chunk));
}

bool PrefixNode::add_prefix(std::shared_ptr<PrefixNode>& prefix) {
    for (auto const& prefix_node : next_prefixes) {
        if (prefix_node->get_prefix_name().compare(prefix->get_prefix_name()) == 0) {
            printf("Prefix `%s` already exists.\n", prefix_node->get_prefix_name().c_str());
            return false;
        }
    }
    next_prefixes.push_back(prefix);
    return true;
}

const std::string& PrefixNode::get_prefix_name() const {return name;}

int PrefixNode::find_dir_locally(std::string prefix) {
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

Chunk::Chunk(int index, std::shared_ptr<MemChunk>& mem_chunk) {
    this->index = index;
    this->next_chunk = mem_chunk;
}

MemChunk::MemChunk(int index, int size) {
    this->index = index;
    this->size = size;
}