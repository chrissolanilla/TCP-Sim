#!/bin/bash

OUTDIR="test_results"
mkdir -p "$OUTDIR"

run_test() {
    TEST_NAME=$1
    DELAY=$2
    DROP_PKTS=$3
    DROP_ACKS=$4

    OUTFILE="$OUTDIR/${TEST_NAME}.txt"

    echo "=== Running Test: $TEST_NAME ==="
    echo "Delay:       $DELAY" > "$OUTFILE"
    echo "Drop Packets: $DROP_PKTS" >> "$OUTFILE"
    echo "Drop ACKs:    $DROP_ACKS" >> "$OUTFILE"
    echo "" >> "$OUTFILE"
    echo "----- Program Output -----" >> "$OUTFILE"

    printf "%s\n%s\n%s\n" "$DELAY" "$DROP_PKTS" "$DROP_ACKS" | ./build/tcp_sim >> "$OUTFILE"

    echo "Saved to $OUTFILE"
    echo ""
}


run_test "01_no_loss" 0 "" ""
run_test "02_drop_packet_1" 300 "1" ""
run_test "03_drop_ack_1" 300 "" "1"
run_test "04_out_of_order" 0 "1" ""
run_test "05_high_delay" 1000 "" ""
echo "All tests completed!"

