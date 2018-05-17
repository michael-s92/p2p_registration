//
// Created by michael on 5/15/18.
//

#ifndef P2P_REGISTRATION_CONSTANTS_H
#define P2P_REGISTRATION_CONSTANTS_H

#include <string>
#include <vector>

static const uint16_t ENROLL_INIT = 680;
static const uint16_t ENROLL_REGISTER = 681;
static const uint16_t ENROLL_SUCCESS = 682;
static const uint16_t ENROLL_FAILURE = 683;

static int PORT = 34151;
static const char* ADDR = "fulcrum.net.in.tum.de";

//static const char* NAME = "Milan";
//static const char* LASTNAME = "Stefanovic";
//static const char* EMAIL = "ga53xis@mytum.de";
static const std::string INFO = "ga53xis@mytum.de\r\nMilan\r\nStefanovic";
// da li treba kodirati u UTF-8 ???

static const std::vector<uint8_t> VECTOR_INFO(INFO.begin(), INFO.end());

static const uint16_t PROJECT = 4963; //DHT
static const uint16_t TEAM_RANDOM =  65535;

static const uint8_t THREADS_NUM = 6;


#endif //P2P_REGISTRATION_CONSTANTS_H
