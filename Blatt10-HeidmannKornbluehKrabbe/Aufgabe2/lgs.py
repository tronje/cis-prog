'''
Heidmann
Kornblueh
Krabbe
'''

import re

p = re.compile(r'[+-]?(\d+(\.\d*)?|\.\d+)([eE][+-]?\d+)?')

class Lgs:
    ''' Klasse zum loesen eines linearen Gleichungssystems'''
    def __init__(self, data):
        self.koeffmat = data
        self.lsgvektor = [0 for x in range(len(data))]

    def istgueltig(self):
        rightSize = True
        anyFirstPosNotZero = False;
        returnValue = False

        for x in self.koeffmat:
            if len(x)  != len(self.koeffmat) + 1:
                rightSize = False

        for x in self.koeffmat:
            print(x[0])
            if x[0] != 0:
                anyFirstPosNotZero = True

        if rightSize == True and anyFirstPosNotZero == True:
            returnValue = True

        return returnValue;

    def isthomogen(self):
        isthomogen = True;

        for x in self.koeffmat:
            if x[len(self.koeffmat)] != 0:
                isthomogen = False

        if self.istgueltig() == True and isthomogen == True:
            return True

        return False

    def isteindeutig(self):
        x = 1
        for i in range(len(self.koeffmat)):
            x *= self.koeffmat[i][i]
        if x == 0 and self.istgueltig() == True:
            return False
        return True

    def bestimme_loesungsvektor(self):

        l =  len(self.koeffmat)
        for i in range(l):

            #if first in line is 0 switch with a line where pos 0 is not 0
            if self.koeffmat[i][0] == 0:
                print("switch")
                #TODO: SWITCH IF ...
            for j in range(i + 1,l):
                faktor = -1 * self.koeffmat[j][i] / self.koeffmat[i][i]
                for k in range(i,len(self.koeffmat[0])):
                    print("lol")
                    
                    self.koeffmat[j][k] = self.koeffmat[j][k] + faktor * self.koeffmat[i][k]
        print(self.koeffmat)

        for i in range(l):
            self.lsgvektor[i] = self.koeffmat[i][len(self.koeffmat[0]) - 1] 
     
    def __str__(self):
        print("")
        pass

def getInput():
    allIsDigit = False
    done = False
    posOneGrtNull = False;
    number_of_entries_in_line = 0
    number_of_lines = 0
    matrix = []

    x = input("please enter matrix line or type \"done\" when done: ")    
    y = x.split()

    matrix.append(y)

    allIsDigit = all(p.match(elem) for elem in matrix[number_of_lines])

    if allIsDigit == False:
        print("Error: Input has non digit parts")
        exit()
    matrix[number_of_lines] = [float(elem) for elem in matrix[number_of_lines]]
    number_of_lines += 1
    number_of_entries_in_line = len(y)

    while done == False:

        #check if all line have the same length
        if len(y) != number_of_entries_in_line:
            print("Error cannot build matrix from lines with different lengths")
            exit()

        #Tell user to input a line
        x = input("please enter matrix line or type \"done\" when done: ")

        #If not done split the string and add it to Lgs
        if x != "done":
            y = x.split()
            matrix.append(y)
            allIsDigit = all(p.match(elem)  for elem in matrix[number_of_lines])
            if allIsDigit == False:
                print("Error: Input has non digit parts")
                exit()
            matrix[number_of_lines] = [float(elem) for elem in matrix[number_of_lines]]
            if(matrix[number_of_lines][0] > 0):
                posOneGrtNull = True
            number_of_lines += 1

        #End the loop
        else:
            done = True

    if number_of_lines != number_of_entries_in_line  - 1:
        print("cannot generate matrix: line lenght and number of lines differ")
        exit()

    # if posOneGrtNull == False:
    #     print("cannot be solved: no line with the needed amount of variables")
    #     exit()

    print("== Input end ==")

    return matrix

matrix = getInput()
lgs = Lgs(matrix)
print(lgs.koeffmat)
print(lgs.isthomogen())
print(lgs.istgueltig())
print("test")
lgs.bestimme_loesungsvektor()

print(lgs.lsgvektor)
print(lgs.koeffmat)
