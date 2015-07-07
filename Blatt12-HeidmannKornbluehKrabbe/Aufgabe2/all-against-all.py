#!/usr/bin/python
# Kornblueh, Krabbe, Heidmann

import argparse, ctypes, threading
unit_edist = ctypes.CDLL("./lib_unit_edist.so") 

parser = argparse.ArgumentParser(prog="all-against-all.py", usage="all-against-all.py -t <t> -k <k> <inputfile>")
parser.add_argument("-t", nargs=1, action="store", type=int, help="number of threads")
parser.add_argument("-k", nargs=1, action="store", type=int, help="number of pairs")
parser.add_argument("inputfile", action="store", help="inputfile to be analysed")

args = parser.parse_args()

data = open(args.inputfile)
seqs=[]
out=[]
seqsnumbers=[]
pairs=[]
threads=[]

def eval(seqs1, seqs2):
    for i in range(len(seqs1)):
            out.append((seqs1[i], seqs2[i],
                        unit_edist.eval_unit_edist(seqs[seqs1[i]], len(seqs[seqs1[i]]), seqs[seqs2[i]], len(seqs[seqs2[i]]))))

#datei einlesen
for line in data:
    if not line[0] == ">":
        seqs.append((ctypes.c_char * len(line))(*line))
data.close()

#seqsbereich init
for i in range(2*args.t[0]):
    seqsnumbers.append([])

#pairs zuweisungen   
for j in range(0, len(seqs)):
    for k in range(j, len(seqs)):
        if not j == k:
            pairs.append((j, k))
            
for i in range(len(pairs)):
    for j in range(args.t[0]):
        if i%args.t[0]==j:
            seqsnumbers[j*2].append(pairs[i][0])
            seqsnumbers[j*2+1].append(pairs[i][1])
            
#diesen teil parallel
for i in range(args.t[0]):
    threads.append(threading.Thread(target=eval, args=(seqsnumbers[i*2], seqsnumbers[(i*2)+1])))
    threads[i].start()
for i in range(args.t[0]):
    threads[i].join()

#output    
out.sort(key=lambda tup: tup[2])
for i in range(args.k[0]):
    print("{:<6.0f}{:<6.0f}{:<6.0f}".format(out[i][0], out[i][1], out[i][2]))
    
