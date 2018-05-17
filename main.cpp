#include <iostream>
#include "ClientSocket.hpp"
#include "Constants.h"
#include "ComputeHash.h"

using namespace std;



int main() {

    bool answer;
    ClientSocket client(ADDR, PORT);

    do {
        client.connectToServer();
        uint64_t ch = client.receiveChallenge();
        cout << "Challenge: " << ch << endl;

        uint64_t nonce = findNonce(ch);
        if(nonce != 0) {
            cout << "Nonce: " << nonce << endl;

            bool sent = client.sendEnrollRegistration(ch, nonce);
            if (sent)
                answer = client.receiveAnswer();
            else
                answer = false;
        } else {
            answer = false;
        }
    } while (!answer);

    return 0;
}