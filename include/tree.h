// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <algorithm>
#include <cstddef>
class PMTree {
 public:
  struct Node {
    char ch;
    std::vector<Node*> sons;
    explicit Node(char c) {
      ch = c;
    }
  };
 private:
  Node* top;
  void make(Node* now, std::vector<char> left) {
    if (left.empty()) {
      return;
    }
    std::sort(left.begin(), left.end());
    for (size_t i = 0; i < left.size(); i++) {
      Node* son = new Node(left[i]);
      now->sons.push_back(son);
      std::vector<char> tmp = left;
      tmp.erase(tmp.begin() + i);
      make(son, tmp);
    }
  }
  void drop(Node* now) {
    if (now == nullptr) {
      return;
    }
    for (size_t i = 0; i < now->sons.size(); i++) {
      drop(now->sons[i]);
    }
    delete now;
  }
 public:
  explicit PMTree(std::vector<char> arr) {
    top = new Node('\0');
    std::sort(arr.begin(), arr.end());
    make(top, arr);
  }
  ~PMTree() {
    drop(top);
  }
  Node* getTop() {
    return top;
  }
};
std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);
#endif  // INCLUDE_TREE_H_
