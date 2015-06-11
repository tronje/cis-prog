#!/bin/env python3

from re import findall
from numpy import mean
from numpy import std

filename = 'Messwerte.txt'

temperatures = []
pressures = []
energies = []
out_of_range = []
n_of_runs = -1

# read data from the file
with open(filename, 'r') as data_file:
    for line in data_file:
        if 'temperature' in line:
            # every time we find 'temperature',
            # we know there's a new run
            n_of_runs += 1
            out_of_range.append(0)
            # it's funny because temp can be short for
            # temperature _or_ temporary. :)
            temp = float(findall('-?\d+.\d+', line)[0])
            temperatures.append(temp)
        elif 'pressure' in line:
            # thankfully, we can't really have negative pressure
            press = float(findall('\d+.\d+', line)[0])
            pressures.append(press)
        elif 'E(intermolecular)' in line:
            energy = float(findall('\d+.\d+', line)[0])
            energies.append(energy)
        elif 'molecule' in line and 'yes' in line:
            out_of_range[n_of_runs] += 1

# calculate and print all relevant information
print("=== Ergebnisse ===")
print(" - Temperatur:", str(mean(temperatures)),\
        "+/-", str(std(temperatures)))
print("   Wertebereich:",  str(min(temperatures)),\
        "-", str(max(temperatures)))
print(" - Druck:", str(mean(pressures)),\
        "+/-", str(std(pressures)))
print("   Wertebereich:", str(min(pressures)),\
        "-", str(max(pressures)))
print(" - intermolekulare Energie:", str(mean(energies)),\
        "+/-", str(std(energies)))
print("   Wertebereich:", str(min(energies)),\
        "-", str(max(energies)))
print(" - Molekuele ausser Reichweite:", str(mean(out_of_range)),\
        "+/-", str(std(out_of_range)))
print("   Wertebereich:", str(min(out_of_range)),\
        "-", str(max(out_of_range)))
