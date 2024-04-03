#!/bin/bash

# Definitions
YELLOW='\033[0m\033[38;2;255;255;0m'
GRAY='\033[0m\033[38;2;230;230;230m'
CYAN='\033[0m\033[38;2;0;230;230m'
CYAN_BOLD='\033[1m\033[38;2;0;230;230m'
GREEN='\033[0m\033[38;2;0;255;0m'
RED='\033[0m\033[38;2;200;120;0m'
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
sum=0
count=0
while read -r value; do
    sum=$(echo "$sum + $value" | bc)
    ((count++))
done < <(cat /proc/cpuinfo | grep 'cpu MHz' | awk '{print $4}')
average=$(echo "scale=3; $sum / $count" | bc)
echo -e "${TAB}${LOG} Current CPU Average Speed : $CYAN$average$RESET"
echo -e "${TAB}${LOG} CPU Architecture : $CYAN$(lscpu | grep "Architecture" | awk -F ":" '{print $2}' | sed 's/^[[:space:]]*//')$RESET"
echo -e "${TAB}${LOG} CPU Cores : $CYAN$(cat /proc/cpuinfo | grep -F processor | wc -l)$RESET"

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

# - Extract Uptime Information
echo -e "${CYAN_BOLD}System Information${RESET}"
echo -e "${TAB}${LOG} Max Opened File (Maximum File Descriptos) : $CYAN$(cat /proc/sys/fs/file-max)$RESET"
echo -e "${TAB}${LOG} Max Pipe Size (Maximum IPC Size) : $CYAN$(cat /proc/sys/fs/pipe-max-size)$RESET"
echo -e "${TAB}${LOG} OS Release : $CYAN$(cat /proc/sys/kernel/osrelease)$RESET"
echo -e "${TAB}${LOG} OS Type : $CYAN$(cat /proc/sys/kernel/ostype)$RESET"
echo -e "${TAB}${LOG} Uptime : $CYAN$(cat /proc/uptime | awk '{print $1}')$RESET"

# - Method to Check if Interface is UP or DOWN
check_interface() {
    local interface="$1"
    if ip link show "$interface" >/dev/null 2>&1; then
        if ip link show "$interface" | grep -q "state UP"; then
            echo -e "$GREEN${interface}$RESET"
        else
            echo -e "$RED$interface$RESET"
        fi
    else
        echo "Device \"$interface\" does not exist."
    fi
}

# - Method to Convert bytes to Kilobytes
bytes_to_megabytes() {
    local bytes=$1
    local kilobytes=$(echo "scale=3; $bytes / 1024" | bc)
    echo "$kilobytes"
}

# - Method to Show Packets of Interface
check_packets() {
    local interface="$1"
    if ip link show "$interface" >/dev/null 2>&1; then
        if ip link show "$interface" | grep -q "state UP"; then
            # echo -e "${TAB}${LOG} Amount of Received Packets from $GREEN$interface$RESET : $CYAN$(cat /sys/class/net/$interface/statistics/rx_packets)$RESET"
            transmit_size=$(bytes_to_megabytes "$(cat /proc/net/dev | grep $interface | awk '{print $10}')")
            receive_size=$(bytes_to_megabytes "$(cat /proc/net/dev | grep $interface | awk '{print $2}')")
            transmit_amount=$(bytes_to_megabytes "$(cat /proc/net/dev | grep $interface | awk '{print $11}')")
            receive_amount=$(bytes_to_megabytes "$(cat /proc/net/dev | grep $interface | awk '{print $3}')")
            # - Size
            echo -e "${TAB}${LOG} Packets Sizes of $GREEN$interface$RESET :"
            echo -e "${TAB}${TAB}- Transmit Size : $CYAN$transmit_size$RESET MB"
            echo -e "${TAB}${TAB}- Receive Size : $CYAN$receive_size$RESET MB"
            # - Amount
            echo -e "${TAB}${LOG} Packets Amount of $GREEN$interface$RESET :"
            echo -e "${TAB}${TAB}- Transmit Amount : $CYAN$transmit_amount$RESET"
            echo -e "${TAB}${TAB}- Receive Amount : $CYAN$receive_amount$RESET"
        fi
    fi
}

# - Extract Network Information
echo -e "${CYAN_BOLD}Network Information${RESET}"
echo -e "${TAB}${LOG} Network Interfaces :$RESET"
ip link show | grep -F 'mtu' | awk '{print $2}' | sed 's/://' | while read -r interface; do
    echo -e "$TAB$TAB- $(check_interface "${interface}")"
done
ip link show | grep -F 'mtu' | awk '{print $2}' | sed 's/://' | while read -r interface; do
    check_packets "${interface}"
done
echo -e "${TAB}${LOG} Network IP Address : $CYAN$(hostname -I)$RESET"
echo -e "${TAB}${LOG} Network Gateway : $CYAN$(ip route | grep -F 'default' | awk '{print $3}')$RESET"

# - Extract Input Devices
echo -e "${CYAN_BOLD}Input Devices${RESET}"
while IFS= read -r line; do
    # Check if the line starts with "N: Name="
    if [[ $line == N:\ Name=* ]]; then
        # Extract the device name
        device_name=$(echo "$line" | cut -d'"' -f2)
        echo -e "$TAB$LOG $device_name"
    fi
done < "/proc/bus/input/devices"