#include "Ultrasonic.hpp"
#include <iostream>

using namespace std::chrono_literals;

Ultrasonic sensor(GPIO_NUM_4, GPIO_NUM_2); // Put correct GPIO pin numbers trig, echo

void setup() {
    sensor.init(); 
}

void loop() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    sensor.measureSync();

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Distance: " << sensor.measureSync().value_or(0) << std::endl;
    std::cout << "Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;

    std::cout << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
} 