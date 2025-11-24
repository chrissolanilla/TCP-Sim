# Simplified TCP Simulation

This project is for UCF networks class. A simplifeid version of TCP sliding window

# Installation
```
git clone https://github.com/chrissolanilla/TCP-Sim.git
cd TCP-Sim
mkdir build
cd build
cmake ..
make

```
now you can run the executable `./tcp_sim`

# usage
Run the execuatble `./tcp_sim` and you will be prompted to enter input in the TUI
- propogation delay in ms
- packet numbers to drop
- ACK numbers to drop

if you leave the fields blank, it will result in no packet loss

# Testing
You can test the binary once built with my little bash script I made `test.sh`.
This Repo contains my output in the `test_results` directory
I have 5 tests.
