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

        self.filename = filename

        self.temperatures = []
        self.n_of_tests = []
        self.velocities = []
        self.measurements = []
        self.n_of_runs = -1

        with open(filename, 'r') as data_file:
            for line in data_file:
                if 'Temperatur:' in line:
                    self.n_of_runs += 1
                    self.n_of_tests.append(0)
                    temp = float(findall('-?\d+.\d+', line)[0])
                    self.temperatures.append(temp)
                elif 'Fliessgeschwindigkeit:' in line:
                    vel = float(findall('\d+.\d+', line)[0])
                    self.velocities.append(vel)
                elif 'Messwert:' in line:
                    mes = float(findall('\d+.\d+', line)[0])
                    self.measurements.append(mes)
                elif 'Test Nr.' in line:
                    self.n_of_tests[self.n_of_runs] += 1

        self.mean_T = mean(self.temperatures)
        self.mean_v = mean(self.velocities)
        self.mean_n = mean(self.n_of_tests)
        self.mean_w = mean(self.measurements)

        self.std_T = std(self.temperatures)
        self.std_v = std(self.velocities)
        self.std_n = std(self.n_of_tests)
        self.std_w = std(self.measurements)

        self.range_T = (min(self.temperatures), max(self.temperatures))
        self.range_v = (min(self.velocities), max(self.velocities))
        self.range_n = (min(self.n_of_tests), max(self.n_of_tests))
        self.range_w = (min(self.measurements), max(self.measurements))

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
        # works okay
        plt.plot(self.temperatures)
        plt.title('test')
        plt.grid(True)
        plt.savefig('test.pdf')
        plt.show
