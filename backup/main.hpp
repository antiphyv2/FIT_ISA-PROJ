#ifndef MAIN_HPP
#define MAIN_HPP

#ifdef DEBUG_MODE
#define DEBUG_PRINT(x) std::cout << x;
#else
#define DEBUG_PRINT(x) do {} while(false);
#endif

#include <iostream>
#include <memory> 
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <csignal>
#include <queue>
#include <poll.h>
#include <cctype>

#endif