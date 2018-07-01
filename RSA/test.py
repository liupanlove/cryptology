
ans = []
for i in range(2, 2000):
    flag = 0
    for j in range(2, i):
        if i % j == 0:
            flag = 1
    if flag == 0:
        ans.append(i)

print(ans)
