#include "ComputeHash.h"
#include "Constants.h"

#include <openssl/sha.h>
#include <iostream>

#include <thread>
#include <mutex>
#include <functional>
#include <vector>


std::mutex lock;

void calculateHash(uint64_t challenge, uint8_t id, uint64_t& nonce, bool& found){

    std::cout << "Thread " << (int)id << " started\n";

    uint64_t tmp_nonce = id - THREADS_NUM;
    bool check;

    do {
        tmp_nonce += THREADS_NUM;

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);

        SHA256_Update(&sha256, &challenge, sizeof(uint64_t));
        SHA256_Update(&sha256, &TEAM_RANDOM, sizeof(uint16_t));
        SHA256_Update(&sha256, &PROJECT, sizeof(uint16_t));
        SHA256_Update(&sha256, &tmp_nonce, sizeof(uint64_t));
        SHA256_Update(&sha256, &VECTOR_INFO, VECTOR_INFO.size());

        SHA256_Final(hash, &sha256);

        check = hash[0] == 0 && hash[1] == 0 && hash[2] == 0 && hash[3] == 0;
    } while (!check && !found);

    if(check){
        std::lock_guard<std::mutex> guard(lock);
        found = true;
        nonce = tmp_nonce;
        std::cout << "Thread " << (int)id << " found hash\n";
    }

}

uint64_t findNonce(uint64_t challenge) {

    uint64_t nonce = 0;
    bool found = false;
    std::vector<std::thread> vec;

    for (int i = 0; i < THREADS_NUM; i++) {
        std::thread t(calculateHash, challenge, i, std::ref(nonce), std::ref(found));
        vec.emplace_back(std::move(t));
    }

    for (auto t = vec.begin(); t < vec.end(); t++) //vector<thread>::iterator
        t->join();

    return nonce;
}