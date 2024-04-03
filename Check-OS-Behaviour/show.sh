#!/bin/bash

# Definitions
YELLOW='\033[0m\033[38;2;255;255;0m'
GRAY='\033[0m\033[38;2;230;230;230m'
CYAN='\033[0m\033[38;2;0;230;230m'
CYAN_BOLD='\033[1m\033[38;2;0;230;230m'
GREEN='\033[0m\033[38;2;0;255;0m'
RED='\033[0m\033[38;2;255;0;0m'
RESET='\033[0m'
ENDL='\n'
TAB='   '

# Log Aternatives
WARNING="${YELLOW}[WARNING]${RESET}"
SUCCESS="${GREEN}[SUCCESS]${RESET}"
FAILED="${RED}[FAILED]${RESET}"
LOG="${GRAY}[LOG]${RESET}"

# - Extract CPU Information
echo -e "${CYAN_BOLD}CPU Information${RESET}"
echo -e "${TAB}${LOG} CPU Model : $CYAN$(lscpu | grep "Model name" | awk -F ":" '{print $2}' | sed 's/^[[:space:]]*//')$RESET"
echo -e "${TAB}${LOG} CPU Architecture : $CYAN$(lscpu | grep "Architecture" | awk -F ":" '{print $2}' | sed 's/^[[:space:]]*//')$RESET"
echo -e "${TAB}${LOG} CPU Cores : $CYAN$(cat /proc/cpuinfo | grep -F processor | wc -l)$RESET"
sum=0
count=0
while read -r value; do
    sum=$(echo "$sum + $value" | bc)
    ((count++))
done < <(cat /proc/cpuinfo | grep 'cpu MHz' | awk '{print $4}')
average=$(echo "scale=3; $sum / $count" | bc)
echo -e "${TAB}${LOG} CPU Average Speed : $CYAN$average$RESET"

# - Extract Memory Information
echo -e "${CYAN_BOLD}Memory Information${RESET}"
echo -e "${TAB}${LOG} Total Memory : $CYAN$(cat /proc/meminfo | grep 'MemTotal' | awk '{print $2 " " $3}')$RESET"
# - Check Free Memory in 5 Seconds
count=0
while [ $count -lt 5 ]; do
    echo -e "${TAB}${LOG} Free Memory in $GRAY$(date "+%H:%M:%S")$RESET : $CYAN$(grep 'MemFree' /proc/meminfo | awk '{print $2 " " $3}')$RESET"
    sleep 0.1
    count=$((count+1))
done

# - Extract Kernel Information
echo -e "${CYAN_BOLD}Kernel Information${RESET}"
echo -e "${TAB}${LOG} Kernel Version 1 : $CYAN$(uname -r)$RESET"
echo -e "${TAB}${LOG} Kernel Version 2 : $CYAN$(cat /proc/sys/kernel/version)$RESET"