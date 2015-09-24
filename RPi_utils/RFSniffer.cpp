/*
 * RF_Sniffer
 * Hacked from http://code.google.com/p/rc-switch/
 * by @justy to provide a handy RF code sniffer
 */

#include "RCSwitch.h"
#include <cstdlib>
#include <cstdio>

int
main(int argc, char *argv[]) {
    // This pin is not the first pin on the RPi GPIO header!
    // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
    // for more information.
    int PIN = 2;

    if (wiringPiSetup() == -1) {
        return 0;
    }

    RCSwitch mySwitch = RCSwitch();
    mySwitch.enableReceive(PIN);  // Receiver on inerrupt 0 => that is pin #2

    while (1) {
        if (mySwitch.available()) {
            int value = mySwitch.getReceivedValue();
            if (value == 0) {
                std::printf("Unknown encoding\n");
            } else {
                std::printf("Received %i\n", mySwitch.getReceivedValue() );
            }
            mySwitch.resetAvailable();
        }
    }

    return (EXIT_SUCCESS);
}

