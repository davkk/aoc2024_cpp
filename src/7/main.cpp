#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <print>
#include <ranges>
#include <span>

namespace rv = std::ranges::views;

auto parse_line(const std::string& line) -> std::pair<size_t, std::vector<size_t>> {
    auto sep{line.find(':')};

    auto result{std::stoul(line.substr(0, sep))};
    auto numbers{
        line.substr(sep + 2)  //
        | rv::split(' ')      //
        | rv::transform([](const auto& ch) {
              return std::stoul(std::string(ch.begin(), ch.end()));
          })
        | std::ranges::to<std::vector>()
    };

    return {result, numbers};
}

namespace Part1 {
auto solve() -> size_t {
    auto answer{0UL};

    for (std::string line{}; std::getline(std::cin, line);) {
        const auto&& [result, numbers]{parse_line(line)};

        size_t n_bits{numbers.size() - 1};
        size_t combinations{1UL << n_bits};

        for (size_t i{0}; i < combinations; ++i) {
            auto acc{numbers[0]};

            for (size_t j{0}; j < n_bits; ++j) {
                auto op{i & (1UL << j)};
                if (op == 0) {
                    acc *= numbers[j + 1];
                } else {
                    acc += numbers[j + 1];
                }
            }

            if (acc == result) {
                answer += result;
                break;
            }
        }
    }

    return answer;
}
}  // namespace Part1

namespace Part2 {
auto solve() -> size_t {
    auto answer{0UL};

    for (std::string line{}; std::getline(std::cin, line);) {
        const auto&& [result, numbers]{parse_line(line)};

        auto n_bits{numbers.size() - 1};
        auto combinations{static_cast<size_t>(std::pow(3, n_bits))};

        for (auto i{0UL}; i < combinations; i++) {
            auto acc{numbers[0]};
            auto num{i};

            for (size_t j{0}; j < n_bits; j++) {
                auto op{num % 3};
                num /= 3;

                switch (op) {
                case 0:
                    acc = std::stoul(std::to_string(acc) + std::to_string(numbers[j + 1]));
                    break;
                case 1:
                    acc += numbers[j + 1];
                    break;
                case 2:
                    acc *= numbers[j + 1];
                    break;
                default:
                    assert(false);
                }
            }

            if (acc == result) {
                answer += result;
                break;
            }
        }
    }

    return answer;
}
}  // namespace Part2

auto main(int argc, const char** argv) -> int {
    auto args{std::span(argv, static_cast<size_t>(argc))};
    std::map<std::string, std::function<size_t()>> parts{
        {"1", Part1::solve},  //
        {"2", Part2::solve}
    };
    const auto* part{args[1]};
    std::println("part{}: {}", part, parts.at(part)());
    return 0;
}
