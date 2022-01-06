#!/bin/bash

read -N 1 move
touch move.txt
printf "%c" $move &> move.txt