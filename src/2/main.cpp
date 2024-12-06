#include <__algorithm/fold.h>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <print>
#include <ranges>
#include <sstream>
#include <string>

namespace rv = std::ranges::views;
namespace r = std::ranges;

auto is_safe(std::vector<int>& line) -> bool {
    auto zipped{rv::zip(line, line | rv::drop(1))};
    const auto&& [first, second]{zipped.front()};

    auto diff{second - first};
    if (diff == 0 || abs(diff) < 1 || abs(diff) > 3) {
        return false;
    }

    auto trend{std::signbit(diff)};
    for (const auto&& [curr, next] : zipped | rv::drop(1)) {
        diff = next - curr;
        if (diff == 0 || abs(diff) < 1 || abs(diff) > 3 || std::signbit(diff) != trend) {
            return false;
        }
    }

    return true;
}

namespace Part1 {
auto solve() -> int {
    int safe_count{0};

    for (std::string line{}; std::getline(std::cin, line);) {
        // NOTE: can also do `stringstream`
        auto split_line{
            rv::split(line, ' ')  //
            | rv::transform([](const auto& ch) {
                  return std::stoi(std::string(ch.begin(), ch.end()));
              })
            | r::to<std::vector<int>>()
        };

        if (is_safe(split_line)) {
            safe_count++;
        }
    }

    return safe_count;
}
}  // namespace Part1

namespace Part2 {
int solve() {
    int safe_count{0};

    for (std::string line{}; std::getline(std::cin, line);) {
        auto split_line{
            rv::split(line, ' ')  //
            | rv::transform([](const auto& ch) {
                  return std::stoi(std::string(ch.begin(), ch.end()));
              })
            | r::to<std::vector<int>>()
        };

        auto result{is_safe(split_line)};

        if (static_cast<size_t>(result) == split_line.size()) {
            safe_count++;
        } else {
            for (int idx{0}; idx < static_cast<int>(split_line.size()); idx++) {
                std::vector<int> new_line(split_line);
                new_line.erase(new_line.begin() + idx);
                if (is_safe(new_line)) {
                    safe_count++;
                    break;
                }
            }
        }
    }

    return safe_count;
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
