#include <functional>
#include <iostream>
#include <map>
#include <print>

namespace Part1 {
int solve() {
    for (std::string line{}; std::getline(std::cin, line);) {
    }
    return -1;
}
}  // namespace Part1

namespace Part2 {
int solve() {
    for (std::string line{}; std::getline(std::cin, line);) {
    }
    return -1;
}
}  // namespace Part2

int main(int argc, const char** argv) {
    if (argc == 1) {
        return 1;
    }
    const auto parts{std::map<std::string, std::function<int()>>{
        {"1", Part1::solve},  //
        {"2", Part2::solve}
    }};
    auto part{argv[1]};
    std::printf("part%s: %d\n", part, parts.at(part)());
    return 0;
}
