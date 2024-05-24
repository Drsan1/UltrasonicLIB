#include "Ultrasonic.hpp"
#include <iostream>

using namespace std::chrono_literals;

std::vector<UltrasonicGroup> sensors;

UltrasonicGroup& usGroup = sensors.emplace_back(
    std::initializer_list<std::tuple<gpio_num_t, gpio_num_t>> {
         { GPIO_NUM_4, GPIO_NUM_2 }, { GPIO_NUM_12, GPIO_NUM_13 }, { GPIO_NUM_27, GPIO_NUM_14 }, { GPIO_NUM_26, GPIO_NUM_25 }, { GPIO_NUM_33, GPIO_NUM_32 }, { GPIO_NUM_18, GPIO_NUM_5 }, {GPIO_NUM_21, GPIO_NUM_19},{GPIO_NUM_22, GPIO_NUM_23}});

void setup() {
    usGroup.init(); 
}

void loop() {
    auto results = usGroup.measureSync(std::chrono::milliseconds(1000));
    for(size_t i = 0; i < results.size(); i++){
        std::cout << "Sensor " << i << ": ";
        if(results[i].has_value()) {
            std::cout << results[i].value() << "mm ";
        } else {
            std::cout << results[i].value();
        }
    }
    std::cout << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}