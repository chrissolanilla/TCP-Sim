#pragma once
#include "packet.h"
#include "channel.h"
#include <iostream>

class Receiver {
public:
    int expected = 0;
    Channel* channel;

    Receiver(Channel* c) : channel(c) {}

    void on_receive(const Packet& p);
};

