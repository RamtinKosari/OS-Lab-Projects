#!/bin/bash

# - Definitions
PROGRESS_BAR_END="\033[0m\033[48;2;0;100;100m "
PROGRESS_BAR_BG="\033[0m\033[48;2;30;50;50m "
PROGRESS_BAR="\033[0m\033[48;2;0;200;200m "
CYAN_BOLD='\033[1m\033[38;2;0;230;230m'
YELLOW='\033[0m\033[38;2;255;255;0m'
GRAY='\033[0m\033[38;2;230;230;230m'
CYAN='\033[0m\033[38;2;0;230;230m'
GREEN='\033[0m\033[38;2;0;255;0m'
RED='\033[0m\033[38;2;200;20;0m'
RESET='\033[0m'
ENDL='\n'
TAB='   '

# - Log Aternatives
WARNING="${YELLOW}[WARNING]${RESET}"
SUCCESS="${GREEN}[SUCCESS]${RESET}"
FAILED="${RED}[FAILED]${RESET}"
LOG="${GRAY}[LOG]${RESET}"

# - Extract IP Ranges
echo -e "${CYAN_BOLD}Extracting IP Ranges ... ${RESET}"
ip_ranges=$(cat ir.csv | cut -d',' -f1 | cut -d'.' -f1,2,3)
amount=$(wc -l < ir.csv)
echo -e "${TAB}${LOG} Total IP Ranges : $CYAN$amount$RESET"

# - Extract Apache Recorded IPs (First three octets)
echo -e "${CYAN_BOLD}Extracting Apache Recorded IPs ... ${RESET}"
apache_amount=$(wc -l < apache_logs.log)
apache_records=$(cat apache_logs.log | cut -d' ' -f1 | cut -d'.' -f1,2,3)
echo -e "${TAB}${LOG} Total Apache Recorded IPs : $CYAN$apache_amount$RESET"


# - Search for IPs in IP Ranges Available in Apache Records
echo -e "${CYAN_BOLD}Searching for IP Ranges in Apache IPs ...${RESET}"
function drawProgressBar {
    percentage=$(echo "scale=2; $1" | bc)
    cols=$(tput cols)
    progressBarWidth=$((cols - 10))
    completedWidth=$(echo "scale=0; $percentage * $progressBarWidth / 100" | bc)
    printf "$PROGRESS_BAR_END\033[0m"
    for ((i = 0; i < completedWidth; i++)); do printf "$PROGRESS_BAR"; done
    for ((i = completedWidth; i < progressBarWidth; i++)); do printf "$PROGRESS_BAR_BG"; done
    printf "$PROGRESS_BAR_END\033[0m %.2f%%\r" "$percentage"
}
found=""
progress=0
total=$(echo "$ip_ranges" | wc -l)
tput civis
while read -r ip; do
    if grep -q "$ip" <<< "$apache_records"; then
        apache_ip=$(cat apache_logs.log | grep $ip | awk '{print $1}' | cut -d'.' -f1,2,3)
        if [ "$apache_ip" == "$ip" ]; then
            echo -e "\033[K${TAB}${SUCCESS} Found IP in Apache Logs: $apache_ip"
            # echo -e "\033[K${TAB}${SUCCESS} Found IP in Apache Logs: ⡽⡾⡿⢀⢁⢂⢃⢄⢅⢆⢇⢈⢉⢊⢋⢌⢍⢎⢏⢐⢑⢒⢓⢔⢕⢖⢗⢘"
            found="$apache_ip"
            details=$(cat apache_logs.log | grep $found)
            echo -e "\033[K${TAB}${TAB}${LOG} Details: $details"
            # echo -e "\033[K${TAB}${TAB}${LOG} Details: ⣗⣘⣙⣚⣛⣜⣝⣞⣟⣠⣡⣢⣣⣤⣥⣦"
        fi
    fi
    progress=$((progress + 1))
    percentage=$(echo "scale=2; $progress * 100.00 / $total" | bc)
    drawProgressBar "$percentage"
done <<< "$ip_ranges"
# while read -r apache_ip; do
#     while read -r ip; do
#         if [ "$apache_ip" == "$ip" ]; then
#             echo -e "\033[K${TAB}${SUCCESS} Found IP in Apache Logs: $apache_ip"
#             found="$apache_ip"
#         fi
#     done <<< "$ip_ranges"
#     progress=$((progress + 1))
#     percentage=$(echo "scale=2; $progress * 100.00 / $total" | bc)
#     drawProgressBar "$percentage"
# done <<< "$apache_records"
tput cnorm
# - Check Failure
if [ -z "$found" ]; then
    echo -e "${TAB}${FAILED} No IP Ranges Found in Apache Logs"
else
    echo -e "\033[K"
fi
