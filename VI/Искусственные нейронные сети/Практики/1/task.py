import socket
import re
import copy

# вычисление
def seti(addr, mask):
    d = {}
    ip = list(map(int, addr.split(".")))
    mask = list(map(int, mask.split(".")))
    invmask = [abs(i-255) for i in mask]
    d['network'] = ".".join(str(i & j) for i, j in zip(mask, ip))
    d['bcast'] = ".".join(str(i | j) for i, j in zip(invmask, ip))
    return d

# ввод ip
while True:
    addr = input('ip: ')
    try:
        if len(addr) == 15 and socket.inet_aton(addr):
            break
    except socket.error:
        print('Incorrect ip')
    else:
        print('Incorrect ip')

# ввод маски
while True:
    f = 1
    mask = input('mask: ')
    msk = copy.deepcopy(mask)
    if len(mask) != 15 or not re.findall(r'(\d{3}.){3}\d{3}', mask):
        print('Incorrect subnet mask')
        continue
    mask = list(map(int, mask.split(".")))
    mask = ''.join([bin(i)[2:] for i in mask])
    for i in range(1, len(mask)):
        if mask[i] > mask[i-1]:
            f = 0
    if f == 1:
        break
    else:
        print('Incorrect subnet mask')
        continue

# вывод
d = seti(addr, msk)
for k, v in d.items():
    print(f'{k}: {v}')