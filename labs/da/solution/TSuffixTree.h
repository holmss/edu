#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>
#include <iostream>

#include <map>
#include <memory>

struct TNode {
    std::map<char, std::shared_ptr<TNode>> to_edge;
    std::string::iterator begin, end; // Отрезок [begin, end]
    std::weak_ptr<TNode> suffix_link; // Суффиксная ссылка
    size_t index;
    TNode (std::string::iterator begin, std::string::iterator end) : to_edge(), begin(begin), end(end), index(0) {};
};

namespace NTree {
    const char symbol = '$';
    class TSuffixTree {
    private:
        std::string text; // текст
        std::shared_ptr<TNode> root; // корень
        size_t remainder;
        std::weak_ptr<TNode> sl_need, active_node;
        size_t active_length;
        std::string::iterator active_edge;

        void Index(std::shared_ptr<TNode>, size_t deep = 0);
        void AddLink(std::shared_ptr<TNode>);
        bool WalkDown(std::string::iterator, std::shared_ptr<TNode>);
        size_t EdgeLength(std::shared_ptr<TNode> node, std::string::iterator position);
        void Extend (std::string::iterator);
        void GetEntries(std::shared_ptr<TNode>, std::vector<size_t>&);
    public:
        TSuffixTree (const std::string& text); 
        std::vector<size_t> Find(const std::string& pattern);
    };

}



#endif
