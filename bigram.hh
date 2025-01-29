#ifndef BIGRAM_HH
#define BIGRAM_HH

#include <vector>
#include <random>
#include <algorithm>

struct bigram_t {
    int vocab_size;
    std::vector<std::vector<float>> token_embedding_table;
    std::vector<std::vector<float>> m, v;
};

void init_bigram(bigram_t &b, int size);
std::vector<float> forward(bigram_t &b, int pos);
void train(bigram_t& b, std::vector<int>& data, int iter, float lr);
int generate(bigram_t &b, int pos);

#endif // BIGRAM_HH
