'''
Heidmann
Kornblueh
Krabbe
'''

class daten_analyse:

    def __init__(self, filename):
        # is it good practise to have
        # __init__ handle so much stuff?
        from re import findall
        from numpy import mean, std

        temperatures = []
        n_of_tests = []
        velocities = []
        measurements = []
        n_of_runs = -1

        with open(filename, 'r') as data_file:
            for line in data_file:
                if 'Temperatur:' in line:
                    n_of_runs += 1
                    n_of_tests.append(0)
                    temp = float(findall('-?\d+.\d+', line)[0])
                    temperatures.append(temp)
                elif 'Fliessgeschwindigkeit:' in line:
                    press = float(findall('\d+.\d+', line)[0])
                    pressures.append(press)
                elif 'Messwert:' in line:
                    energy = float(findall('\d+.\d+', line)[0])
                    energies.append(energy)
                elif 'Test Nr.' in line:
                    n_of_tests[n_of_runs] += 1

        self.mean_T = mean(temperatures)
        self.mean_v = mean(velocities)
        self.mean_n = mean(n_of_tests)
        self.mean_w = mean(measurements)

        self.std_T = std(temperatures)
        self.std_v = std(velocities)
        self.std_n = std(n_of_tests)
        self.std_w = std(measurements)

        self.range_T = (min(temperatures), max(temperatures))
        self.range_v = (min(velocities), max(velocities))
        self.range_n = (min(n_of_tests), max(n_of_tests))
        self.range_w = (min(measurements), max(measurements))

    def __str__(self):
        ret = "=== Analyse der Ergebnisse in "
        ret += self.filename + " ==="
        ret += " - Temperatur: " + str(self.mean_T)
        ret += " +/- " + str(self.std_T) + "\n"
        ret += "   Wertebereich: " + str(self.range_T[0])
        ret += " - " + str(self.range_T[1]) + "\n"
        ret += " - Fliessgeschwindigkeit: " + str(self.mean_v)
        ret += " +/- " + str(self.std_v) + "\n"
        ret += "   Wertebereich:" + str(self.range_v[0])
        ret += " - " + str(self.range_v[1]) + "\n"
        ret += " - notwendige Tests:" + str(self.mean_n)
        ret += " +/- " + str(self.std_n) + "\n"
        ret += "   Wertebereich:" + str(self.range_n[0])
        ret += " - " + str(self.range_n[1]) + "\n"
        ret += " - Messwert:" + str(self.mean_w)
        ret += " +/- " + str(self.std_w) + "\n"
        ret += "   Wertebereich:" + str(self.range_w[0])
        ret += " - " + str(self.range_w[1])
        return ret

    def plot_results(self):
        import matplotlib.pyplot as plt
        pass
