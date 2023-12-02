/**
 * @file    day02.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    02 Dec 2023
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day02.h"

#include "common.h"

struct Set {
    int red = 0;
    int green = 0;
    int blue = 0;
};

struct Game {
    int id;
    std::vector<Set> sets;
};

char getFirstChar(std::string line)
{
    for (auto c : line) {
        if ('a' <= c && c <= 'z') {
            return c;
        }
    }
    return ' ';
}

Game parseGame(std::string line)
{
    Game game;

    auto split1res = parse::split(line, ':');
    game.id = parse::getInteger(split1res[0]);

    auto sets = parse::split(split1res[1], ';');
    for (auto &&set : sets) {
        Set gameSet;
        auto colors = parse::split(set, ',');
        for (auto &&color : colors) {
            int value = parse::getInteger(color);
            switch (getFirstChar(color)) {
                case 'r':
                    gameSet.red = value;
                    break;
                case 'b':
                    gameSet.blue = value;
                    break;
                case 'g':
                    gameSet.green = value;
                    break;
                default:
                    break;
            }
        }
        game.sets.push_back(gameSet);
    }

    return game;
}

void insert(Game part, std::vector<Game> *list)
{
    list->push_back(std::move(part));
}

uint64_t countValids(std::vector<Game> &games, Set initial)
{
    uint64_t sum = 0;
    for (auto &&game : games) {
        bool allOk = true;
        for (auto &&set : game.sets) {
            if (!(set.red <= initial.red && set.blue <= initial.blue && set.green <= initial.green)) {
                allOk = false;
                break;
            }
        }
        if (allOk) {
            sum += game.id;
        }
    }
    return sum;
}

uint64_t countPower(std::vector<Game> &games)
{
    uint64_t sum = 0;
    for (auto &&game : games) {
        Set minSet = { 0, 0, 0 };

        for (auto &&set : game.sets) {
            minSet.red = std::max(minSet.red, set.red);
            minSet.green = std::max(minSet.green, set.green);
            minSet.blue = std::max(minSet.blue, set.blue);
        }

        uint64_t power = minSet.red * minSet.blue * minSet.green;
        sum += power;
    }
    return sum;
}

std::string day02::process1(std::string file)
{
    std::vector<Game> games;

    parse::read<Game, std::vector<Game> *>(file, '\n', parseGame, insert, &games);

    auto result = countValids(games, { 12, 13, 14 });
    return std::to_string(result);
}

std::string day02::process2(std::string file)
{
    std::vector<Game> games;

    parse::read<Game, std::vector<Game> *>(file, '\n', parseGame, insert, &games);

    auto result = countPower(games);
    return std::to_string(result);
}