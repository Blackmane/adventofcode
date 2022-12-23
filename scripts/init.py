#!/usr/bin/python

import sys
import os
from datetime import date
from string import Template


def init(path, year, day, template_path, overwrite):
    fullpath = os.path.join(path, day)

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
        'YEAR': year,
        'DAY': day,
        'TEST': 'test_' + day,
        'TESTCOMMAND': day + '_test',
        'TODAY': today.strftime("%d %b %Y")
    }

    files = [
        ['CMakeLists.txt', 'CMakeLists.txt'],
        ['dayXX.cpp', day + '.cpp'],
        ['dayXX.h', day + '.h'],
        ['main.cpp', 'main.cpp'],
        ['test.cpp', 'test.cpp'],
        ['input_temp.txt', 'input.txt'],
        ['test1.txt', 'test1.txt']
    ]

    for file in files:
        file_from = os.path.join(template_path, file[0])
        file_to = os.path.join(fullpath, file[1])
        if not overwrite and os.path.exists(file_to) and os.path.getsize(file_to) > 0:
            print("Already exists: " + file_to)
        else:
            print("Open: " + file_from)
            with open(file_from, 'r') as f:
                src = Template(f.read())
                result = src.substitute(subs)
                print("Creation: " + file_to)
                filecpp = open(file_to, "w")
                filecpp.write(result)
                print("Created")


def fromCurrentDir(year, day, overwrite):
    current_directory = os.path.abspath(os.getcwd())
    cur_path = os.path.join(current_directory, year)
    init(cur_path, year, day, current_directory + '/template', overwrite)
