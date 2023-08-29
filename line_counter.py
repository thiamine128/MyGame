# -*- coding: utf-8 -*-
"""
Created on Sun Aug 27 21:39:42 2023

@author: saltyfishsss
"""

import os

def findCpps(path):
    lis = []
    for root, dir, files in os.walk(path):
        for file in files:
            if file.endswith(".cpp") and not "imgui" in file and (not "rendering" in root):
                lis.append(root + "\\" + file)
    return lis

def lineCount(path):
    count = 0
    with open(path) as fp:
        for count, line in enumerate(fp):
            pass
    print(path, count + 1)
    return count + 1

files = findCpps("src")
tot = 0
for f in files:
    tot = tot + lineCount(f)
print(tot)