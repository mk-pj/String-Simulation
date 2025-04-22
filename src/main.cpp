#include <filesystem>
#include "func.h"

int main() {
    std::filesystem::create_directories("../data");
    auto pos_file = "../data/pos1.csv";
    auto en_file = "../data/energy1.csv";
    auto dt = 0.2;
    constexpr auto t_max = 2;
    constexpr auto n = 50;
    run(en_file, pos_file, dt, t_max, n);

    pos_file = "../data/pos2.csv";
    en_file = "../data/energy2.csv";
    dt = 0.001;
    run(en_file, pos_file, dt, t_max, n);
    return 0;
}