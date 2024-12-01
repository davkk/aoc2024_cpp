#include <functional>
#include <iostream>
#include <map>
#include <print>
#include <span>

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
    auto args{std::span(argv, static_cast<size_t>(argc))};
    std::map<std::string, std::function<int()>> parts{
        {"1", Part1::solve},  //
        {"2", Part2::solve}
    };
    const auto* part{args[1]};
    std::println("part{}: {}", part, parts.at(part)());
    return 0;
}
