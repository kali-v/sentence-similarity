import matplotlib.pyplot as plt

data = [
    (10000, 124135),
    (100000, 1055063),
    (1000000, 7660988),
    (5000000, 39631455),
    (25000000, 206878580)
]

keys = [k for k, _ in data]
values = [v for _, v in data]

plt.figure(figsize=[10, 5])
plt.loglog(keys, values, 'o-', label='dist-1')
plt.loglog(keys, [(k / keys[0]) * values[0] for k in keys], 'r--', label='linear')

plt.grid(True)
plt.xlabel('num of sentence ')
plt.ylabel('execution time')
plt.legend()
plt.show()
