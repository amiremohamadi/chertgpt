#include <set>
#include <algorithm>
#include "encoder.hh"

std::string decode(encoder_t &e, std::vector<int> &chars) {
    std::string decoded;
    std::map<int, char> reverse_map;

    for (auto pair : e.table) {
        reverse_map[pair.second] = pair.first;
    }

    for (auto c : chars) {
        decoded += reverse_map[c];
    }

    return decoded;
}

std::vector<int> encode(encoder_t &e, std::string buf) {
    int i = 0;
    std::vector<int> encoded(buf.length());

    std::set<char> chars(buf.begin(), buf.end());
    for (auto c : chars) {
        e.table[c] = i++;
    }

    std::transform(buf.begin(), buf.end(), encoded.begin(), [&e](char c) {
        return e.table[c];
    });

    return encoded;
}
