#include "fs.h"

FS::FS(const char* name, int size) {
    // initializing a new prefix tree
    path = "";
    block_device = std::make_unique<Blkd>(name, size);
    prefix_tree = std::make_unique<PrefixTrie>();
    free_memory_list.push_back(std::make_shared<struct MemChunk>(0, size));
    // deserialization isn't implemented yet ...
}

void FS::make_dir(const char* name) {
    if (!prefix_tree->current.expired()) {
        std::shared_ptr<PrefixNode> dir_prefix = std::make_shared<PrefixNode>(name, prefix_tree->current.lock());
        prefix_tree->current.lock()->add_prefix(dir_prefix);
    }
}

void FS::print_current() {
    if(!prefix_tree->current.expired()) {
        std::cout << path << std::endl;
        prefix_tree->current.lock()->print_all_local();
    }
}

void FS::go_to_local(std::string prefix) {
    if (!prefix_tree->current.expired()) {
            int index = prefix_tree->current.lock()->find_locally(prefix);
            if (index != -1) {
                std::shared_ptr<PrefixNode>& tmp = prefix_tree->current.lock()->get_prefix_node(index);
                prefix_tree->current.reset();
                prefix_tree->current = tmp;
                path += prefix_tree->current.lock()->get_prefix_name() + DELIMITER;
            }
    }
}

void FS::go_back() {
    if(!prefix_tree->current.expired()) {
        std::shared_ptr<PrefixNode> tmp = prefix_tree->current.lock()->get_parent().lock();
        prefix_tree->current.reset();
        prefix_tree->current = tmp;

        path = path.substr(0, path.find_last_of(DELIMITER)); // remove last delimiter
        path = path.substr(0, path.find_last_of(DELIMITER) + 1); // remove last prefix
    }
}