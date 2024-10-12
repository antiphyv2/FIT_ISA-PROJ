#ifndef MAIN_HPP
#define MAIN_HPP

#ifdef DEBUG_MODE
#define DEBUG_PRINT(x) std::cout << x;
#else
#define DEBUG_PRINT(x) do {} while(false);
#endif

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


extern std::atomic<bool> snifferFlag;

void gracefulExit(int signal);

#endif