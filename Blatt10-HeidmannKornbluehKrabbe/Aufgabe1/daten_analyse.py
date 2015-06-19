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
        ret += self.filename + " ===\n"
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

    def _running_mean(self, l):
        means = []
        s = 0
        for n, value in enumerate(l):
            s += value
            means.append(s / (n + 1))
        return means

    def _running_sterr(self, l, means):
        sterr = []
        for n, value in enumerate(l):
            sq_sum = 0
            for m in range(n+1):
                sq_sum += (l[m] - means[n]) ** 2
            sterr.append((sq_sum ** 0.5) / (n + 1))
        return sterr

    def plot_results(self):
        import matplotlib.pyplot as plt

        indices = [i for i in range(1, self.n_of_runs + 2)]

        # Abbildung 1
        plt.figure(figsize=(10,10))

        ## temperature plot
        plt.subplot(311)
        plt.plot(self.temperatures, "ko")
        means = self._running_mean(self.temperatures)
        plt.errorbar(indices,
                     means,
                     fmt="r-p",
                     yerr=self._running_sterr(self.temperatures, means))
        plt.ylabel("Temperatur (°C)")
        plt.title('Abbildung 1')

        ## velocity plot
        plt.subplot(312)
        plt.plot(self.velocities, "ks")
        means = self._running_mean(self.velocities)
        plt.errorbar(indices,
                     means,
                     fmt="r-p",
                     yerr=self._running_sterr(self.velocities, means))
        plt.ylabel("Flussgeschwindigkeit (cm/s)")

        ## measurement plot
        plt.subplot(313)
        plt.plot(self.measurements, "k^")
        means = self._running_mean(self.measurements)
        plt.errorbar(indices,
                     means,
                     fmt="r-p",
                     yerr=self._running_sterr(self.measurements, means))
        plt.ylabel("Messwert")
        plt.xlabel("# Messung")

        plt.grid(True)
        plt.savefig('Abb1.pdf')

        plt.clf()

        # Abbildung 2
        plt.hist(self.n_of_tests, range(1,7), color="gray")
        plt.xlabel("Notwendige Tests")
        plt.ylabel("Anzahl Messungen")
        plt.title("Abbildung 2")
        
        plt.savefig("Abb2.pdf")
