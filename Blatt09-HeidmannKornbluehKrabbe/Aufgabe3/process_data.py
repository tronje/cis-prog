#!/bin/env python3
'''
Heidmann
Kornblueh
Krabbe
'''

from re import findall

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

# we used numpy earlier, but it felt like cheating
# so we defined our own functions for mean and
# standard deviation.
def mean(l):
    ''' Returns the arithmetic mean
        for a list of numbers.'''
    return sum(l)/len(l)

def std(l, mean):
    ''' Returns the standard deviation
        for a list of numbers.'''
    ret = 0
    for e in l:
        ret += (e - mean) ** 2
    return (ret / len(l)) ** (0.5)

#calculate relevant information for printing later
temp_mean = mean(temperatures)
press_mean = mean(pressures)
en_mean = mean(energies)
oor_mean = mean(out_of_range)

temp_std = std(temperatures, temp_mean)
press_std = std(pressures, press_mean)
en_std = std(energies, en_mean)
oor_std = std(out_of_range, oor_mean)

# print all relevant information
# we felt like 4 decimal places were sensible
print("=== Ergebnisse ===")
print(" - Temperatur:", "%.4f" % temp_mean,\
        "+/-", "%.4f" % temp_std)
print("   Wertebereich:",  str(min(temperatures)),\
        "-", str(max(temperatures)))
print(" - Druck:", "%.4f" % press_mean,\
        "+/-", "%.4f" % press_std)
print("   Wertebereich:", str(min(pressures)),\
        "-", str(max(pressures)))
print(" - intermolekulare Energie:", "%.4f" % en_mean,\
        "+/-", "%.4f" % en_std)
print("   Wertebereich:", str(min(energies)),\
        "-", str(max(energies)))
print(" - Molekuele ausser Reichweite:", "%.4f" % oor_mean,\
        "+/-", "%.4f" % oor_std)
print("   Wertebereich:", str(min(out_of_range)),\
        "-", str(max(out_of_range)))
