# write a program a list of all possible permutations of three numbers
x = int(input())
y = int(input())
z = int(input())
n = int(input())
list1 = [ i for i in range(x + 1)]

list2 = [ j for j in range(y + 1)]
list3 = [ k for k in range(z + 1)]
b = 0
c = 0

print([[i, j, k] for k in list3 for j in list2 for i in list1 if sum([i,j,k]) != n])

'''
x = [[list1[0],list2[0],i] for i in list3]
print(i for i in x if sum(x) != n)

x = [[list1[0], k ,list3[0]] for k in list2]

'''

'''
for i in list1:
    for j in list2:
        for k in list3:
            x = [i,j,k]
            print(x if sum(x) != n else '')
    print(x if sum(x) != n else '')
print(x if sum(x) != n else '')
'''
 

