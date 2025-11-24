#pragma once
#include "packet.h"
#include "channel.h"
#include <map>
#include <thread>
#include <atomic>

class Sender {
public:
    int window_size = 4;
    int next_seq = 0;
    int base = 0;
    bool timer_running = false;
    int timeout_ms = 1000;

    Channel* channel;

    std::map<int,Packet> unacked;

    Sender(Channel* c) : channel(c) {}

    void send_data(const std::string& msg);
    void start_timer();
    void timeout_handler();
    void on_ack(const Packet& p);
};

