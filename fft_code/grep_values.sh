#!/bin/bash

grep -e "total number of instructions executed" -e "total number of loads executed" -e "total number of stores executed" -e "total number of branches executed" -e "total simulation time in seconds" -e "cycles per instruction" -e "instructions per cycle" -e "instruction per branch" -e "total power usage of alu" -e "total power usage of resultbus" -e "total power usage of clock" -e "avg power usage of alu" -e "avg power usage of resultbus" -e "avg power usage of clock" $1
