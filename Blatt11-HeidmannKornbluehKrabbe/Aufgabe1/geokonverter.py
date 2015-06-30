#!/usr/bin/python
#Krabbe, Heidmann, Kornblueh

import argparse

parser = argparse.ArgumentParser(prog="geokonverter",
                                 usage = "geokonverter.py -o <Ausgabeformat> [Optionen] <Input-Datei (en)>")
parser.add_argument("-o", nargs=1, action="store", help="Output type")
parser.add_argument("-f", nargs=1, action="store",
                    help="<Datei>: Angabe einer Ausgabedatei, anderfalls wird auf stdout geschrieben.")
parser.add_argument("-b", action="store_true",
                    help="Batch-Modus, es koennen beliebig viele Dateien angegenben werden, deren Formate alle in das ausgabeformat konvertiert werden; Ausgaben werden surch #----# getrennt")
parser.add_argument("inputfile", nargs="*", action="store")
args = parser.parse_args()
if(args.b):
    print("b")
    print(args.inputfile)
else:
    print(args.inputfile)
