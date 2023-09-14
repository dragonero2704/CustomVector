#pragma once

#ifndef MACROS
#define MACROS
#include <cstdio>
#define info(msg, ...) printf("[i] " msg "\n", ##__VA_ARGS__)
#define success(msg, ...) printf("[+] " msg "\n", ##__VA_ARGS__)
#define error(msg, ...) printf("[-] " msg "\n", ##__VA_ARGS__)
#endif