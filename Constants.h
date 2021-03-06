#ifndef P2P_REGISTRATION_CONSTANTS_H
#define P2P_REGISTRATION_CONSTANTS_H

#include <string>
#include <vector>

#include <arpa/inet.h>

static const uint16_t ENROLL_INIT = 680;
static const uint16_t ENROLL_REGISTER = 681;
static const uint16_t ENROLL_SUCCESS = 682;
static const uint16_t ENROLL_FAILURE = 683;

static int PORT = 34151;
static const char* ADDR = "fulcrum.net.in.tum.de";

static const std::string INFO = "ga53xis@mytum.de\r\nMilan\r\nStefanovic";
static const auto INFO_C = INFO.c_str();

static const uint16_t PROJECT = htons(4963); //DHT
static const uint16_t TEAM_RANDOM = htons(65535);

static const uint8_t THREADS_NUM = 8;
static const uint64_t START_VALUE = 70000000;

static const uint8_t SECONDS_TO_WAIT = 40;

#endif //P2P_REGISTRATION_CONSTANTS_H