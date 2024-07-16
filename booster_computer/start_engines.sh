#!/bin/bash

# Function to kill any process using a specific port
kill_process_on_port() {
    port=$1
    pid=$(lsof -t -i:$port)
    if [ -n "$pid" ]; then
       # echo "Killing process $pid on port $port"
        kill -9 $pid
    fi
}

# Start engine computers on different ports
for port in {8080..8087}; do
    kill_process_on_port $port  # Kill any existing process on the port
    ./engine_computer $port &
    echo "Started engine computer on port $port"
done

# Wait for all background jobs to complete (optional)
wait
