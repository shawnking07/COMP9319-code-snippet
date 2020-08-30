input_str = "database$"

vector = []
last = list(input_str)
vector.append(last.copy())
for i in range(len(input_str)-1):
    a = last.pop(-1)
    last.insert(0, a)
    vector.append(last.copy())

vc = sorted(vector, key=lambda a: ''.join(a))
bwt = ''.join([i[-1] for i in vc])
print(bwt)
