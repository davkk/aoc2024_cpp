#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <print>
#include <span>

auto get_letter(std::vector<std::string>& lines, size_t x, size_t y) -> char {
    if (x < 0 || x > lines.size() || y < 0 || y > lines.size()) {
        return 0;
    }
    return lines[y][x];
}

namespace Part1 {
int solve() {
    std::vector<std::string> lines{std::istream_iterator<std::string>(std::cin), {}};

    static constexpr std::array<std::pair<size_t, size_t>, 8> directions = {{
        {0, -1},
        {0, 1},
        {-1, 0},
        {1, 0},
        {-1, -1},
        {1, -1},
        {-1, 1},
        {1, 1}  //
    }};

    auto count{0};
    for (auto y{0UL}; y < lines.size(); y++) {
        for (auto x{0UL}; x < lines[0].size(); x++) {
            if (get_letter(lines, x, y) == 'X') {
                for (const auto& [dx, dy] : directions) {
                    count += static_cast<int>(
                        std::format(
                            "{}{}{}",
                            get_letter(lines, x + dx, y + dy),
                            get_letter(lines, x + (2 * dx), y + (2 * dy)),
                            get_letter(lines, x + (3 * dx), y + (3 * dy))
                        )
                        == "MAS"
                    );
                }
            }
        }
    }

    return count;
}
}  // namespace Part1

namespace Part2 {
int solve() {
    std::vector<std::string> lines{std::istream_iterator<std::string>(std::cin), {}};

    auto count{0};
    for (auto y{0UL}; y < lines.size(); y++) {
        for (auto x{0UL}; x < lines[0].size(); x++) {
            if (get_letter(lines, x, y) == 'A') {
                auto mas_NE{std::format(
                    "{}{}{}",
                    get_letter(lines, x - 1, y + 1),
                    get_letter(lines, x, y),
                    get_letter(lines, x + 1, y - 1)
                )};
                auto mas_SE{std::format(
                    "{}{}{}",
                    get_letter(lines, x - 1, y - 1),
                    get_letter(lines, x, y),
                    get_letter(lines, x + 1, y + 1)
                )};
                count += static_cast<int>((mas_NE == "MAS" || mas_NE == "SAM") && (mas_SE == "MAS" || mas_SE == "SAM"));
            }
        }
    }

    return count;
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
