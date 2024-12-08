#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <print>
#include <set>
#include <span>
#include <utility>

using Antinode = std::pair<int, int>;

namespace Part1 {
auto solve() -> int {
    std::vector<std::string> grid{std::istream_iterator<std::string>(std::cin), {}};

    auto height{static_cast<int>(grid.size())};
    auto width{static_cast<int>(grid[0].size())};

    auto is_inside = [&width, &height](Antinode& anode) {
        auto& [x, y]{anode};
        return x >= 0 && x < width && y >= 0 && y < height;
    };

    std::set<Antinode> antinodes{};

    for (auto y{0}; y < height; y++) {
        for (auto x{0}; x < width; x++) {
            auto curr{grid[y][x]};

            if (curr == '.') {
                continue;
            }

            for (auto sy{0}; sy < height; sy++) {
                for (auto sx{x + 1}; sx < width; sx++) {
                    if (curr != grid[sy][sx] || x == sx || y == sy) {
                        continue;
                    }

                    auto dx{sx - x};
                    auto dy{sy - y};

                    Antinode anode_close{x - dx, y - dy};
                    if (is_inside(anode_close)) {
                        antinodes.insert(anode_close);
                    }

                    Antinode anode_far{x + (2 * dx), y + (2 * dy)};
                    if (is_inside(anode_far)) {
                        antinodes.insert(anode_far);
                    }
                }
            }
        }
    }

    return antinodes.size();
}
}  // namespace Part1

namespace Part2 {
auto solve() -> int {
    std::vector<std::string> grid{std::istream_iterator<std::string>(std::cin), {}};

    auto height{static_cast<int>(grid.size())};
    auto width{static_cast<int>(grid[0].size())};

    auto is_inside = [&width, &height](Antinode& anode) {
        auto& [x, y]{anode};
        return x >= 0 && x < width && y >= 0 && y < height;
    };

    std::set<Antinode> antinodes{};

    for (auto y{0}; y < height; y++) {
        for (auto x{0}; x < width; x++) {
            auto curr{grid[y][x]};

            if (curr == '.') {
                continue;
            }

            for (auto sy{0}; sy < height; sy++) {
                for (auto sx{x + 1}; sx < width; sx++) {
                    if (curr != grid[sy][sx] || x == sx || y == sy) {
                        continue;
                    }

                    auto dx0{sx - x};
                    auto dy0{sy - y};

                    antinodes.insert({x, y});
                    antinodes.insert({x + dx0, y + dy0});

                    auto dx{dx0};
                    auto dy{dy0};
                    while (true) {
                        Antinode anode_close{x - dx, y - dy};
                        if (is_inside(anode_close)) {
                            antinodes.insert(anode_close);
                            dx += dx0;
                            dy += dy0;
                        } else {
                            break;
                        }
                    }

                    dx = 2 * dx0;
                    dy = 2 * dy0;
                    while (true) {
                        Antinode anode_far{x + dx, y + dy};
                        if (is_inside(anode_far)) {
                            antinodes.insert(anode_far);
                            dx += dx0;
                            dy += dy0;
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }

    return antinodes.size();
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
