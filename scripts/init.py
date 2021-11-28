#!/usr/bin/python

import sys
import os
from datetime import date
from string import Template


def init(path, name, template_path):
    fullpath = os.path.join(path, name)

    response = input("Create %s ? (Y)\n>" % fullpath)
    if len(response) > 0 and response[0] != 'y' and response[0] != 'Y':
        print("terminate")
        exit(1)

    print("continue")

    try:
        print("Creating dir: %s" % fullpath)
        os.mkdir(fullpath)
    except FileNotFoundError as e:
        print("Error in path: %s" % e)
        exit(1)
    except FileExistsError:
        print("Already exists, continue")

    today = date.today()

    subs = {
        'DAY': name,
        'TEST': 'test_' + name,
        'TESTCOMMAND': name + '_test',
        'TODAY': today.strftime("%d %b %Y")
    }

    files = [
        ['CMakeLists.txt', 'CMakeLists.txt'],
        ['dayXX.cpp', name + '.cpp'],
        ['dayXX.h', name + '.h'],
        ['main.cpp', 'main.cpp'],
        ['test.cpp', 'test.cpp'],
        ['input.txt', 'input.txt'],
        ['test1.txt', 'test1.txt']
    ]

    for file in files:
        file_from = file[0]
        file_to = file[1]
        print("Open: " + template_path + '/' + file_from)
        with open(template_path + '/' + file_from, 'r') as f:
            src = Template(f.read())
            result = src.substitute(subs)
            print("Creation: " + fullpath + "/" + file_to)
            filecpp = open(fullpath + "/" + file_to, "w")
            filecpp.write(result)
            print("Created")


def fromCurrentDir(path, name):
    current_directory = os.path.abspath(os.getcwd())
    cur_path = os.path.join(current_directory, path)
    init(cur_path, name, current_directory + '/template')
