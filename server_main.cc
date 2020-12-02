#include <array>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <vector>

#include "network.h"
#include "timer.h"
#include "secret_sharing_efficient_tools.h"

typedef uint64_t Num;
typedef std::vector<Num> Array;

void run(int64_t depth, NetAdapter *net) {
  static triplet_b tri;
  const int64_t K = 1 << depth;
  std::cout << "depth = " << depth << std::endl;
  // std::cout << "K = " << K << std::endl;
  Array path(depth * K);

  auto res_edge_count = depth;
  while (res_edge_count > 1) {
    auto _half = res_edge_count / 2;
    Array path1(_half * K), path2(_half * K);
    for (auto i = 0; i < _half * K; i += K) {
      for (auto j = 0; j < K; j++) {
        path1[i + j] = path[i + j];
        path2[i + j] = path[i + j + _half * K];
      }
    }
    secure_mul_server_batch(path1.data(), path2.data(), path.data(), _half, tri,
                            net);

    path.resize(_half * K);
    res_edge_count = _half;
  }
  // std::cout << "path array length is: " << path.size() << std::endl;

  Array predict_value(K), final_result(K);
  secure_mul_server_batch(path.data(), predict_value.data(),
                          final_result.data(), K, tri, net);

  uint64_t sum = 0;
  for (uint64_t i = 0; i < K; i++) {
    sum += final_result[i];
  }
}

int main(int argc, char *argv[]) {
  NetAdapter net(0);
  std::vector<int> trees;
  for (int i = 1; i < argc; i++) {
    trees.push_back(atoi(argv[i]));
  }

  // run(trees[0], &net);
  for (auto tree: trees) {
    Timer t;
    run(tree, &net);
  }

  return 0;
}
