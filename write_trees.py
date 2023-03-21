import ROOT
import sys, os

WICE = 0
WICG = 0
CIGE = 0

def printTreeInfo(filename):
    global WICE, WICG, CIGE
    file = ROOT.TFile(filename)
    for key in file.GetListOfKeys():
        obj = key.ReadObj()
        if obj.IsA().GetName() == 'TTree':
            tree = obj
            if tree.GetName() == 'WICE': WICE = tree.GetEntries()
            if tree.GetName() == 'WICG': WICG = tree.GetEntries()
            if tree.GetName() == 'CIGE': CIGE = tree.GetEntries()

            print(f'{tree.GetName()}:\t {tree.GetEntries()}')

if __name__ == '__main__':
    filename = sys.argv[1]
    printTreeInfo(filename)
    print(f'\nGamma/Electrons = {round(WICG/WICE,3)}')
    print(f'Electrons, that counted / electrons on cathode = {round(CIGE/WICE,3)}')
