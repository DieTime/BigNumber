import random

random.seed()

f = open("Cases/summation.txt", "w")

for i in range(100):
    length = 1024

    a = random.getrandbits(int(20/6*length))
    sign = random.randint(0, 1)
    if sign == 0:
        a = -a

    b = random.getrandbits(int(20/6*length))
    sign = random.randint(0, 1)
    if sign == 0:
        b = -b

    f.write(str(a) + " " + str(b) + " " + str(a * b) + "\n")

f.close()
print("OK")

