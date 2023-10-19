#!/bin/bash

for (( i = 0; i < 5; i++ )); do
    ./zappy_ai -n "Team1" -p 4242 &
    sleep 0.1
    ./zappy_ai -n "Team2" -p 4242 &
    sleep 0.1
    ./zappy_ai -n "Team3" -p 4242 &
    sleep 0.1
    ./zappy_ai -n "Team4" -p 4242 &
    sleep 0.1
done