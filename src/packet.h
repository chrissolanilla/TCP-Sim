#pragma once
#include <string>

struct Packet {
    int seq;
    int ack;
    bool is_ack;
    std::string data;
};

