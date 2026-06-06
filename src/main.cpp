// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include "tree.h"
int fact(int n) {
  int res = 1;
  for (int i = 2; i <= n; i++) {
    res *= i;
  }
  return res;
}
int main() {
  std::ofstream fout("result/data.txt");
  std::srand(static_cast<unsigned>(std::time(nullptr)));
  for (int n = 3; n <= 9; n++) {
    std::vector<char> arr;
    for (int i = 0; i < n; i++) {
      arr.push_back('a' + i);
    }
    PMTree tree(arr);
    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<char>> all = getAllPerms(tree);
    auto t2 = std::chrono::high_resolution_clock::now();
    int num = std::rand() % fact(n) + 1;
    auto t3 = std::chrono::high_resolution_clock::now();
    std::vector<char> p1 = getPerm1(tree, num);
    auto t4 = std::chrono::high_resolution_clock::now();
    std::vector<char> p2 = getPerm2(tree, num);
    auto t5 = std::chrono::high_resolution_clock::now();
    int64_t timeAll =
        std::chrono::duration_cast
        <std::chrono::microseconds>(t2 - t1).count();
    int64_t timeP1 =
        std::chrono::duration_cast
        <std::chrono::microseconds>(t4 - t3).count();
    int64_t timeP2 =
        std::chrono::duration_cast
        <std::chrono::microseconds>(t5 - t4).count();
    fout << n << " "
         << timeAll << " "
         << timeP1 << " "
         << timeP2 << std::endl;
    std::cout << n << std::endl;
  }
  fout.close();
  return 0;
}
