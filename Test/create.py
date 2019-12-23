import random
from decimal import *

random.seed()
f = open("Cases/10000000digits.txt", "w")

a = "6123809001"
l = []
for i in range(1000000):
    l.append(a)
str = ''.join(l)
f.write(str)
f.close()

print("OK!")