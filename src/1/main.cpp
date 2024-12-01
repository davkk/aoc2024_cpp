#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>
#include <print>
#include <ranges>
#include <string>
#include <vector>

namespace Part1 {
int solve() {
    std::vector<int> list1{};
    std::vector<int> list2{};

    for (std::string line{}; std::getline(std::cin, line);) {
        const auto split{line.find("   ")};
        list1.push_back(std::stoi(line.substr(0, split)));
        list2.push_back(std::stoi(line.substr(split + 2, line.size())));
    }

    std::ranges::sort(list1);
    std::ranges::sort(list2);

    int total_d{std::ranges::fold_left(
        std::ranges::views::zip(list1, list2),
        0,  //
        [](auto acc, const auto& curr) {
            const auto& [x1, x2]{curr};
            return acc + std::abs(x1 - x2);
        }
    )};

    return total_d;
}
}  // namespace Part1

namespace Part2 {
int solve() {
    std::vector<int> list1{};
    std::vector<int> list2{};

    for (std::string line{}; std::getline(std::cin, line);) {
        const auto split{line.find("   ")};
        list1.push_back(std::stoi(line.substr(0, split)));
        list2.push_back(std::stoi(line.substr(split + 2, line.size())));
    }

    auto total_d{std::ranges::fold_left(
        list1,
        0,  //
        [&list2](auto acc, const auto& x1) {
            return acc + (x1 * std::ranges::count(list2, x1));
        }
    )};

    return static_cast<int>(total_d);
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
