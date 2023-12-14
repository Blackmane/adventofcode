/**
 * @file    day12.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    12 Dec 2023
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day12.h"

#include "common.h"

uint64_t resolveIterative(const std::string &springs, const std::vector<uint> &numbers)
{
    std::vector<uint> partialSum = numbers;
    uint sum = 0;
    for (int i = numbers.size() - 1; i >= 0; --i) {
        sum += numbers[i];
        partialSum[i] = sum;
        sum++; // '.' between two numbers
    }

    const auto n = springs.size();
    const auto m = numbers.size();

    auto remainingSpring = [&](const std::pair<uint, uint> &cur) { return n - cur.first; };
    auto remainingNumbers = [&](const std::pair<uint, uint> &cur) { return m - cur.second; };

    std::map<std::pair<uint, uint>, uint64_t> locMemoization;

    std::function<uint64_t(std::pair<uint, uint> curr)> search;
    search = [&](const std::pair<uint, uint> &curr) -> uint64_t {
        auto it = locMemoization.find(curr);
        if (it != locMemoization.end()) {
            return it->second;
        }

        // springs.empty()
        if (remainingSpring(curr) == 0) {
            // Can't continue
            if (remainingNumbers(curr) == 0) { // numbers.empty()
                return 1;
            }
            return 0;
        }

        // Some char in springs (!springs.empty)
        if (remainingNumbers(curr) == 0) {
            // No more numbers
            for (auto pos = curr.first; pos < n; pos++) {
                if (springs[pos] == '#') {
                    return 0;
                }
            }
            return 1;
        }

        // Some chars, some numbers

        auto pos = curr.first;
        while (pos < n && springs[pos] == '.') {
            pos++;
        }
        if (pos == n || n - pos < partialSum[curr.second]) {
            // No more space
            return 0;
        }

        // Current is '#' o '?'
        uint64_t resSkip = 0;
        if (springs[pos] == '?') {
            // Skip
            std::pair<uint, uint> key = { pos + 1, curr.second };
            resSkip = search(key);
        }

        // Current is '#' o '?', but '?' as '.' already handled
        for (auto cpos = pos; cpos < pos + numbers[curr.second]; cpos++) {
            if (springs[cpos] == '.') {
                // Doesn't fit
                return resSkip + 0;
            }
        }

        // Looks good

        if (pos + numbers[curr.second] == n) {
            // Last number
            return resSkip + 1;
        }
        if (springs[pos + numbers[curr.second]] == '#') {
            // Doesn't fit
            return resSkip + 0;
        }

        std::pair<uint, uint> key = { pos + numbers[curr.second] + 1, curr.second + 1 };
        uint64_t res = search(key);
        locMemoization.insert({ key, res });
        return res + resSkip;
    };
    return search({ 0, 0 });
}

std::string day12::process1(std::string file)
{
    std::vector<std::string> list;
    parse::read_all(file, &list);
    uint64_t count = 0;
    for (auto &&line : list) {
        auto parts = parse::split(line, ' ');
        auto numbers = parse::getGenericIntegers<uint>(op::replaceAll(parts[1], ',', ' '));
        count += resolveIterative(parts[0], numbers);
    }
    return std::to_string(count);
}

std::string repeat(const std::string &list, uint n)
{
    auto result = list;
    size_t size = list.size();
    result.reserve((size + 1) * n);
    for (uint i = 1; i < n; i++) {
        result.push_back('?');
        for (uint j = 0; j < size; j++) {
            result.push_back(list[j]);
        }
    }
    return result;
}

std::vector<uint> repeat(const std::vector<uint> list, uint n)
{
    auto result = list;
    size_t size = list.size();
    result.reserve(size * n);
    for (uint i = 1; i < n; i++) {
        for (uint j = 0; j < size; j++) {
            result.push_back(list[j]);
        }
    }
    return result;
}

std::string day12::process2(std::string file)
{
    std::vector<std::string> list;
    parse::read_all(file, &list);
    uint64_t count = 0;
    for (auto &&line : list) {
        auto parts = parse::split(line, ' ');
        auto numbers = parse::getGenericIntegers<uint>(op::replaceAll(parts[1], ',', ' '));
        count += resolveIterative(repeat(parts[0], 5), repeat(numbers, 5));
    }
    return std::to_string(count);
}

// uint64_t resolve(std::string::iterator begin, std::string::iterator end, uint curr, std::queue<uint> numbers)
// {
//     if (begin == end) {
//         // Can't continue
//         if (numbers.empty()) {
//             return 1;
//         }
//         if (numbers.size() == 1 && curr == numbers.front()) {
//             // End with the current number
//             return 1;
//         }
//         return 0;
//     }
//     // Some char in springs
//     if (numbers.empty()) {
//         // !springs.empty
//         for (auto c = begin; c != end; c++) {
//             if (*c == '#') {
//                 return 0;
//             }
//         }
//         return 1;
//     }
//     if (curr == numbers.front()) {
//         if (*begin == '#') {
//             // After '###' must be a `.` or `?`
//             return 0;
//         }
//         numbers.pop();
//         return resolve(begin + 1, end, 0, std::move(numbers));
//     }
//     // curr != numbers.front()
//     if (curr == 0) {
//         uint64_t count = 0;
//         if (*begin == '#' || *begin == '?') {
//             count += resolve(begin + 1, end, 1, numbers);
//         }
//         if (*begin == '.' || *begin == '?') {
//             count += resolve(begin + 1, end, 0, std::move(numbers));
//         }
//         return count;
//     }
//     // curr != numbers.front() && curr >0
//     if (*begin == '.') {
//         return 0;
//     }
//     return resolve(begin + 1, end, curr + 1, std::move(numbers));
// }

// uint64_t resolve(const std::string &springs, uint curr, std::queue<uint> numbers)
// {
//     auto it = memoization.find({ springs, curr, numbers });
//     if (it != memoization.end()) {
//         return it->second;
//     }

//     if (springs.empty()) {
//         // Can't continue
//         if (numbers.empty()) {
//             return 1;
//         }
//         if (numbers.size() == 1 && curr == numbers.front()) {
//             // End with the current number
//             return 1;
//         }
//         return 0;
//     }
//     // Some char in springs
//     if (numbers.empty()) {
//         // !springs.empty
//         for (auto c : springs) {
//             if (c == '#') {
//                 return 0;
//             }
//         }
//         return 1;
//     }
//     if (curr == numbers.front()) {
//         if (springs[0] == '#') {
//             // After '###' must be a `.` or `?`
//             return 0;
//         }
//         auto oldNumbers = numbers;
//         numbers.pop();
//         auto val = resolve(springs.substr(1, springs.size() - 1), 0, numbers);
//         memoization.insert({ { springs, curr, std::move(oldNumbers) }, val });
//         return val;
//     }
//     // curr != numbers.front()
//     if (curr == 0) {
//         uint64_t count = 0;
//         if (springs[0] == '#' || springs[0] == '?') {
//             count += resolve(springs.substr(1, springs.size() - 1), 1, numbers);
//         }
//         if (springs[0] == '.' || springs[0] == '?') {
//             count += resolve(springs.substr(1, springs.size() - 1), 0, numbers);
//         }
//         memoization.insert({ { springs, curr, numbers }, count });
//         return count;
//     }
//     // curr != numbers.front() && curr >0
//     if (springs[0] == '.') {
//         return 0;
//     }

//     auto val = resolve(springs.substr(1, springs.size() - 1), curr + 1, numbers);
//     memoization.insert({ { springs, curr, numbers }, val });
//     return val;
// }