
input_str = "etbda$saa"

ascii_list = list(range(256))

def mtf(a: str, mylist: list, ans=[]):
    idx=mylist.index(ord(a))
    mylist.insert(0, mylist.pop(idx))
    ans.append(idx)


ans=[]
for i in input_str:
    mtf(i, ascii_list, ans)

print(ans)
