#pragma once
#include "packet.h"
#include <queue>
#include <vector>
#include <functional>
#include <iostream>

class Channel {
public:
    int delay_ms = 200;
    std::vector<int> drop_packets;
    std::vector<int> drop_acks;

    std::function<void(const Packet&)> deliver_to_receiver;
    std::function<void(const Packet&)> deliver_to_sender;

    Channel(int delay) : delay_ms(delay) {}

    void send_to_receiver(const Packet& p);
    void send_to_sender(const Packet& p);
};

