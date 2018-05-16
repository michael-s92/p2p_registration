#include <iostream>
#include "ClientSocket.hpp"
#include "Constants.h"
#include "ComputeHash.h"

using namespace std;



int main() {

    bool answer;
    do {
        ClientSocket client(ADDR, PORT);
        uint64_t ch = client.receiveChallenge();
        cout << "Challenge: " << ch << endl;

        uint64_t nonce = findNonce(ch);
        cout << "Nonce: " << nonce << endl;

        bool sent = client.sendEnrollRegistration(ch, nonce);
        if(sent)
            answer = client.receiveAnswer();
        else
            answer = false;

    } while (!answer);

    return 0;
}