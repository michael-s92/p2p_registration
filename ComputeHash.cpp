#include "ComputeHash.h"
#include "Constants.h"

#include <openssl/sha.h>
#include <iostream>

uint64_t findNonce(uint64_t challenge) {

    uint64_t nonce = 0;
    bool check;

    do {
        nonce++;

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);

        SHA256_Update(&sha256, &challenge, sizeof(uint64_t));
        SHA256_Update(&sha256, &TEAM_RANDOM, sizeof(uint16_t));
        SHA256_Update(&sha256, &PROJECT, sizeof(uint16_t));
        SHA256_Update(&sha256, &nonce, sizeof(uint64_t));
        SHA256_Update(&sha256, &VECTOR_INFO, VECTOR_INFO.size());

        SHA256_Final(hash, &sha256);

        check = hash[0] == 0 && hash[1] == 0 && hash[2] == 0 && hash[3] == 0;
    } while (!check);

    return nonce;
}