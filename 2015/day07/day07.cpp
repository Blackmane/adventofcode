/**
 * @file    day07.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    07 Dec 2023
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "day07.h"

#include "common.h"

#include <queue>

enum Type { NOT, AND, OR, LSHIFT, RSHIFT, ASSIGN, CONNECT };

struct Connection {
    Type type;
    uint16_t value;
    std::string from1;
    std::string from2;
    std::string to;
};

void insert(std::vector<Connection> *connections, const std::string &line)
{
    auto parts = parse::split(line, ' ');
    if (parts[0] == "NOT") {
        Connection connection;
        connection.type = Type::NOT;
        connection.from1 = parts[1];
        connection.to = parts[3];
        connections->push_back(std::move(connection));
    }
    if (parts[1] == "AND") {
        Connection connection;
        connection.type = Type::AND;
        if (parts[0][0] >= 'a' && parts[0][0] <= 'z') {
            connection.from1 = parts[0];
            connection.from2 = parts[2];
        } else {
            connection.from1 = parts[2];
            connection.value = std::stoll(parts[0]);
        }
        connection.to = parts[4];
        connections->push_back(std::move(connection));
    }
    if (parts[1] == "OR") {
        Connection connection;
        connection.type = Type::OR;
        connection.from1 = parts[0];
        connection.from2 = parts[2];
        connection.to = parts[4];
        connections->push_back(std::move(connection));
    }
    if (parts[1] == "LSHIFT") {
        Connection connection;
        connection.type = Type::LSHIFT;
        connection.from1 = parts[0];
        connection.value = std::stoll(parts[2]);
        connection.to = parts[4];
        connections->push_back(std::move(connection));
    }
    if (parts[1] == "RSHIFT") {
        Connection connection;
        connection.type = Type::RSHIFT;
        connection.from1 = parts[0];
        connection.value = std::stoll(parts[2]);
        connection.to = parts[4];
        connections->push_back(std::move(connection));
    }
    if (parts[1] == "->") {
        if (parts[0][0] >= 'a' && parts[0][0] <= 'z') {
            Connection connection;
            connection.type = Type::CONNECT;
            connection.from1 = parts[0];
            connection.to = parts[2];
            connections->push_back(std::move(connection));
        } else {
            Connection connection;
            connection.type = Type::ASSIGN;
            connection.value = std::stoll(parts[0]);
            connection.to = parts[2];
            connections->push_back(std::move(connection));
        }
    }
}

std::map<std::string, uint16_t> connect(std::vector<Connection> &connections)
{
    std::map<std::string, uint16_t> variables;
    std::queue<Connection> list;
    for (auto &&connection : connections) {
        if (connection.type == Type::ASSIGN) {
            variables[connection.to] = connection.value;
        } else {
            list.push(connection);
        }
    }
    while (!list.empty()) {
        auto curr = list.front();
        list.pop();
        auto from1It = variables.find(curr.from1);
        if (from1It == variables.end()) {
            list.push(std::move(curr));
            continue;
        }
        if (curr.type == Type::AND || curr.type == Type::OR) {
            uint16_t value2 = 0;
            if (curr.from2 == "") {
                value2 = curr.value;
            } else {
                auto from2It = variables.find(curr.from2);
                if (from2It == variables.end()) {
                    list.push(std::move(curr));
                    continue;
                }
                value2 = from2It->second;
            }
            if (curr.type == Type::AND) {
                variables[curr.to] = (from1It->second) & value2;
            } else {
                variables[curr.to] = (from1It->second) | value2;
            }
            continue;
        }
        switch (curr.type) {
            case Type::NOT:
                variables[curr.to] = ~(from1It->second);
                break;
            case Type::LSHIFT:
                variables[curr.to] = (from1It->second) << curr.value;
                break;
            case Type::RSHIFT:
                variables[curr.to] = (from1It->second) >> curr.value;
                break;
            case Type::CONNECT:
                variables[curr.to] = (from1It->second);
                break;
            default:
                break;
        }
    }

    return variables;
}

std::string day07::process1(std::string file)
{
    std::vector<Connection> connections;
    parse::read<std::vector<Connection> *>(file, '\n', insert, &connections);
    auto variables = connect(connections);
    return std::to_string(variables["a"]);
}

std::string day07::process2(std::string file)
{
    std::vector<Connection> connections;
    parse::read<std::vector<Connection> *>(file, '\n', insert, &connections);
    auto variables = connect(connections);
    Connection setB;
    setB.type = Type::ASSIGN;
    setB.to = "b";
    setB.value = variables["a"];
    connections.push_back(setB);
    variables = connect(connections);
    return std::to_string(variables["a"]);
}