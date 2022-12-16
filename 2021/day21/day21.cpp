/**
 * @file    day21.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    21 Dec 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day21.h"

#include "common.h"

#include <deque>

constexpr uint64_t CELLS = 10;

struct Player {
    int64_t pos = 0;
    uint64_t points = 0;
    void move(uint64_t movement)
    {
        pos += movement;
        pos = pos % CELLS;
        points += pos + 1;
    }
};

struct Game {
    Player one;
    Player two;
    bool secondRead = false;
};

void convertInput(Game *game, std::string line)
{
    if (!game->secondRead) {
        game->one.pos = line[line.size() - 1] - '0' - 1;
        game->secondRead = true;
    } else {
        game->two.pos = line[line.size() - 1] - '0' - 1;
    }
}

uint64_t findSolution1(Game *game, uint64_t total)
{
    uint64_t roll = 0;
    bool playerOneTurn = true;
    while (game->one.points < total && game->two.points < total) {
        auto movement = roll * 3 + 6;
        roll += 3;
        if (playerOneTurn) {
            game->one.move(movement);
        } else {
            game->two.move(movement);
        }
        playerOneTurn = !playerOneTurn;
    }

    if (game->one.points > game->two.points) {
        return roll * game->two.points;
    } else {
        return roll * game->one.points;
    }
}

struct Play {
    Game game;
    bool playerOneTurn = true;
    uint64_t value = 0;
    uint64_t counter = 1;
};

void splitFuture(std::deque<Play> *future, Play play)
{
    auto counter = play.counter;
    play.value = 3;
    play.counter = counter * 1;
    future->push_front(play);
    play.value = 4;
    play.counter = counter * 3;
    future->push_front(play);
    play.value = 5;
    play.counter = counter * 6;
    future->push_front(play);
    play.value = 6;
    play.counter = counter * 7;
    future->push_front(play);
    play.value = 7;
    play.counter = counter * 6;
    future->push_front(play);
    play.value = 8;
    play.counter = counter * 3;
    future->push_front(play);
    play.value = 9;
    play.counter = counter * 1;
    future->push_front(play);
}

uint64_t findSolution2(Game *game, uint64_t total)
{
    uint64_t oneWin = 0;
    uint64_t twoWin = 0;

    std::deque<Play> future;
    Play firstPlay;
    firstPlay.game.one = game->one;
    firstPlay.game.two = game->two;
    firstPlay.playerOneTurn = true;
    firstPlay.counter = 1;
    splitFuture(&future, firstPlay);

    while (!future.empty()) {
        Play play = future.front();
        future.pop_front();

        if (play.playerOneTurn) {
            play.game.one.move(play.value);
        } else {
            play.game.two.move(play.value);
        }

        if (play.game.one.points >= total || play.game.two.points >= total) {
            if (play.game.one.points > play.game.two.points) {
                oneWin += play.counter;
            } else {
                twoWin += play.counter;
            }
        } else {
            // Roll
            play.playerOneTurn = !play.playerOneTurn;
            splitFuture(&future, play);
        }
    }
    return oneWin > twoWin ? oneWin : twoWin;
}

std::string day21::process1(std::string file)
{
    Game game;
    parse::read<Game *>(file, '\n', convertInput, &game);
    auto res = findSolution1(&game, 1000);
    return std::to_string(res);
}

std::string day21::process2(std::string file)
{
    Game game;
    parse::read<Game *>(file, '\n', convertInput, &game);
    auto res = findSolution2(&game, 21);
    return std::to_string(res);
}
