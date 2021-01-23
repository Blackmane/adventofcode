/**
 * @file    day22.cpp
 * @brief   
 * @project advent of code 2020
 * 
 * @author  Niccolò Pieretti
 * @date    10 Gen 2021
 * @bug     
 * @todo    
 * 
 ****************************************************************************-
 *                                              
 *             _  _   o   __  __   __    _  o   _   ,_    _  
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/  
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|                     
 *                                    \|     
 ****************************************************************************/

#include <deque>
#include <fstream>
#include <iostream>
#include <set>
#include <string>


namespace day22 {

class Players {
public:
    Players(std::string inputFilename);
    uint64_t play();
    uint64_t playRecursive();
    uint64_t startGame();
private:
    std::deque<uint64_t> deckOne;
    std::deque<uint64_t> deckTwo;

    void playHand();
};

// Used by hash function
uint64_t primeNumbers[] = {/*1,*/ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 
    71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 
    179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281};

class Game {
public:
    Game(std::deque<uint64_t> _deckOne, std::deque<uint64_t> _deckTwo);
    uint64_t play();
    uint64_t getWinnerPoints();
private:
    std::deque<uint64_t> deckOne;
    std::deque<uint64_t> deckTwo;
    std::set<uint64_t> rounds;
    void playHand();
    bool saveRound();
};

uint64_t process1(std::string file);
uint64_t process2(std::string file);

} // namespace day22


// ===== ===== ===== Main ===== ===== ===== 
int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No input file" << std::endl;
        return 1;
    }
	std::string inputFilename(argv[1]);

    // Part 1
    std::cout << "Part1" << std::endl;
    std::cout << day22::process1(inputFilename) << std::endl;
    
    // Part 2
    std::cout << "Part2" << std::endl;
    std::cout << day22::process2(inputFilename) << std::endl;

	return 0;
}


// ===== ===== ===== Implementations ===== ===== ===== 

uint64_t day22::process1(std::string file) {
    Players players(file);
    return players.play();
}


uint64_t day22::process2(std::string file) {
    Players players(file);
    return players.playRecursive();
}

// ===== ===== ===== Implementations ===== ===== ===== 

day22::Players::Players(std::string inputFilename) {
    std::ifstream source;
    source.open(inputFilename);
    std::string part;
    // Read player 1 deck
    while (std::getline(source, part, '\n')) {
        if (part == "") {
            break;
        }
        if (part != "Player 1:") {
            deckOne.push_back(std::stol(part));
        }
    }
    // Read player 2 deck
    while (std::getline(source, part, '\n')) {
        if (part != "" && part != "Player 2:") {
            deckTwo.push_back(std::stol(part));
        }
    }
}


uint64_t day22::Players::play() {
    // Play until a deck has no cards
    while (deckOne.size() > 0 && deckTwo.size() > 0 ) {
        playHand();
    }
    // Check the winner
    std::deque<uint64_t> *winnerDeck;
    if (deckOne.size() > 0) {
        winnerDeck = &deckOne;
    } else {
        winnerDeck = &deckTwo;
    }
    // Calculate score
    uint64_t sum = 0;
    size_t len = winnerDeck->size();
    for (auto card : *winnerDeck) {
        sum += card * len;
        len--;
    }
    return sum;
}


void day22::Players::playHand() {
    // Draw a card
    uint64_t cardOne = deckOne.front();
    deckOne.pop_front();
    uint64_t cardTwo = deckTwo.front();
    deckTwo.pop_front();
    // Check who win and put them on bottom
    if (cardOne > cardTwo) {
        deckOne.push_back(cardOne);
        deckOne.push_back(cardTwo);
    } else {
        deckTwo.push_back(cardTwo);
        deckTwo.push_back(cardOne);
    }
}


uint64_t day22::Players::playRecursive() {
    // Copy decks and start game
    Game game(deckOne, deckTwo);
    game.play();
    return game.getWinnerPoints();
}


day22::Game::Game(std::deque<uint64_t> _deckOne, std::deque<uint64_t> _deckTwo) {
    deckOne = _deckOne;
    deckTwo = _deckTwo;
}


uint64_t day22::Game::play() {
    // Play until a deck has no cards
    while (deckOne.size() > 0 && deckTwo.size() > 0 ) {
        playHand();
        // Save and check loop condition
        if (!saveRound()) {
            // is a loop: player one win
            return 1;
        }
    }
    // Check the winner
    if (deckOne.size() > 0) {
        // player one win
        return 1;
    } else {
        // player two win
        return 2;
    }
}


bool day22::Game::saveRound() {
    // Hash decks
    uint64_t hashOne = 0;
    uint64_t i = 0;
    for (auto card : deckOne) {
        hashOne += card * primeNumbers[i];
        i++;
    }
    uint64_t hashTwo = 0;
    i = 0;
    for (auto card : deckTwo) {
        hashTwo += card * primeNumbers[i];
        i++;
    }
    // Check existence
    auto round = hashOne * hashTwo; // i'm not sure it's ok
    if (rounds.find(round) != rounds.end()) {
        //  Already exists
        return false;
    } else {
        // Save state
        rounds.insert(round);
        return true;
    }
}


uint64_t day22::Game::getWinnerPoints() {
    // Check winner
    std::deque<uint64_t> *winnerDeck;
    if (deckOne.size() > 0) {
        winnerDeck = &deckOne;
    } else {
        winnerDeck = &deckTwo;
    }
    // Calculate score
    uint64_t sum = 0;
    size_t len = winnerDeck->size();
    for (auto card : *winnerDeck) {
        sum += card * len;
        len--;
    }
    return sum;
}


void day22::Game::playHand() {
    // Draw a card
    uint64_t cardOne = deckOne.front();
    deckOne.pop_front();
    uint64_t cardTwo = deckTwo.front();
    deckTwo.pop_front();
    // Check that the decks have enough cards to start a new game
    if (deckOne.size() >= cardOne && deckTwo.size() >= cardTwo) {
        // Copy decks
        std::deque<uint64_t> subdeckOne;
        int count = cardOne;
        for (auto card : deckOne) {
            if (count <= 0) {
                break;
            }
            subdeckOne.push_back(card);
            count--;
        }
        std::deque<uint64_t> subdeckTwo;
        count = cardTwo;
        for (auto card : deckTwo) {
            if (count <= 0) {
                break;
            }
            subdeckTwo.push_back(card);
            count--;
        }
        // Create a new sub game
        Game game(subdeckOne, subdeckTwo);
        if (game.play() == 1) {
            // Player one win
            deckOne.push_back(cardOne);
            deckOne.push_back(cardTwo);
        } else {
            // Player two win
            deckTwo.push_back(cardTwo);
            deckTwo.push_back(cardOne);
        }
    } else {
        // Check who win
        if (cardOne > cardTwo) {
            deckOne.push_back(cardOne);
            deckOne.push_back(cardTwo);
        } else {
            deckTwo.push_back(cardTwo);
            deckTwo.push_back(cardOne);
        }
    }
}