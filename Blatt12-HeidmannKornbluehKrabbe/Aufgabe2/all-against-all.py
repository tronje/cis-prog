#!/usr/bin/python
# Kornblueh, Krabbe, Heidmann

import argparse, ctypes
clib = ctypes.CDLL("unit_edist.h")


parser = argparse.ArgumentParser(prog="all-against-all.py", usage="all-against-all.py -t <t> -k <k> <inputfile>")
parser.add_argument("-t", nargs=1, action="store", type=int, help="number of pairs")
parser.add_argument("-k", nargs=1, action="store", type=int, help="number of threads")
parser.add_argument("inputfile", action="store", help="inputfile to be analysed")

args = parser.parse_args()

data = open(args.inputfile)
seqs=[]
for line in data:
    if not line[0] == ">":
        seqs.append((ctypes.c_char * len(line))(*line))
data.close()

for i in len(seqs):
    for j in len(seqs):
        if not i == j:
            print i, j
