t = 'abc'

def fact(n):
    if n == 1 : return 1
    else: return n * fact(n-1)

def perm(a, res):
    print '[' + str(len(a)) + ']'
    
    if len(a) == 0: 
        pass
    elif len(a) == 1:
        res.append(a)
    elif len(a) == 2:
        res.append(a[::-1])
        res.append(a)
    else:
        for i in xrange(0, len(a)):
            l = []
            c = a[i]
            w = a[0:i] + a[i+1:]
            perm(w, l)
            for x in l:
                res.append(x + c)
    

list1 = []
perm('a', list1)
print list1

list2 = []
perm('ab', list2)
print list2

list3 = []
perm(t, list3)
print list3

bigstr = 'fucksystem'
pro_size = fact(len(bigstr))
print 'problem size =', pro_size
list4 = []
perm(bigstr, list4)
print list4, pro_size == len(list4)
            