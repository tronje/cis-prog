#!/usr/bin/env python3

import sys
from daten_analyse import daten_analyse as da

filename = input("Bitte geben Sie den Namen der zu untersuchenden Datei: ")

print("Analysiere", filename, "...")
analyzer = da(filename)

print(analyzer)

print("Konstruiere Graphen...")
analyzer.plot_results()
print("Graphen konstruiert in Abb1.pdf und Abb2.pdf!")
