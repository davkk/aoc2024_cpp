#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <print>
#include <ranges>
#include <set>
#include <span>
#include <sstream>

using Tree = std::map<std::string, std::set<std::string>>;

auto fill_tree(Tree& tree) -> void {
    for (std::string line{}; std::getline(std::cin, line) && line != "";) {
        std::stringstream edge(line);

        std::string from{};
        std::getline(edge, from, '|');

        std::string to{};
        std::getline(edge, to, '|');

        tree[from].insert(to);
    }
}

namespace Part1 {
auto solve() -> int {
    Tree tree{};
    fill_tree(tree);

    auto answer{0};
    for (std::string line{}; std::getline(std::cin, line);) {
        auto updates{line | std::views::split(',') | std::ranges::to<std::vector<std::string>>()};
        auto is_ok{true};
        for (size_t i{0}; i < updates.size(); i++) {
            for (size_t j{i + 1}; j < updates.size(); j++) {
                if (!tree[updates[i]].contains(updates[j])) {
                    is_ok = false;
                }
            }
        }

        if (is_ok) {
            answer += std::stoi(updates[updates.size() / 2]);
        }
    }

    return answer;
}
}  // namespace Part1

namespace Part2 {
auto solve() -> int {
    Tree tree{};
    fill_tree(tree);

    auto reorder = [&](std::string& a, std::string& b) -> bool {
        return tree[a].contains(b);
    };

    auto answer{0};
    for (std::string line{}; std::getline(std::cin, line);) {
        auto updates{line | std::views::split(',') | std::ranges::to<std::vector<std::string>>()};

        auto is_ok{true};
        for (size_t i{0}; i < updates.size(); i++) {
            for (size_t j{i + 1}; j < updates.size(); j++) {
                if (!tree[updates[i]].contains(updates[j])) {
                    is_ok = false;
                    std::ranges::sort(updates, reorder);
                    break;
                }
            }
        }

        if (!is_ok) {
            answer += std::stoi(updates[updates.size() / 2]);
        }
    }

    return answer;
}
}  // namespace Part2

auto main(int argc, const char** argv) -> int {
    auto args{std::span(argv, static_cast<size_t>(argc))};
    std::map<std::string, std::function<int()>> parts{
        {"1", Part1::solve},  //
        {"2", Part2::solve}
    };
    const auto* part{args[1]};
    std::println("part{}: {}", part, parts.at(part)());
    return 0;
}
