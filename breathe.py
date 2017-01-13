#!/usr/bin/env python3

import math

N = 128
period = (1 << 13)

print("const u32 breathe[] = {")

for i in range(N):
    a = math.pi * i / N
    s = math.sin(a)
    t = int(period * s)
    # print(i, a, s, t)
    print("{},".format(t))

for i in range(N):
    print("{},".format(0))

print("};")
