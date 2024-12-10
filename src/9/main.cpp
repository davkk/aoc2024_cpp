#include <__algorithm/fold.h>
#include <functional>
#include <iostream>
#include <map>
#include <print>
#include <ranges>
#include <span>

auto parse_input() -> std::vector<int> {
    std::string input{};
    std::getline(std::cin, input);

    return input  //
         | std::views::transform([](char ch) {
               return ch - '0';
           })
         | std::ranges::to<std::vector<int>>();
}

namespace Part1 {
auto solve() -> size_t {
    auto numbers{parse_input()};

    auto p{0UL};
    auto q{numbers.size() - 1UL};

    std::queue<int> files{};

    while (p < q + 1) {
        if (p % 2 == 0) {
            for (auto i{0}; i < numbers[p]; i++) {
                files.push(static_cast<int>(p / 2));
            }
            p++;
        } else if (q % 2 == 0) {
            while (numbers[p] > 0 && numbers[q] > 0) {
                files.push(static_cast<int>(q / 2));
                numbers[p]--;
                numbers[q]--;
            }
            if (numbers[q] == 0) {
                q--;
            }
            if (numbers[p] == 0) {
                p++;
            }
        } else {
            q--;
        }
    }

    auto checksum{0UL};
    auto idx{0UL};

    while (!files.empty()) {
        auto file{files.front()};
        checksum += idx++ * static_cast<size_t>(file);
        files.pop();
    }

    return checksum;
}
}  // namespace Part1

namespace Part2 {
using Memory = std::vector<std::vector<int>>;

auto solve() -> size_t {
    auto numbers{parse_input()};

    auto mem_slots{
        std::ranges::views::iota(0)                 //
        | std::ranges::views::take(numbers.size())  //
        | std::ranges::views::filter([](int i) {
              return i % 2 == 0;
          })
    };

    auto free_slots{
        std::ranges::views::iota(0)                 //
        | std::ranges::views::take(numbers.size())  //
        | std::ranges::views::filter([](int i) {
              return i % 2 != 0;
          })
    };

    auto has_space_left = [&](size_t idx) {
        for (const auto& slot : free_slots) {
            if (slot > idx) {
                return -1;
            }

            auto desired_size{numbers[idx]};
            auto space_left{numbers[slot]};

            if (space_left >= desired_size) {
                return slot;
            }
        }
        return -1;
    };

    Memory memory(numbers.size());

    for (const auto& slot : mem_slots) {
        for (auto i{0}; i < numbers[slot]; i++) {
            memory[slot].push_back(slot / 2);
        }
    }

    for (const auto& slot : free_slots) {
        for (auto i{0}; i < numbers[slot]; i++) {
            memory[slot].push_back(-1);
        }
    }

    auto idx{memory.size() - 1};
    while (idx > 0) {
        auto free{has_space_left(idx)};
        if (free < 0) {
            idx -= 2;
            continue;
        }

        auto last{-1};
        while (memory[free][++last] != -1) {
        }
        for (auto i{0}; i < memory[idx].size(); i++) {
            memory[free][last + i] = memory[idx][i];
            memory[idx][i] = -1;
            numbers[free]--;
        }

        idx -= 2;
    }

    auto id{0UL};
    auto checksum{0UL};
    for (auto slot{0UL}; slot < memory.size(); slot++) {
        for (const auto file : memory[slot]) {
            if (file >= 0) {
                checksum += id * static_cast<size_t>(file);
            }
            id++;
        }
    }

    return checksum;
}

auto gpt_cleanup_solve() -> size_t {
    auto numbers = parse_input();
    size_t num_slots = numbers.size();

    auto even_slots = std::ranges::views::iota(0, static_cast<int>(num_slots))  //
                    | std::ranges::views::filter([](int i) {
                          return i % 2 == 0;
                      });

    auto odd_slots = std::ranges::views::iota(0, static_cast<int>(num_slots))  //
                   | std::ranges::views::filter([](int i) {
                         return i % 2 != 0;
                     });

    auto find_free_slot = [&](size_t idx) -> std::optional<int> {
        for (int slot : odd_slots) {
            if (slot > static_cast<int>(idx)) {
                break;
            }

            if (numbers[slot] >= numbers[idx]) {
                return slot;
            }
        }
        return std::nullopt;
    };

    Memory memory(num_slots);
    for (int slot : even_slots) {
        memory[slot] = std::vector<int>(numbers[slot], slot / 2);
    }
    for (int slot : odd_slots) {
        memory[slot] = std::vector<int>(numbers[slot], -1);
    }

    for (int idx = static_cast<int>(num_slots) - 1; idx >= 0; idx -= 2) {
        auto free_slot = find_free_slot(idx);
        if (!free_slot) {
            continue;
        }

        int free = *free_slot;
        auto& dest = memory[free];
        auto& src = memory[idx];

        auto insert_pos = std::ranges::find(dest, -1);
        for (int file : src) {
            if (file == -1) {
                break;
            }
            *insert_pos = file;
            insert_pos++;
        }

        src.assign(src.size(), -1);
        numbers[free] -= static_cast<int>(src.size());
    }

    size_t checksum = 0;
    size_t id = 0;
    for (const auto& slot : memory) {
        for (int file : slot) {
            if (file >= 0) {
                checksum += id * static_cast<size_t>(file);
            }
            id++;
        }
    }

    return checksum;
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
