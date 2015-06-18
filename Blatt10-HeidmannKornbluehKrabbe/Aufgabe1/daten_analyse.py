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
        print("=== Analyse der Ergebnisse in",
                self.filename, "===")
        print(" - Temperatur:", self.mean_T,
                "+/-", self.std_T)
        print("   Wertebereich:", self.range_T[0],
                "-", self.range_T[1])
        print(" - Fliessgeschwindigkeit:", self.mean_v,
                "+/-", self.std_v)
        print("   Wertebereich:", self.range_v[0],
                "-", self.range_v[1])
        print(" - notwendige Tests:", self.mean_n,
                "+/-", self.std_n)
        print("   Wertebereich:", self.range_n[0],
                "-", self.range_n[1])
        print(" - Messwert:", self.mean_w,
                "+/-", self.std_w)
        print("   Wertebereich:", self.range_w[0],
                "-", self.range_w[1])

    def plot_results(self):
        pass

