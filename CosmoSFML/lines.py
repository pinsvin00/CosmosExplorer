from os import listdir
from os.path import isfile, join
import pathlib

def count(name):
    f = open(name)
    lines = 0
    for x in f:
        lines += 1
    return lines

def getLines():
    files = [f for f in listdir(pathlib.Path().absolute()) if isfile(join(pathlib.Path().absolute(), f))]
    lines = 0
    for x in files:
        if x.endswith(".cpp") or x.endswith(".h"):
            lines += count(x)
    return lines


f = open("lines.txt", "w")
f.write(str(getLines()))