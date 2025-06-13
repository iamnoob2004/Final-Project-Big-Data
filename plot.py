import matplotlib.pyplot as plt

n, m = map(int,input().split())

vals = [[] for i in range(m)]

for i in range(n):
	arr = list(input().split())
	msk = 0
	for j in range(m - 1):
		if float(arr[j + 1]) > 0.01:
			msk |= 1 << j;
	if msk == 15:
		for j in range(m - 1):
			vals[j].append(float(arr[j + 1]))


plt.scatter(vals[0], vals[1], s=1)
plt.xlabel("0")
plt.ylabel("1")
plt.grid(True)
plt.tight_layout()
plt.savefig("public_mask_15_01.png")
plt.show()


plt.scatter(vals[1], vals[2], s=1)
plt.xlabel("1")
plt.ylabel("2")
plt.grid(True)
plt.tight_layout()
plt.savefig("public_mask_15_12.png")
plt.show()


plt.scatter(vals[2], vals[3], s=1)
plt.xlabel("2")
plt.ylabel("3")
plt.grid(True)
plt.tight_layout()
plt.savefig("public_mask_15_23.png")
plt.show()