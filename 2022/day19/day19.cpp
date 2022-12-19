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

#include <unordered_set>

typedef std::array<uint16_t, 8> Blueprint;

constexpr size_t ORE_ORE = 0;
constexpr size_t CLY_ORE = 1;
constexpr size_t OBS_ORE = 2;
constexpr size_t OBS_CLY = 3;
constexpr size_t GEO_ORE = 4;
constexpr size_t GEO_OBS = 5;

struct State {
    uint16_t TIME = 0;
    uint16_t R_ORE = 1;
    uint16_t R_CLY = 0;
    uint16_t R_OBS = 0;
    uint16_t R_GEO = 0;
    uint16_t T_ORE = 0;
    uint16_t T_CLY = 0;
    uint16_t T_OBS = 0;
    uint16_t T_GEO = 0;

    bool operator<(const State &b) const
    {
        return TIME < b.TIME && R_ORE < b.R_ORE && R_CLY < b.R_CLY && R_OBS < b.R_OBS && R_GEO < b.R_GEO &&
               T_ORE < b.T_ORE && T_CLY < b.T_CLY && T_OBS < b.T_OBS && T_GEO < b.T_GEO;

        return TIME < b.TIME;
    }

    bool operator==(const State &b) const
    {
        return TIME == b.TIME && R_ORE == b.R_ORE && R_CLY == b.R_CLY && R_OBS == b.R_OBS && R_GEO == b.R_GEO &&
               T_ORE == b.T_ORE && T_CLY == b.T_CLY && T_OBS == b.T_OBS && T_GEO == b.T_GEO;
    }

    inline void product()
    {
        T_ORE += R_ORE;
        T_CLY += R_CLY;
        T_OBS += R_OBS;
        T_GEO += R_GEO;
    }

    inline bool canBuildGEO(const Blueprint &blueprint) const
    {
        return T_ORE >= blueprint[GEO_ORE] && T_OBS >= blueprint[GEO_OBS];
    }
    inline bool canBuildOBS(const Blueprint &blueprint) const
    {
        return T_ORE >= blueprint[OBS_ORE] && T_CLY >= blueprint[OBS_CLY];
    }
    inline bool canBuildCLY(const Blueprint &blueprint) const
    {
        return T_ORE >= blueprint[CLY_ORE];
    }
    inline bool canBuildORE(const Blueprint &blueprint) const
    {
        return T_ORE >= blueprint[ORE_ORE];
    }
    inline void buildGEO(const Blueprint &blueprint)
    {
        R_GEO++;
        T_ORE -= blueprint[GEO_ORE];
        T_OBS -= blueprint[GEO_OBS];
    }
    inline void buildOBS(const Blueprint &blueprint)
    {
        R_OBS++;
        T_ORE -= blueprint[OBS_ORE];
        T_CLY -= blueprint[OBS_CLY];
    }
    inline void buildCLY(const Blueprint &blueprint)
    {
        R_CLY++;
        T_ORE -= blueprint[CLY_ORE];
    }
    inline void buildORE(const Blueprint &blueprint)
    {
        R_ORE++;
        T_ORE -= blueprint[ORE_ORE];
    }
};

class StateHash
{
  public:
    size_t operator()(const State &state) const
    {
        size_t result = state.TIME;
        result = result << 6;
        result += state.R_ORE;
        result = result << 6;
        result += state.R_CLY;
        result = result << 6;
        result += state.R_OBS;
        result = result << 6;
        result += state.R_GEO;
        result = result << 6;
        result += state.T_ORE;
        result = result << 6;
        result += state.T_CLY;
        result = result << 6;
        result += state.T_OBS;
        result = result << 6;
        result += state.T_GEO;
        return result;
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

#define BUILD(TYPE)                             \
    State nextState = state;                    \
    nextState.product();                        \
    if (nextState.T_GEO > maxGeode) {           \
        maxGeode = nextState.T_GEO;             \
    }                                           \
    if (nextState.TIME < max_time) {            \
        TYPE(blueprint);                        \
        states.push_back(std::move(nextState)); \
    }

uint16_t getGeodes(const Blueprint &blueprint, const uint16_t max_time)
{
    uint16_t maxGeode = 0;
    State initialState;

    uint16_t MAX_R_ORE =
        std::max(std::max(blueprint[GEO_ORE], blueprint[OBS_ORE]), std::max(blueprint[CLY_ORE], blueprint[ORE_ORE]));
    uint16_t MAX_R_CLY = blueprint[OBS_CLY];
    uint16_t MAX_R_OBS = blueprint[GEO_OBS];

    std::vector<State> states;
    states.reserve(4 * max_time);
    states.push_back(initialState);
    std::unordered_set<State, StateHash> calculated;
    State state;
    while (!states.empty()) {
        state = states.back();
        states.pop_back();

        // Memoize
        auto it = calculated.find(state);
        if (it != calculated.end()) {
            continue;
        }
        calculated.insert(state);

        auto remaning = max_time - state.TIME - 1;
        if (state.T_GEO + state.TIME * state.R_GEO + (remaning * (remaning + 1)) / 2 < maxGeode) {
            // If I built a GEOID robot every turn, I will not exceed the current maximum
            continue;
        }

        state.TIME++;
        // What to build
        if (state.canBuildGEO(blueprint)) {
            BUILD(nextState.buildGEO);
        } else {
            int done = 0;
            // Take a decision
            if (state.R_OBS < MAX_R_OBS && state.canBuildOBS(blueprint)) {
                BUILD(nextState.buildOBS);
                done++;
            }
            if (state.R_CLY < MAX_R_CLY && state.canBuildCLY(blueprint)) {
                BUILD(nextState.buildCLY);
                done++;
            }
            if (state.R_ORE < MAX_R_ORE && state.canBuildORE(blueprint)) {
                BUILD(nextState.buildORE);
                done++;
            }
            // Wait
            State nextState = state;
            nextState.product();
            // Update max
            if (nextState.T_GEO > maxGeode) {
                maxGeode = nextState.T_GEO;
            }
            // No need to wait if I already can build all kind of robot
            if (done < 3 && nextState.R_ORE < MAX_R_ORE && nextState.TIME < max_time) {
                states.push_back(std::move(nextState));
            }
        }
    }

    return maxGeode;
}

uint16_t getMaximisedGeode(const std::vector<Blueprint> &blueprints)
{
    uint16_t count = 0;
    uint16_t step = 1;
    for (auto &&blueprint : blueprints) {
        count += getGeodes(blueprint, 24) * step;
        step++;
    }
    return count;
}

uint16_t getMultipliedGeode(const std::vector<Blueprint> &blueprints)
{
    uint16_t count = 1;
    for (size_t i = 0; i < 3; ++i) {
        count *= getGeodes(blueprints[i], 32);
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