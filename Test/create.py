import random


def div(left, right):
    negative = False
    if left < 0:
        negative = not negative
    if right < 0:
        negative = not negative
    left = abs(left)
    right = abs(right)
    if negative:
        return -(left // right)
    return left // right


random.seed()

f = open("Cases/division.txt", "w")

for i in range(100):
    length = random.randint(1, 4096)
    a = random.getrandbits(int(20 / 6 * length))
    while a == 0:
        a = random.getrandbits(int(20 / 6 * length))
    sign = random.randint(0, 1)
    if sign == 0:
        a = -a

    length = random.randint(1, 4096)
    b = random.getrandbits(int(20 / 6 * length))
    while b == 0:
        b = random.getrandbits(int(20 / 6 * length))
    sign = random.randint(0, 1)
    if sign == 0:
        b = -b

    f.write(str(a) + " " + str(b) + " " + str(div(a, b)) + "\n")

f.close()
print("OK")
