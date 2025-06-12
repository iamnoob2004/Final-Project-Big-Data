import pandas as pd

n, m = map(int, input().split())

data = []

label = [-1 for i in range(n + 1)]

for i in range(n):
	arr = list(input().split())
	x, y = int(arr[0]), int(arr[1])
	label[x] = y

for i in range(1, n + 1):
	row = dict()
	row['id'] = i;
	row['label'] = label[i]
	data.append(row)

df = pd.DataFrame(data)
keys = ['id', 'label']
df = df[keys]
df.to_csv('output.csv', index = False)