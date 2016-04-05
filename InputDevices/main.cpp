/* 
 * File:   main.cpp
 * Author: takeshi
 *
 * Created on April 4, 2016, 7:33 PM
 */

#include <stdint.h>
#include <cstdlib>
#include <iostream>
#include "myCommon.h"
#include "InputDevices.h"
#include <wiringPi.h>

using namespace std;

static void funcKey (InputDevices::INPUT_STATUS *inputStatus);
static void funcRotary (InputDevices::INPUT_STATUS *inputStatus);
static void funcTap (InputDevices::INPUT_STATUS *inputStatus);

int main(int argc, char** argv) {
    InputDevices *p_inputDevices = InputDevices::getInstance();    
    p_inputDevices->registerKeyChangedCallback(funcKey);
    p_inputDevices->registerRotaryEncoderChangedCallback(funcRotary);
    p_inputDevices->registerTappedCallback(funcTap);
    p_inputDevices->start();
    
    // wait until any key input
    char x;
    cin >> x;
    
    // exit threads
    p_inputDevices->stopRendezvous();
    return 0;
}

static void funcKey (InputDevices::INPUT_STATUS *inputStatus){
    cout << "Keys: " << inputStatus->key[0] << ", " << inputStatus->key[1] << endl;
    pinMode( 22, OUTPUT);
    if( inputStatus->key[0] == false ) {
        digitalWrite(22, 0);
    } else {
        digitalWrite(22, 1);
    }    
    
    cout << "ACCEL_X: " << inputStatus->accelX << endl;;
    cout << "ACCEL_Y: " << inputStatus->accelY << endl;;
    cout << "ACCEL_Z: " << inputStatus->accelZ << endl;;
}

static void funcRotary (InputDevices::INPUT_STATUS *inputStatus){
    cout << "Rotate: " << inputStatus->rotaryTickSpeed << endl;
}

static void funcTap (InputDevices::INPUT_STATUS *inputStatus){
    cout << "Tap: " << inputStatus->accelTapNum << endl;
}
