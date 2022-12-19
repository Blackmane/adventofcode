/**
 * @file    day19.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    19 Dec 2022
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day19.h"

#include "common.h"

typedef std::array<uint64_t, 8> Blueprint;

constexpr size_t ORE_ORE = 0;
constexpr size_t CLY_ORE = 1;
constexpr size_t OBS_ORE = 2;
constexpr size_t OBS_CLY = 3;
constexpr size_t GEO_ORE = 4;
constexpr size_t GEO_OBS = 5;

constexpr size_t TIME = 0;
constexpr size_t R_ORE = 1;
constexpr size_t R_CLY = 2;
constexpr size_t R_OBS = 3;
constexpr size_t R_GEO = 4;
constexpr size_t T_ORE = 5;
constexpr size_t T_CLY = 6;
constexpr size_t T_OBS = 7;
constexpr size_t T_GEO = 8;

struct State {
    std::array<uint64_t, 9> s;
    inline void product()
    {
        s[T_ORE] += s[R_ORE];
        s[T_CLY] += s[R_CLY];
        s[T_OBS] += s[R_OBS];
        s[T_GEO] += s[R_GEO];
    }

    bool canBuildGEO(const Blueprint &blueprint)
    {
        return s[T_ORE] >= blueprint[GEO_ORE] && s[T_OBS] >= blueprint[GEO_OBS];
    }
    bool canBuildOBS(const Blueprint &blueprint)
    {
        return s[T_ORE] >= blueprint[OBS_ORE] && s[T_CLY] >= blueprint[OBS_CLY];
    }
    bool canBuildCLY(const Blueprint &blueprint)
    {
        return s[T_ORE] >= blueprint[CLY_ORE];
    }
    bool canBuildORE(const Blueprint &blueprint)
    {
        return s[T_ORE] >= blueprint[ORE_ORE];
    }
    void buildGEO(const Blueprint &blueprint)
    {
        s[R_GEO]++;
        s[T_ORE] -= blueprint[GEO_ORE];
        s[T_OBS] -= blueprint[GEO_OBS];
    }
    void buildOBS(const Blueprint &blueprint)
    {
        s[R_OBS]++;
        s[T_ORE] -= blueprint[OBS_ORE];
        s[T_CLY] -= blueprint[OBS_CLY];
    }
    void buildCLY(const Blueprint &blueprint)
    {
        s[R_CLY]++;
        s[T_ORE] -= blueprint[CLY_ORE];
    }
    void buildORE(const Blueprint &blueprint)
    {
        s[R_ORE]++;
        s[T_ORE] -= blueprint[ORE_ORE];
    }
};

void parser(std::vector<Blueprint> *blueprints, std::string line)
{
    Blueprint blueprint;
    std::string numbers;
    for (auto c : line) {
        if (c >= '0' && c <= '9') {
            numbers.push_back(c);
        } else {
            if (numbers.back() != ' ') {
                numbers.push_back(' ');
            }
        }
    }
    auto values = parse::getIntegers(numbers);
    blueprint[ORE_ORE] = values[1];
    blueprint[CLY_ORE] = values[2];
    blueprint[OBS_ORE] = values[3];
    blueprint[OBS_CLY] = values[4];
    blueprint[GEO_ORE] = values[5];
    blueprint[GEO_OBS] = values[6];
    blueprints->push_back(blueprint);
}

#define BUILD(TYPE)                      \
    nextState = state;                   \
    nextState.product();                 \
    if (nextState.s[T_GEO] > maxGeode) { \
        maxGeode = nextState.s[T_GEO];   \
    }                                    \
    if (nextState.s[TIME] < max_time) {  \
        TYPE(blueprint);                 \
        states.push_back(nextState);     \
    }

uint64_t getGeodes(const Blueprint &blueprint, const uint64_t max_time)
{
    uint64_t maxGeode = 0;
    State initialState;
    initialState.s = { 0, 1, 0, 0, 0, 0, 0, 0, 0 };

    uint64_t MAX_R_ORE =
        std::max(std::max(blueprint[GEO_ORE], blueprint[OBS_ORE]), std::max(blueprint[CLY_ORE], blueprint[ORE_ORE]));
    uint64_t MAX_R_CLY = blueprint[OBS_CLY];
    uint64_t MAX_R_OBS = blueprint[GEO_OBS];

    State nextState;
    std::vector<State> states;
    states.reserve(max_time);
    states.push_back(initialState);
    while (!states.empty()) {
        State state = states.back();
        states.pop_back();
        state.s[TIME]++;
        // What to build
        if (state.canBuildGEO(blueprint)) {
            BUILD(nextState.buildGEO);
        } else {
            int done = 0;
            // Take a decision
            if (state.s[R_OBS] < MAX_R_OBS && state.canBuildOBS(blueprint)) {
                BUILD(nextState.buildOBS);
                done++;
            }
            if (state.s[R_CLY] < MAX_R_CLY && state.canBuildCLY(blueprint)) {
                BUILD(nextState.buildCLY);
                done++;
            }
            if (state.s[R_ORE] < MAX_R_ORE && state.canBuildORE(blueprint)) {
                BUILD(nextState.buildORE);
                done++;
            }
            // Wait
            nextState = state;
            nextState.product();
            // Update max
            if (nextState.s[T_GEO] > maxGeode) {
                maxGeode = nextState.s[T_GEO];
            }
            // No need to wait if I already can build all kind of robot
            if (done < 3 && nextState.s[R_ORE] < MAX_R_ORE && nextState.s[TIME] < max_time) {
                states.push_back(nextState);
            }
        }
    }

    return maxGeode;
}

uint64_t getMaximisedGeode(const std::vector<Blueprint> &blueprints)
{
    uint64_t count = 0;
    uint64_t step = 1;
    for (auto &&blueprint : blueprints) {
        count += getGeodes(blueprint, 24) * step;
        step++;
        println(count);
    }
    return count;
}

uint64_t getMultipliedGeode(const std::vector<Blueprint> &blueprints)
{
    uint64_t count = 1;
    for (size_t i = 0; i < 3; ++i) {
        count *= getGeodes(blueprints[i], 32);
        println(count);
    }
    return count;
}

std::string day19::process1(std::string file)
{
    std::vector<Blueprint> blueprints;
    parse::read<std::vector<Blueprint> *>(file, '\n', &parser, &blueprints);
    auto result = getMaximisedGeode(blueprints);
    return std::to_string(result);
}

std::string day19::process2(std::string file)
{
    std::vector<Blueprint> blueprints;
    parse::read<std::vector<Blueprint> *>(file, '\n', &parser, &blueprints);
    auto result = getMultipliedGeode(blueprints);
    return std::to_string(result);
}