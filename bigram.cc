#include "optimizer.hh"
#include "bigram.hh"

auto softmax(std::vector<float> logits) {
    float sum = 0;
    std::vector<float> probs(logits.size());
    auto max = *std::max_element(logits.begin(), logits.end());

    for (int i = 0; i < logits.size(); i++) {
        probs[i] = std::exp(logits[i] - max);
        sum += probs[i];
    }

    for (int i = 0; i < logits.size(); i++) {
        probs[i] /= sum;
    }

    return probs;
}

// FIXME
float frand() {
    std::random_device r;
    std::uniform_real_distribution<float> dist(-0.1, 0.1);
    return dist(r);
}

void init_bigram(bigram_t &b, int vocab_size) {
    b.vocab_size =  vocab_size;
    b.token_embedding_table.resize(vocab_size, std::vector<float>(vocab_size));
    b.m.resize(vocab_size, std::vector<float>(vocab_size, 0));
    b.v.resize(vocab_size, std::vector<float>(vocab_size, 0));

    for (auto &r : b.token_embedding_table) {
        for (auto &v : r) {
            v = frand();
        }
    }
}

std::vector<float> forward(bigram_t &b, int pos) {
    return b.token_embedding_table[pos];
}

void train(bigram_t &b, std::vector<int>& data, int iter, float lr) {
    int vocab_size = b.vocab_size;
    float beta1 = 0.9f, beta2 = 0.999f, epsilon = 1e-8f, weight_decay = 0.01f;

    for (int i = 0; i < iter; i++) {
        std::vector<std::vector<float>> grads(vocab_size,
                std::vector<float>(vocab_size, 0.0f));

        // TODO: cross entropy loss

        adamw_optimizer(b.token_embedding_table, grads,
                b.m, b.v, lr, beta1, beta2, epsilon, weight_decay, iter);
    }
}

int generate(bigram_t &b, int pos) {
    float sum = 0.0f;

    std::vector<float> logits = forward(b, pos);
    std::vector<float> probs = softmax(logits);

    auto r = static_cast<float>(rand()) / RAND_MAX;
    for (size_t i = 0; i < b.vocab_size; ++i) {
        sum += probs[i];

        if (r <= sum) {
            return i;
        }
    }

    return b.vocab_size - 1;
}
