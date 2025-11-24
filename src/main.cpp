#include "sender.h"
#include "receiver.h"
#include "channel.h"
#include <iostream>
#include <sstream>
#include <string>

std::vector<int> parse_int_list(const std::string& s) {
    std::vector<int> result;
    std::stringstream ss(s);
    int x;
    while (ss >> x) result.push_back(x);
    return result;
}

int main() {
    std::cout << "=====Simplified TCP Simulation=====\n";

    int delay;
    std::cout << "Enter propagation delay in ms: ";
    std::cin >> delay;

    std::cin.ignore();

    std::string drop_pkt_str;
    std::cout << "Enter packet numbers to drop, or leave blank: ";
    std::getline(std::cin, drop_pkt_str);

    std::string drop_ack_str;
    std::cout << "Enter ACK numbers to drop, or leave blank: ";
    std::getline(std::cin, drop_ack_str);

    Channel channel(delay);
    channel.drop_packets = parse_int_list(drop_pkt_str);
    channel.drop_acks = parse_int_list(drop_ack_str);

    Sender sender(&channel);
    Receiver receiver(&channel);

    channel.deliver_to_receiver = [&](const Packet& p){
        receiver.on_receive(p);
    };

    channel.deliver_to_sender = [&](const Packet& p){
        sender.on_ack(p);
    };

    std::cout << "\nRunning simulation...\n";

    sender.send_data("Yo whats up");
    sender.send_data("Kansane Teto word of the day: ");
    sender.send_data("TCP");

    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "\nSimulation ended.\n";
	//need this for my test script ngl
	std::this_thread::sleep_for(std::chrono::seconds(2));
}

