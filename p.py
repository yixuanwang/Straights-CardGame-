import os

suits = ['C', 'D', 'H', 'S']
ranks = ['A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K']

for f in os.listdir('.'):
    if len(f) != 7:
        continue
    s = suits[int(f[0])]
    r = ranks[int(f[2])] if f[2].isdigit() else f[2].upper()
    # print(f, r + s + '.png')
    os.rename(f, r + s + '.png')
