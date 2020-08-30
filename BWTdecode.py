L = "arbbr$aa"

F = sorted(L)

count = [0] * len(L)
count_dict = {}
for i in range(len(L)):
    count_dict[L[i]] = count_dict.setdefault(L[i], 0) + 1
    count[i] = count_dict[L[i]] - 1

S = []
idx = 0
for i in range(len(L)):
    S.append(L[idx])
    idx = F.index(L[idx]) + count[idx]

S.reverse()
S = ''.join(S)

print(S)
