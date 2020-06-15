#include "TSuffixTree.h"

namespace NTree {
    TSuffixTree::TSuffixTree(const std::string& string) : text(string), root(), remainder(0), sl_need(), active_node(), active_length(0), active_edge() {
        text.push_back(symbol);
        root = std::make_shared<TNode> (text.end() - 1, text.end() - 1);
        root -> suffix_link = root;
        root -> index = -1;
        active_edge = text.begin();
        active_node = sl_need = root;
        for (auto it = text.begin(); it != text.end(); ++it) {
            Extend(it);
        }
        Index(root);
    }
    void TSuffixTree::Extend(std::string::iterator add) {
        sl_need = root;
        ++remainder;
        while (remainder) {
            if (!active_length) {
                active_edge = add;
            }
            auto it = active_node.lock() -> to_edge.find(*active_edge);
            std::shared_ptr<TNode> next = (it == active_node.lock() -> to_edge.end()) ? nullptr : it -> second;
            if (next == nullptr) {
                std::shared_ptr<TNode> leaf = std::make_shared<TNode> (add, text.end() - 1);
                active_node.lock() -> to_edge[*active_edge] = leaf;
                AddLink(active_node.lock());
            } else {
                if (WalkDown(add, next)) {
                    continue;
                }
                if (*(next -> begin + active_length) == *add) {
                    ++active_length;
                    AddLink(active_node.lock());
                    break;
                }

                std::shared_ptr<TNode> split = std::make_shared<TNode> (next -> begin, next -> begin + active_length - 1);
                std::shared_ptr<TNode> leaf = std::make_shared<TNode> (add, text.end() - 1);
                active_node.lock() -> to_edge[*active_edge] = split;
                split -> to_edge[*add] = leaf;
                next -> begin += active_length;
                split -> to_edge [*next -> begin] = next;
                AddLink(split);
            }
            --remainder;
            if (active_node.lock() == root && active_length) {
                --active_length;
                active_edge = add - remainder + 1;
            } else {
                active_node = ((active_node.lock() -> suffix_link).lock() != nullptr) ? active_node.lock() -> suffix_link : root;
            }
        }
    }

    void TSuffixTree::AddLink(std::shared_ptr<TNode> node) {
        if (sl_need.lock() != root) {
            sl_need .lock() -> suffix_link = node;
        }
        sl_need = node;
    }

    bool TSuffixTree::WalkDown(std::string::iterator iterator, std::shared_ptr<TNode> node) {
        if (active_length >= EdgeLength(node, iterator)) {
            active_edge += EdgeLength(node, iterator);
            active_length -= EdgeLength(node, iterator);
            active_node = node;
            return true;
        }
        return false;
    }

    size_t TSuffixTree::EdgeLength(std::shared_ptr<TNode> node, std::string::iterator position) {
        return std::min(node -> end, position) + 1 - node -> begin;
    }

    void TSuffixTree::Index(std::shared_ptr<TNode> node, size_t deep) {
        node -> index += node -> end - node -> begin + deep + 1;
        //std::cout << node -> index << std::endl;
        for (auto it: node -> to_edge) Index(it.second, node -> index);
    }

    std::vector<size_t> TSuffixTree::Find(const std::string& pattern) {
        std::vector<size_t> entries;
        if (!pattern.size()) return entries;
        auto pattern_iterator = pattern.begin();
        if (root -> to_edge.find(*pattern_iterator) == root -> to_edge.end()) return entries;
        std::shared_ptr<TNode> current_node = root -> to_edge[*pattern_iterator];
        auto text_iterator = current_node -> begin;
        while (pattern_iterator != pattern.end()) {
            if (text_iterator > current_node -> end) {
                if (current_node -> to_edge.find(*pattern_iterator) == current_node -> to_edge.end()) {
                    return entries;
                }
                current_node = current_node -> to_edge[*pattern_iterator];
                text_iterator = current_node -> begin;
            }
            if (*pattern_iterator != *text_iterator) return entries;
            ++text_iterator;
            ++pattern_iterator;
        }
        // OK
        GetEntries(current_node, entries);
        return entries;
    }

    void TSuffixTree::GetEntries(std::shared_ptr<TNode> current_node, std::vector<size_t>& entries) {
        if (current_node -> to_edge.size() == 0) {
            entries.push_back(text.size() - current_node -> index + 1);
        }
        for (auto it: current_node -> to_edge) {
            GetEntries(it.second, entries);
        }
    }

}
