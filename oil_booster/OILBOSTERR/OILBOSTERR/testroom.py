import matplotlib.pyplot as plt


input_txt = 'room1.txt'
x = []
y = []
z = []

f = open(input_txt)
for line in f:
    line = line.strip('\n')
    line = line.split(' ')

    x.append(int(line[0]))
    y.append(int(line[1]))

f.close

input_txt = 'room2.txt'
f = open(input_txt)
for line in f:
    line = line.strip('\n')
    line = line.split(' ')

    z.append(int(line[1]))

f.close

plt.plot(x, y, marker='o', label='backtrack')
plt.plot(x, z, marker='*', label='branch_bound',linestyle="--")


plt.xticks(x[0:len(x):2], x[0:len(x):2], rotation=45)
plt.margins(0)
plt.xlabel("data")
plt.ylabel("cost(Byte)")
plt.title("compare roomspace")
plt.tick_params(axis="both")
plt.legend()
plt.show()
