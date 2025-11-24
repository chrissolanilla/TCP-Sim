#include "receiver.h"

void Receiver::on_receive(const Packet& p) {
    std::cout << "[RECEIVER] got seq=" << p.seq << "\n";

    if (p.seq == expected) {
        std::cout << "[RECEIVER] accepted seq=" << p.seq << "\n";
        expected++;

        Packet ack;
        ack.is_ack = true;
        ack.ack = p.seq;

        channel->send_to_sender(ack);

    } else {
        std::cout << "[RECEIVER] out of order, resend last ACK\n";
        Packet ack;
        ack.is_ack = true;
        ack.ack = expected - 1;

        channel->send_to_sender(ack);
    }
}

