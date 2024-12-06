#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <print>
#include <set>
#include <span>
#include <unordered_set>

using Grid = std::vector<std::string>;

auto find_start(Grid& grid) -> std::tuple<int, int> {
    auto height{grid.size()};
    auto width{grid[0].size()};
    for (auto y{0UL}; y < height; y++) {
        for (auto x{0UL}; x < width; x++) {
            if (grid[y][x] == '^') {
                return {x, y};
            }
        }
    }
    assert(false && "start not found");
}

namespace Part1 {
auto solve() -> size_t {
    std::vector<std::string> grid{std::istream_iterator<std::string>(std::cin), {}};

    auto height{static_cast<int>(grid.size())};
    auto width{static_cast<int>(grid[0].size())};

    auto [x, y]{find_start(grid)};
    auto direction{std::pair{0, 1}};  // UP

    std::set<std::pair<int, int>> visited{};

    while (x > 0 && x < width && y > 0 && y < height) {
        visited.insert({x, y});

        auto [dx, dy]{direction};
        auto new_x{x + dx};
        auto new_y{y - dy};

        if (grid[new_y][new_x] == '#') {
            direction = {dy, -dx};
            continue;
        }

        x = new_x;
        y = new_y;
    }

    return visited.size();
}
}  // namespace Part1

namespace Part2 {
using Direction = std::pair<int, int>;
using Position = std::tuple<int, int, Direction>;

auto is_loop(Grid& grid) -> bool {
    auto height{static_cast<int>(grid.size())};
    auto width{static_cast<int>(grid[0].size())};

    auto [x, y]{find_start(grid)};
    auto direction{Direction{0, 1}};  // UP

    std::set<Position> visited{};

    while (x > 0 && x < width && y > 0 && y < height) {
        auto [dx, dy]{direction};
        auto new_x{x + dx};
        auto new_y{y - dy};

        if (grid[new_y][new_x] == '#') {
            direction = {dy, -dx};
            continue;
        }

        Position curr_pos{x, y, direction};
        if (visited.contains(curr_pos)) {
            return true;
        }
        visited.insert(curr_pos);

        x = new_x;
        y = new_y;
    }

    return false;
}

auto solve() -> int {
    Grid grid{std::istream_iterator<std::string>(std::cin), {}};

    auto height{static_cast<int>(grid.size())};
    auto width{static_cast<int>(grid[0].size())};

    auto loops{0};

    for (int y{0}; y < height; y++) {
        for (int x{0}; x < width; x++) {
            if (grid[y][x] == '^' || grid[y][x] == '#') {
                continue;
            }

            auto new_grid = grid;
            new_grid[y][x] = '#';

            loops += is_loop(new_grid);
        }
    }

    return loops;
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
