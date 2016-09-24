from __future__ import division, print_function

import itertools as it
from functools import partial

import time


class LED(object):
    def __init__(self, i, r, g, b):
        self.i = i
        self.r = r
        self.g = g
        self.b = b

    def __str__(self):
        return "@{{{},{},{},{}}}".format(self.i, self.r, self.g, self.b)


def screen(i):
    def f(i, j):
        return LED(j, (i*j) % 256, (i+j) % 256, (i%(1+j)) % 256)

    pixels = "@[{}]".format(
        ",".join(
            map(
                str,
                map(
                    partial(f, i),
                    range(40)
                )
            )
        )
    )

    return pixels


def g(i):
    print(screen(i))
    time.sleep(0.1)


if __name__ == "__main__":

    list(map(
        g, it.cycle(range(255))
    ))

