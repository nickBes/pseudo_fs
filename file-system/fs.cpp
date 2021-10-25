#include "fs.h"

FS::FS(const char* name, int size) {
    // initializing a new prefix tree
    path = ROOT_PREFIX;
    path += DELIMITER;
    block_device = std::make_unique<Blkd>(name, size);
    prefix_tree = std::make_unique<PrefixTrie>();
    free_memory_list.push_back(std::make_shared<MemChunk>(0, size));
    free_memory = size;
    // deserialization isn't implemented yet ...
}

bool FS::show_content(const char* name) {
    if (!prefix_tree->current.expired()) {
        const int index = prefix_tree->current.lock()->find_file_locally(name);
        if (index == -1) {
            std::cout << "File doesn't exists." << std::endl;
            return false;
        }
        const std::vector<std::unique_ptr<Chunk>>& chunks = prefix_tree->current.lock()->get_prefix_node(index)->get_chunks();
        char* buffer;
        for(const auto& chunk : chunks){
            const int size = chunk->get_next_mem_chunk()->index - chunk->get_index();
            buffer = new char[size];
            block_device->read(chunk->get_index(), size, buffer);
            std::cout << buffer;
            delete[] buffer;
        }
        std::cout << std::endl;
        return true;
    }
    std::cout << "Current dir doesn't exist anymore." << std::endl;
    return false;
}

bool FS::make_file(const char* name, int data_size, const char* data) {
    const int org_size = data_size;
    if (data_size <= free_memory) {
        if (prefix_tree->current.expired()) {
            std::cout << "Current dir doesn't exist anymore." << std::endl;
            return false;
        }
        std::shared_ptr<PrefixNode> file_prefix = std::make_shared<PrefixNode>(name, prefix_tree->current.lock());
        bool created_prefix = prefix_tree->current.lock()->add_prefix(file_prefix);
        if (!created_prefix) {
            std::cout << "Couldn't create a prefix for this file" << std::endl;
            return false;
        }
        int data_index = 0;
        while (!free_memory_list.empty()) {
            if (data_size <= 0) {
                printf("File of size %dB has been created.\n", org_size);
                free_memory -= org_size;
                return true;
            } else {
                const int next_size = std::min(data_size, free_memory_list.front()->size);
                const int chunk_left_size = free_memory_list.front()->size - next_size;
                std::shared_ptr<MemChunk> next_mem_chunk = std::make_shared<MemChunk>(
                    free_memory_list.front()->index + next_size,
                    chunk_left_size
                );
                if (chunk_left_size > 0) free_memory_list.push_back(next_mem_chunk);
                file_prefix->add_chunk(free_memory_list.front()->index, next_mem_chunk);
                char* data_chunk = new char[next_size]; 
                for (int i = 0; i < next_size; i++) {
                    data_chunk[i] = data[data_index + i];
                }
                block_device->write(free_memory_list.front()->index, next_size, data_chunk);
                delete[] data_chunk;
                free_memory_list.erase(free_memory_list.begin());
                data_size -= next_size;
                data_index += next_size;
            }
        }

    }
    printf("File of size %dB wouldn't fit (%dB space left)\n", org_size, free_memory);
    return false;
}

bool FS::make_dir(const char* name) {
    if (!prefix_tree->current.expired()) {
        std::shared_ptr<PrefixNode> dir_prefix = std::make_shared<PrefixNode>(name, prefix_tree->current.lock());
        prefix_tree->current.lock()->add_prefix(dir_prefix);
        return true;
    }
    return false;
}

void FS::print_current() {
    if(!prefix_tree->current.expired()) {
        std::cout << path << std::endl;
        prefix_tree->current.lock()->print_all_local();
    }
}

void FS::go_to_local(std::string prefix) {
    if (!prefix_tree->current.expired()) {
            int index = prefix_tree->current.lock()->find_dir_locally(prefix);
            if (index != -1) {
                std::shared_ptr<PrefixNode>& tmp = prefix_tree->current.lock()->get_prefix_node(index);
                prefix_tree->current.reset();
                prefix_tree->current = tmp;
                path += prefix_tree->current.lock()->get_prefix_name() + DELIMITER;
            }
    }
}

void FS::go_back() {
    if(!prefix_tree->is_head()) {
        std::shared_ptr<PrefixNode> tmp = prefix_tree->current.lock()->get_parent().lock();
        prefix_tree->current.reset();
        prefix_tree->current = tmp;

        path = path.substr(0, path.find_last_of(DELIMITER)); // remove last delimiter
        path = path.substr(0, path.find_last_of(DELIMITER) + 1); // remove last prefix
    }
}