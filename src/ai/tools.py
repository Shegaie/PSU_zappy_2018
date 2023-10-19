#!/usr/bin/python3

import sys
import re


def print_error(str):
    print(str)
    sys.exit(84)


def clean_data(data):
    result = re.search('\'(.*)\'', str(data))
    ret = result.group(1)
    ret = ret.split('\\n')
    ret.remove(ret[-1])
    return ret