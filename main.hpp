#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <thread>
#include <future>
#include <stdexcept>
#include <atomic> 

#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <netinet/ether.h>
#include <netinet/ip6.h>
#include <netinet/ip_icmp.h>
#include <netinet/icmp6.h>
#include <csignal>

//Atomic flag to be able to close the sniffer
extern std::atomic<bool> snifferFlag;


/**
 * @brief Function called upon pressing CTRL+C which closes the sniffer
 * 
 * @param signal signal number
 */
void gracefulExit(int signal);

#endif