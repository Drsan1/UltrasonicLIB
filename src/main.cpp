#include "Ultrasonic.hpp"
#include <iostream>

using namespace std::chrono_literals;

std::vector<UltrasonicGroup> sensors;

UltrasonicGroup& usGroup = sensors.emplace_back(
    std::initializer_list<std::tuple<gpio_num_t, gpio_num_t>> {
        { GPIO_NUM_4, GPIO_NUM_2 }, { GPIO_NUM_14, GPIO_NUM_12 } });

void setup() { usGroup.init(); }

void loop()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::chrono::milliseconds timeout(1000);
    std::vector<std::optional<double>> syncResult = usGroup.measureSync(timeout);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    for (const auto& distance : syncResult) {
        if (distance.has_value()) {
            std::cout << distance.value() << "mm ";
        } else {
            std::cout << "Timeout ";
        }
    }
    std::cout << std::endl;
    std::cout << "Time = "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin)
                     .count()
              << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}