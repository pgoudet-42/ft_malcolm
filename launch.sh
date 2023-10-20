#!/bin/zsh

SRC_IP_ADDR="172.20.48.1"
MAC_ADDR_SRC="00:15:5d:0a:88:70"
IP_ADDR_TRGT="172.20.53.236"
MAC_ADDR_TRGT="00:15:5d:21:5a:d3"
gcc  ft_malcolm.c receiv_request.c send_reply.c  utils.c utils_display.c errors.c -o ft_malcolm
# IP_ADDR_HOST=$(ifconfig | grep inet); IP_ADDR_HOST=${IP_ADDR_HOST:13:14}; IP_ADDR_HOST=`echo $IP_ADDR_HOST | sed 's/ *$//g'`; IP_ADDR_HOST=`echo $IP_ADDR_HOST | sed 's/ //g'`; echo "IP_ADDR_HOST = <$IP_ADDR_HOST>"
# MAC_ADDR_HOST=$(ifconfig | grep ether); MAC_ADDR_HOST=${MAC_ADDR_HOST:14:17}; echo "MAC_ADDR_HOST = <$MAC_ADDR_HOST>"
# SERVER_IP_ADDR=$(cat /etc/resolv.conf | grep nameserver); SERVER_IP_ADDR=$(echo ${SERVER_IP_ADDR:11:15} | sed 's/ *$//g'); echo "SERVER_IP_ADDR = <$SERVER_IP_ADDR>"
# ./ft_malcolm $SERVER_IP_ADDR $MAC_ADDR_HOST  "172.23.61.39" "00:15:5d:01:71:c9"
# valgrind --leak-check=full ./ft_malcolm $SRC_IP_ADDR $MAC_ADDR_SRC $IP_ADDR_TRGT $MAC_ADDR_TRGT
./ft_malcolm $SRC_IP_ADDR $MAC_ADDR_SRC $IP_ADDR_TRGT $MAC_ADDR_TRGT

