# !/usr/bin/python3

import sys
import socket
import re
from copy import deepcopy
import tools
import elevation
import random
import time

keys = ['food', 'linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame']
blacklist = ['food', 'player']


def merge_dicts(dict1, dict2):
    ret = {}
    for key in dict1:
        ret[key] = int(dict1[key]) + int(dict2[key])
    return ret


def remove_key(obj):
    withoutKey = deepcopy(obj)
    for key in blacklist:
        if key in withoutKey:
            del withoutKey[key]
    return withoutKey


def get_array_from_look(str):
    obj = {'player': 0, 'food': 0, 'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0,
           'thystame': 0}
    arr = str.strip().split(' ')

    for key in obj:
        obj[key] = arr.count(key)
    return obj


def compare_minerals(to_check, to_have):
    keys = ['linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame']

    for key in keys:
        if int(to_check[key]) >= int(to_have[key]):
            continue
        else:
            return key
    return True


class Drone():
    port = 0
    host = "localhost"
    team = ""
    sock = ""
    map = []
    lvl = 1
    bc = 0

    def __init__(self, port, host, team):
        self.port = port
        self.host = host
        self.team = team

    def connect_client(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.sock.connect((self.host, self.port))
        except socket.error:
            tools.print_error("Error: Connection to the server refused.")
        self.receive()

    def chose_team(self):
        self.send(self.team + '\n')
        data = self.receive()
        if data[0] == 'ko':
            tools.print_error("Error: Team " + self.team + " doesn't exist.")
        elif data[0] == '0':
            tools.print_error("Error: Team " + self.team + " is currently full.")
        else:
            self.map = data[1].split(' ')

    def disconnect_client(self):
        self.sock.close()

    def rcv_broadcast(self, data):
        data = data.replace(',', '').replace('\n', '').split(' ')
        dir = int(data[1]) - 1
        msg = ' '.join(data[2:])
        moves = [["Forward\n"], ["Forward\n", "Left\n", "Forward\n"],
                 ["Left\n", "Forward\n"], ["Left\n", "Forward\n", "Left\n", "Forward\n"],
                 ["Left\n", "Left\n", "Forward\n"], ["Right\n", "Forward\n", "Right\n", "Forward\n"],
                 ["Right\n", "Forward\n"], ["Forward\n", "Right\n", "Forward\n"]]
        move = moves[dir]

        if int(msg) != self.lvl:
            return
        for command in move:
            self.send(command)
            var = self.receive()[0]

    def send(self, message):
        self.sock.sendto(message.encode(), (self.host, self.port))

    def receive(self):
        ret = tools.clean_data(self.sock.recv(1024))
        if len(ret) == 0 or ret[0] == "dead":
            self.disconnect_client()
            sys.exit(0)
        while ret[0].find('message') != -1:
            self.rcv_broadcast(ret[0])
            ret = tools.clean_data(self.sock.recv(1024))
        return ret

    def inventory(self):
        index = 0
        ret = []
        obj = {'food': 0, 'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0,
               'thystame': 0}

        self.send("Inventory\n")
        res = self.receive()[0]
        if res == 'ko':
            return
        clean = res[res.find("[ ") + 1:res.find(" ]")].split(',')
        for i in clean:
            clean[index] = i.strip()
            ret.append(clean[index].split(' ')[1])
            index += 1
        for counter, value in enumerate(ret):
            obj[keys[counter]] = value
        return obj

    def look_around(self):
        ret = []

        self.send("Look\n")
        res = self.receive()[0]

        clean = res[res.find("[ ") + 1:res.find(" ]")].split(',')
        for it in clean:
            ret.append(get_array_from_look(it))
        return ret

    def incantation(self):
        self.send("Incantation\n")
        res = self.receive()[0]
        if res == 'ko':
            res = self.receive()[0]
            return False
        else:
            res = self.receive()[0]
            if res == 'ko':
                return False
            else:
                self.lvl = int(res.split(':')[1].strip())
                return True

    def take_objects(self, around, inventory):
        inv = deepcopy(inventory)

        for key in around[0]:
            if key == 'player':
                continue
            self.send('Take ' + key + '\n')
            while self.receive()[0] != "ko" and int(inv[key]) <= 1:
                self.send('Take ' + key + '\n')
                obj = int(inv[key])
                obj += 1
                inv[key] = str(obj)

    def set_objects(self, inventory):
        for stone in inventory:
            if int(inventory[stone]) > 0:
                self.set_down(stone)

    def take(self, obj):
        self.send("Take " + obj + "\n")
        res = self.receive()[0]
        if res == 'ko':
            return False
        else:
            return True

    def set_down(self, obj):
        self.send("Set " + obj + "\n")
        res = self.receive()[0]
        if res == 'ko':
            return False
        else:
            return True

    def broadcast(self):
        if self.bc > 65:
            to_send = "Broadcast " + str(self.lvl) + "\n"
            self.send(to_send)
            var = self.receive()[0]
            self.bc = 0
        else:
            self.bc += 1
            return

    def fork(self):
        self.send("Fork\n")
        var = self.receive()[0]

    def move(self, miss, around):
        moves = [["Forward\n", "Left\n", "Forward\n"], ["Forward\n"], ["Forward\n", "Right\n", "Forward\n"]]
        index = 0

        for place in around[1:4]:
            if miss != True and int(place[miss]) > 0:
                for command in moves[index]:
                    if int(place['food']) > 0:
                        self.take('food')
                    self.send(command)
                    var = self.receive()[0]
                return
            index += 1
        index = random.randint(0, 2)
        for command in moves[index]:
            self.send(command)
            var = self.receive()[0]
        return

    def check_incantation(self, inventory, around, requirements):
        floor = remove_key(around[0])
        own = remove_key(inventory)
        need = remove_key(requirements)
        merged = compare_minerals(merge_dicts(own, floor), need)

        if merged == True:
            if int(requirements['player']) > int(around[0]['player']):
                if int(inventory['food']) < 6 and int(around[0]['food']) == 0:
                    self.take_objects(around, inventory)
                    self.move(merged, around)
                self.broadcast()
                return
            self.set_objects(own)
            self.incantation()
            self.fork()
            self.take_objects(around, inventory)
        else:
            self.take_objects(around, inventory)
            self.move(merged, around)

    def launch_ai(self):
        while 1:
            requirements = elevation.getRequirements(self.lvl)
            inventory = self.inventory()
            around = self.look_around()

            if int(around[0]['food']) > 0:
                self.take('food')
            self.check_incantation(inventory, around, requirements)

    def run(self):
        self.connect_client()
        self.chose_team()
        self.launch_ai()
        self.disconnect_client()
