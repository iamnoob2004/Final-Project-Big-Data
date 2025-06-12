import pandas as pd

df = pd.read_csv('private_data.csv')

n, m = df.shape
name = df.columns.tolist()

print(n, m)
for i in range(n):
	for j in range(m):
		x = df[name[j]][i]
		x = int(x)
		print(x, end = ' ')
	print('')