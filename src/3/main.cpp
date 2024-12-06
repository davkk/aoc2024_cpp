#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <map>
#include <optional>
#include <print>
#include <ranges>

namespace r = std::ranges;

struct Mul {
    std::optional<int> x;
    std::optional<int> y;
};

namespace Part1 {
int solve() {
    std::vector<Mul> ops{};
    std::string token{};

    auto data{r::istream_view<char>(std::cin)};
    for (char ch : data) {
        if (token == "mul(" && (std::isdigit(ch) != 0)) {
            token.clear();
            token += ch;

            Mul mul{};
            for (const auto& d : data) {
                if (std::isdigit(d) != 0) {
                    token += d;
                } else if (d == ',') {
                    mul.x = std::stoi(token);
                    token.clear();
                    continue;
                } else if (mul.x != std::nullopt && d == ')') {
                    mul.y = std::stoi(token);
                    ops.push_back(mul);
                    break;
                } else {
                    break;
                }
            }
        } else {
            token += ch;
            if (token.size() > 4) {
                token.erase(0, 1);
            }
        }
    }

    return r::fold_left(
        ops,  //
        0,
        [](int acc, const auto& op) {
            auto x{*op.x};
            auto y{*op.y};
            return acc + (x * y);
        }
    );
}
}  // namespace Part1

namespace Part2 {
int solve() {
    bool should_count{true};

    std::vector<Mul> ops{};
    std::string token{};

    auto input{r::istream_view<char>(std::cin)};
    for (const auto& ch : input) {
        if (should_count && token.ends_with("mul(") && (std::isdigit(ch) != 0)) {
            token.clear();
            token += ch;

            Mul mul{};
            for (const auto& d : input) {
                if (std::isdigit(d) != 0) {
                    token += d;
                } else if (d == ',' && !token.empty()) {
                    mul.x = std::stoi(token);
                    token.clear();
                } else if (d == ')' && mul.x.has_value()) {
                    mul.y = std::stoi(token);
                    if (mul.y) {
                        ops.push_back(mul);
                    }
                    break;
                } else {
                    break;
                }
            }
        } else {
            token += ch;

            if (token.ends_with("do()")) {
                should_count = true;
            } else if (token.ends_with("don't()")) {
                should_count = false;
            }
        }
    }

    return r::fold_left(
        ops,  //
        0,
        [](int acc, const Mul& op) {
            return acc + (*op.x * *op.y);
        }
    );
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
