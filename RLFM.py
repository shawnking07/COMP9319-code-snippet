def deriveB(L):
    F=sorted(L)

    print(F)

    B = [1]*len(F)
    for i in range(1,len(L)):
        if L[i-1] != L[i]:
            B[i]=1
        else:
            B[i]=0

    print(f"B list: {B}")

    F_p = F.copy()
    B_prime = [0]*len(F)
    count = 1
    current_val = L[0]
    for i in range(1,len(L)):
        if L[i]==current_val:
            count+=1
        else:
            idx=F_p.index(current_val)
            B_prime[idx]=1

            for j in range(idx,idx+count):
                F_p[j]=False

            current_val=L[i]
            count=1
    
    idx=F_p.index(current_val)
    B_prime[idx]=1

    for j in range(idx,idx+count):
        F_p[j]=False

    current_val=L[i]
    count=1

    print(f"B Prime: {B_prime}")

def deriveL(S, B):
    L=[]

    count=-1
    for i in B:
        if i=='1':
            count+=1
        L.append(S[count])
    
    return ''.join(L)


# deriveB("n$rsoocimpse")
L=deriveL('cgc$agagatc','1101011101110011')
print(L)
deriveB(L)