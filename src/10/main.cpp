#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <print>
#include <set>
#include <span>

using Point = std::pair<int, int>;

const std::array<std::pair<int, int>, 4> directions{{
    {0, -1},
    {1, 0},
    {0, 1},
    {-1, 0},
}};

namespace Part1 {
auto solve() -> size_t {
    std::vector<std::string> map{std::istream_iterator<std::string>(std::cin), {}};

    auto height{map.size()};
    auto width{map[0].size()};

    auto is_inside{[&](Point& p) {
        auto& [x, y]{p};
        return x >= 0 && x < width && y >= 0 && y < height;
    }};

    std::function<void(Point, std::set<Point>&)> walk{[&](Point curr, std::set<Point>& ends) -> void {
        auto&& [x, y]{curr};

        if (not is_inside(curr)) {
            return;
        }

        if (map[y][x] == '9') {
            ends.insert(curr);
        } else {
            for (const auto& [dx, dy] : directions) {
                Point next{x + dx, y + dy};
                if (is_inside(next) && map[y][x] + 1 == map[next.second][next.first]) {
                    walk(next, ends);
                }
            }
        }
    }};

    auto answer{0UL};
    for (auto y{0UL}; y < height; ++y) {
        for (auto x{0UL}; x < width; ++x) {
            if (map[y][x] == '0') {
                std::set<Point> trail_ends{};
                walk({x, y}, trail_ends);
                answer += trail_ends.size();
            }
        }
    }

    return answer;
}
}  // namespace Part1

namespace Part2 {
auto solve() -> size_t {
    std::vector<std::string> map{std::istream_iterator<std::string>(std::cin), {}};

    auto height{map.size()};
    auto width{map[0].size()};

    auto is_inside{[&](Point& p) {
        auto& [x, y]{p};
        return x >= 0 && x < width && y >= 0 && y < height;
    }};

    std::function<int(Point)> walk{[&](Point curr) -> int {
        auto& [x, y]{curr};

        if (not is_inside(curr)) {
            return 0;
        }

        if (map[y][x] == '9') {
            return 1;
        }

        auto trails{0};

        for (const auto& [dx, dy] : directions) {
            Point next{x + dx, y + dy};
            if (is_inside(next) && map[y][x] + 1 == map[next.second][next.first]) {
                trails += walk(next);
            }
        }

        return trails;
    }};

    auto answer{0UL};
    for (auto y{0UL}; y < height; ++y) {
        for (auto x{0UL}; x < width; ++x) {
            if (map[y][x] == '0') {
                answer += walk({x, y});
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
