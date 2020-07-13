import os
from os import path
from pathlib import Path


def find_and_remove(file_dirctory):
    the_list = os.listdir(file_dirctory)
    for name in the_list:
        name = path.join(file_dirctory, name)
        if path.isfile(name):
            name_list = path.splitext(name)
            if name_list[-1] in ['.tmp', '.log', '.obj', '.txt'] or path.getsize(name) == 0:
                os.remove(name)
                print("%s" %name + " deleted......")
        elif path.isdir(name):
            find_and_remove(name)

dirctory = input("input the dirctory: ")
file_dirctory = Path(dirctory)
find_and_remove(file_dirctory)




#/Users/jerryw/Desktop/experience