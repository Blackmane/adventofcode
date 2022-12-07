/**
 * @file    day07.cpp
 * @project advent of code
 *
 * @author  Niccolò Pieretti
 * @date    07 Dec 2022
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

struct File {
    uint64_t size;
};

struct Dir {
    std::string name;
    Dir *parent;
    std::vector<Dir> subdir;
    std::vector<File> files;

    uint64_t size = 0;

    void calculateSize()
    {
        size = 0;
        for (auto &&dir : subdir) {
            dir.calculateSize();
            size += dir.size;
        }
        for (auto &&file : files) {
            size += file.size;
        }
    }

    uint64_t sumOfFilteredSize()
    {
        uint64_t sum = 0;
        if (size <= 100000) {
            sum += size;
        }
        for (auto &&dir : subdir) {
            sum += dir.sumOfFilteredSize();
        }
        return sum;
    }

    std::set<uint64_t> getDirSize()
    {
        std::set<uint64_t> sizes;
        sizes.insert(size);
        for (auto &&dir : subdir) {
            auto subdirSizes = dir.getDirSize();
            sizes.insert(subdirSizes.begin(), subdirSizes.end());
        }
        return sizes;
    }

    uint64_t getDeletedSize()
    {
        uint64_t freeSpace = 70000000 - size;
        std::set<uint64_t> dirSize = getDirSize();
        for (auto s : dirSize) {
            if (s + freeSpace >= 30000000) {
                return s;
            }
        }
        return 0;
    }
};

Dir navigate(std::vector<std::string> &list)
{
    Dir root;
    Dir *cur = &root;

    for (auto &&line : list) {
        if (line[0] == '$') {
            // command
            if (line[2] == 'c') {
                auto name = line.substr(5, line.size() - 5);
                if (name.compare("/") == 0) {
                    cur->name = name;
                    // do nothing, first command
                } else if (name.compare("..") == 0) {
                    cur = cur->parent;
                } else {
                    for (auto &&dir : cur->subdir) {
                        if (dir.name.compare(name) == 0) {
                            cur = &dir;
                            break;
                        }
                    }
                }
            }
            // else ls, nothing to do
        } else if (line[0] == 'd') {
            // dir
            auto parts = parse::split(line, ' ');
            Dir dir;
            dir.name = parts[1];
            dir.parent = cur;
            cur->subdir.push_back(dir);
        } else {
            // file
            auto parts = parse::split(line, ' ');
            File file;
            file.size = std::stoull(parts[0]);
            cur->files.push_back(file);
        }
    }
    return root;
}

std::string process1(std::string file)
{
    std::vector<std::string> list;
    parse::read_all(file, &list);

    auto root = navigate(list);
    root.calculateSize();
    auto result = root.sumOfFilteredSize();
    return std::to_string(result);
}

std::string process2(std::string file)
{
    std::vector<std::string> list;
    parse::read_all(file, &list);

    auto root = navigate(list);
    root.calculateSize();
    auto result = root.getDeletedSize();
    return std::to_string(result);
}
