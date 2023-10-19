#!/usr/bin/python3

import sys
import socket
import tools


def display_help(ret):
    f = open("./help", "r")
    line = f.readline()
    while line:
        print(line, end='')
        line = f.readline()
    f.close()
    return ret


def check_if_exists(args, index):
    if args[index] is None:
        return False
    else:
        print("Error: Each argument must be unique.\n")
        return display_help(84)


def port(arg, args):
    if check_if_exists(args, 0) == 84:
        return 84
    if not arg.isdigit():
        print("Error: Port must be a positive number.\n")
        return display_help(84)
    args[0] = int(arg)
    return 0


def name(arg, args):
    if check_if_exists(args, 1):
        return 84
    args[1] = arg
    return 0


def machine(arg, args):
    if check_if_exists(args, 2):
        return 84
    try:
        socket.gethostbyname(arg)
    except socket.error:
        tools.print_error("Error: The machine given in argument doesn't exist.")
    args[2] = arg
    return 0


def check_params(args):
    index = 1
    ret = [None] * 3
    func = {"-p": port, "-n": name, "-h": machine}
    if len(args) != 5 and len(args) != 7:
        sys.exit(display_help(84))
    while index <= len(args) - 2:
        if args[index] not in func:
            sys.exit(display_help(84))
        if func[args[index]](args[index + 1], ret) == 84:
            sys.exit(display_help(84))
        index += 2
    if len(args) == 5:
        ret[2] = "localhost"
    for it in ret:
        if it is None:
            sys.exit(display_help(84))
    return ret
