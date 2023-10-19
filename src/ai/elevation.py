# !/usr/bin/python3

levels = [
        [1, 1, 0, 0, 0, 0, 0],
        [2, 1, 1, 1, 0, 0, 0],
        [2, 2, 0, 1, 0, 2, 0],
        [4, 1, 1, 2, 0, 1, 0],
        [4, 1, 2, 1, 3, 0, 0],
        [6, 1, 2, 3, 0, 1, 0],
        [6, 2, 2, 2, 2, 2, 1]
    ]
keys = ['player', 'linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame']


def getRequirements(current_lvl):
    obj = {'player': 0, 'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0,
           'thystame': 0}

    for counter, value in enumerate(levels[current_lvl - 1]):
        obj[keys[counter]] = value
    return obj
