import random

random.seed()
#
# for j in [1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192]:
#     f = open("Cases/multiplication" + str(j) + ".txt", "w")
#
#     for i in range(1000):
#         length = j#random.randint(1, 20000)
#
#         a = random.getrandbits(int(20/6*length))
#         sign = random.randint(0, 1)
#         if sign == 0:
#             a = -a
#
#         b = random.getrandbits(int(20/6*length))
#         sign = random.randint(0, 1)
#         if sign == 0:
#             b = -b
#
#         f.write(str(a) + " " + str(b) + " " + str(a * b) + "\n")
#
#     print(j)
#     f.close()


f = open("Cases/multiplication.txt", "w")

for i in range(1000):
    length = random.randint(1, 20000)

    a = random.getrandbits(int(20 / 6 * length))
    sign = random.randint(0, 1)
    if sign == 0:
        a = -a

    b = random.getrandbits(int(20 / 6 * length))
    sign = random.randint(0, 1)
    if sign == 0:
        b = -b

    f.write(str(a) + " " + str(b) + " " + str(a * b) + "\n")

f.close()

