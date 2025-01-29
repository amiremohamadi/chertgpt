#ifndef ENCODER_HH
#define ENCODER_HH

#include <vector>
#include <string>
#include <map>

struct encoder_t {
    std::map<char, int> table;
};

std::string decode(encoder_t &e, std::vector<int> &chars);
std::vector<int> encode(encoder_t &e, std::string buf);

#endif // ENCODER_HH
