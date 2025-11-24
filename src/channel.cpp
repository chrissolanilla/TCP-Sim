#include "channel.h"
#include <thread>
#include <chrono>
#include <algorithm>

void Channel::send_to_receiver(const Packet& p) {
    if (!p.is_ack &&
        std::find(drop_packets.begin(), drop_packets.end(), p.seq) != drop_packets.end())
    {
        std::cout << "[CHANNEL] DROPPED PACKET seq=" << p.seq << "\n";
        return;
    }

    std::thread([this,p]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
        deliver_to_receiver(p);
    }).detach();
}

void Channel::send_to_sender(const Packet& p) {
    if (p.is_ack &&
        std::find(drop_acks.begin(), drop_acks.end(), p.ack) != drop_acks.end())
    {
        std::cout << "[CHANNEL] DROPPED ACK ack=" << p.ack << "\n";
        return;
    }

    std::thread([this,p]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
        deliver_to_sender(p);
    }).detach();
}

