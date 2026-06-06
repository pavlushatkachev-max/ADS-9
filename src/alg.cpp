// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <vector>
#include "tree.h"
namespace {
void walk(PMTree::Node* now,
          std::vector<char>* way,
          std::vector<std::vector<char>>* ans) {
  if (now->sons.empty()) {
    if (!way->empty()) {
      ans->push_back(*way);
    }
    return;
  }
  for (size_t i = 0; i < now->sons.size(); i++) {
    way->push_back(now->sons[i]->ch);
    walk(now->sons[i], way, ans);
    way->pop_back();
  }
}
int fact(int n) {
  int res = 1;
  for (int i = 2; i <= n; i++) {
    res *= i;
  }
  return res;
}
}
std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> ans;
  std::vector<char> way;
  walk(tree.getTop(), &way, &ans);
  return ans;
}
std::vector<char> getPerm1(PMTree& tree, int num) {
  std::vector<std::vector<char>> all = getAllPerms(tree);
  if (num < 1 || num > static_cast<int>(all.size())) {
    return {};
  }
  return all[num - 1];
}
std::vector<char> getPerm2(PMTree& tree, int num) {
  PMTree::Node* now = tree.getTop();
  int n = static_cast<int>(now->sons.size());
  if (num < 1 || num > fact(n)) {
    return {};
  }
  std::vector<char> ans;
  num--;
  while (!now->sons.empty()) {
    int block = fact(static_cast<int>(now->sons.size()) - 1);
    int pos = num / block;
    ans.push_back(now->sons[pos]->ch);
    now = now->sons[pos];
    num %= block;
  }
  return ans;
}
