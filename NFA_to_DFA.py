from FA import Arc
from FA import FA


Q = [('A',),('B',),('C',),('D',),('E',)]
sig = ['a','b']
deltaFunc = [
    Arc('A','B','a'),
    Arc('A','D','b'),
    Arc('B','B','a'),
    Arc('B','C','b'),
    Arc('C','D','a'),
    Arc('C','E','b'),
    Arc('D','D','a'),
    Arc('D','E','b'),
    Arc('E','B','a'),
    Arc('E','C','b'),
]
q0 = ('A',)
F = [('C',),('E',)]

fa1 = FA(Q,sig,deltaFunc,q0,F)

print()
print(fa1.NFA_to_DFA())
print()
print(fa1.NFA_to_RDFA())
print()
print(fa1.DFA_to_RDFA())

Q2 = [('A',),('B',),('C',),('D',),('E',)]
sig2 = ['0','1']
deltaFunc2 = [
    Arc('A','B','0'),
    Arc('A','C','1'),
    Arc('B','B','0'),
    Arc('B','D','1'),
    Arc('C','B','0'),
    Arc('C','C','1'),
    Arc('D','B','0'),
    Arc('D','E','1'),
    Arc('E','B','0'),
    Arc('E','C','1'),
]
q02 = ('A',)
F2 = [('E',)]

fa2 = FA(Q2,sig2,deltaFunc2,q02,F2)

print()
print(fa2)
print()
print(fa2.DFA_to_RDFA())

Q3 = [('A',),('B',),('C',),('D',)]
sig3 = ['a','b']
deltaFunc3 = [
    Arc('A','A','a'),
    Arc('A','B'),
    Arc('A','D'),
    Arc('B','C','a'),
    Arc('C','C','b'),
    Arc('C','D'),
    Arc('D','D','a'),
]
q03 = ('A',)
F3 = [('D',)]

fa3 = FA(Q3,sig3,deltaFunc3,q03,F3)

print()
print(fa3)
print()
print(fa3.NFA_to_DFA())
print()
print(fa3.NFA_to_RDFA())