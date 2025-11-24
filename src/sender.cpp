#include "sender.h"
#include <iostream>
#include <chrono>

void Sender::send_data(const std::string& msg) {
    if (next_seq < base + window_size) {
        Packet p;
        p.seq = next_seq;
        p.data = msg;
        p.is_ack = false;

        std::cout << "[SENDER] sending seq=" << p.seq << "\n";
        unacked[p.seq] = p;

        channel->send_to_receiver(p);

        if (!timer_running) start_timer();
        next_seq++;
    } else {
        std::cout << "[SENDER] window full, cannot send\n";
    }
}

void Sender::start_timer() {
    timer_running = true;
    std::thread([this]() { timeout_handler(); }).detach();
}

void Sender::timeout_handler() {
    std::this_thread::sleep_for(std::chrono::milliseconds(timeout_ms));
    if (unacked.count(base)) {
        std::cout << "[SENDER] TIMEOUT, retransmitting window\n";
        for (auto& kv : unacked)
            channel->send_to_receiver(kv.second);
        start_timer();
    } else {
        timer_running = false;
    }
}

void Sender::on_ack(const Packet& p) {
    std::cout << "[SENDER] received ACK=" << p.ack << "\n";

    if (unacked.count(p.ack)) {
        unacked.erase(p.ack);
        base = p.ack + 1;

        if (unacked.empty()) {
            timer_running = false;
        }
    }
}

