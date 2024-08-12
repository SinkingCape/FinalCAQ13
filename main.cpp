#include "mbed.h"

// Define the LED and serial objects
DigitalOut myled(LED1);
BufferedSerial pc(USBTX, USBRX, 9600); // Corrected to BufferedSerial
BufferedSerial dev(D1, D0, 115200);    // Corrected to BufferedSerial
// Baud Rates set during intialisation.

// Function to handle reception from the device serial
void dev_recv() {
    while (dev.readable()) {
        char c;
        dev.read(&c, 1);
        pc.write(&c, 1);
    }    
}

// Function to handle reception from the PC serial
void pc_recv() {
    while (pc.readable()) {
        char c;
        pc.read(&c, 1);
        dev.write(&c, 1);
    }    
}

int main() {
    // Attach callback functions with interrupt mode
    pc.sigio(pc_recv); // Attach function for USB serial
    dev.sigio(dev_recv); // Attach function for hardware serial

    pc.write("Hello!! \r\n", 11);

    while (1) {
        myled = 1;
        ThisThread::sleep_for(1s); // Updated delay function
        myled = 0;
        ThisThread::sleep_for(1s); // Updated delay function
    }
}
