#!/usr/bin/env python3

from daten_analyse import daten_analyse as da

while(True):
    filename = input("Bitte geben Sie den Namen "
            + "der zu untersuchenden Datei: ")
    print("Analysiere", filename, "...")
    try:
        analyzer = da(filename)
    except FileNotFoundError:
        print("Datei existiert nicht!")
        continue
    except PermissionError:
        print("Sie haben nicht die benötigten Rechte!")
        continue
    break

print(analyzer)

print()

print("Konstruiere Graphen...")
analyzer.plot_results()
print("Graphen konstruiert in Abb1.pdf und Abb2.pdf!")
