#include <iostream>
#include <fstream>
#include "bigram.hh"
#include "encoder.hh"

int main() {
    encoder_t enc;
    bigram_t model;
    std::ifstream file("./dataset.txt");
    std::string buf((std::istreambuf_iterator<char>(file)),
            (std::istreambuf_iterator<char>()));

    auto n = buf.length() * 9 / 10;
    auto train_data = encode(enc, buf.substr(0, n));

    init_bigram(model, enc.table.size());

    std::cout << "training..." << std::endl;
    train(model, train_data, 100, 0.1);

    std::cout << "generating response..." << std::endl;
    int pos = train_data[0];
    std::vector<int> response;
    for (int i = 0; i < 50; i++) {
        pos = generate(model, pos);
        response.push_back(pos);
    }

    std::cout << decode(enc, response) << std::endl;

    return 0;
}
