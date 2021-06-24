from typing import Dict

class Arc:
    def __init__(self, S, F, symbol = None):
        self.orient = S  #orientation 우리에게 보이는 상황에는 str이지만, 함수 내부에서는 튜플을 받는다
        self.dest = F  #destination
        self.symbol = symbol # None은 epsilon move
    def __str__(self):
        return f"{self.orient} -> {self.dest}, symbol = {self.symbol}"

class FA:
    def __init__(self, Q : list[tuple], sig : list[str], deltaFunc : list[Arc], q0 : tuple, F : list[tuple]): #input은 모두 튜플 형태
        
        self.Q = set[tuple](Q)
        self.sig = set[str](sig)
        self.deltaFunc = set[Arc](deltaFunc)
        self.q0 = q0
        self.F = set[tuple](F)
        #Q와 sig의 경우 deltaFunc를 보고 알 수 있으나, 경우에 따라 따로 필요한 경우가 존재하여 그냥 따로 설정했다.

    def __str__(self):
        string = f"Q : {self.Q}\nsig : {self.sig}\ndeltaFunc : {[str(func) for func in self.deltaFunc]}\nq0 : {self.q0}\nF : {self.F}"
        return string
    #string 으로 표현한다.

    def _epsilon_Closure(self, state : tuple):
        eps_Closure = list[str](state)

        for stat in eps_Closure:
            for deltF in self.deltaFunc: #deltaFunc 내의 Arc 중에서
                if deltF.orient == stat and deltF.symbol == None: #Q에 대해 epsilon 보고 가는 경우
                    eps_Closure.append(deltF.dest[0])#다음 상태를 eps_Closure에 추가한다.
        return tuple(eps_Closure) #완성된 epsilon closure를 튜플 형태로 돌려준다.

    def NFA_to_DFA(self):
        qp0 = self._epsilon_Closure(self.q0)

        DFA = FA((qp0,),self.sig,(), qp0, ()) # q'0

        tempQ = list(DFA.Q)

        for q in tempQ:
            for sig in DFA.sig:
                dest = set[str]() # q 에서 a를 보고 갈 수 있는 조합
                for state in q:    #q 상태를 구성하는 각각의 상태들에 대하여
                    for df in self.deltaFunc: #q에서 sig = a를 보고 갈 수 있는 조합을 찾는다.
                        if df.orient == state and df.symbol == sig:
                            dest.add(df.dest) #1차적으로 넣는다
                if len(dest) != 0: 
                        #q에서 a를 보고 갈 수 있는 조합이 존재하지 않으면, deltaFunc 도 정의되지 않는 것.    
                        #따라서, 따로 추가하지 않는다.
                    dest = dest.union(self._epsilon_Closure(dest)) # epsilon closure을 찾는다
                    p = tuple(sorted(list(dest)))
                    DFA.Q.add(p) # 만들어진 새로운 상태 p를 DFA의 Q에 추가한다
                    if p not in tempQ:
                        tempQ.append(p)
                    DFA.deltaFunc.add(Arc(q, p, sig))
            
        for q in DFA.Q:
            for state in q: #만들어진 state 안 각각의 state를 의미
                temp = (state,)
                if temp in self.F: #F에 하나라도 속하는 게 있다면
                    DFA.F.add(q)
                    break
        count = 0       #만들어진 상태들을 새롭게 포장한다
        temp = list(DFA.Q)
        for q in temp:
            value = str(count)
            state = (value,)
            
            DFA.Q.discard(q)
            DFA.Q.add(state)

            if q == DFA.q0:
                DFA.q0 = state
            
            if q in DFA.F:
                DFA.F.discard(q)
                DFA.F.add(state)
            
            for df in list(DFA.deltaFunc):
                if q == df.orient:
                    df.orient = value
                if q == df.dest:
                    df.dest = value
            count += 1
        return DFA

    def DFA_to_RDFA(self):
        partitions : list[set[tuple]] = [self.F, self.Q.difference(self.F)]#set으로 초기 상태 생성

        if len(partitions[1]) == 0:
            return self
            #자기 자신이 모두 F이면, 연산이 필요 없음.
        endPartition = False
        lastPartitionTable : Dict[tuple, Dict] = {}#끝나는 상황에서 파티션 테이블을 가져오기 위한 임시 변수

        while not endPartition:
            endPartition = True #partition 발생하면 바로 False로 바꿀 예정
            partitionTable : Dict[tuple, Dict] = {} # 동치류 분할을 위해 만드는 테이블
            
            for q in self.Q:
                partitionTable[q] = {} #sigma에 대한 테이블 생성

            for df in self.deltaFunc:
                stateCount = -1
                for partition in partitions:
                    stateCount += 1
                    if (df.dest,) in partition:
                        partitionTable[(df.orient,)][df.symbol] = stateCount #partition table 나누기

            for partition in partitions:
                tempList = [] #partition에서 나온 놈들에 대하여 저장
                tempPart = list(partition)
                for state in tempPart:
                    for sigma in self.sig:
                        if partitionTable[state].get(sigma) != partitionTable[tempPart[0]].get(sigma):
                            endPartition = False # 분할 되었으므로, partition이 추가로 필요하게 된다
                            partition.discard(state) #상태를 제거한다
                            tempList.append(state)
                for tempState in tempList:
                    tempSet = set()
                    tempSet.add(tempState)
                    for temp in tempList:
                        if tempState != temp:
                            canAdd = True
                            for sigma in self.sig:
                                if partitionTable[tempState].get(sigma) != partitionTable[temp].get(sigma):
                                    canAdd = False
                                    break
                            if canAdd:
                                tempList.remove(temp)
                                tempSet.add(temp)
                    partitions.append(tempSet)
            lastPartitionTable = partitionTable

        #partition이 종결되어, while문 밖으로 나온 상황!
        Q = [(str(a),) for a in range(len(partitions))] #나뉜 파티션의 갯수만큼 새롭게 Q를 정의한다
        sig : set[str] = set() # sigma 설정
        deltaFunc = []
        q0 = 0 # 우선 선언해둠
        F = []
        count = 0
        #partitions.remove(set())
        for partition in partitions:
            orient = str(count)
            #첫번째 값을 0으로 지정했던 것을 기억해보자!
            if self.q0 in partition:
                q0 = (orient,) # q0 생성 코드
            for f in self.F:         # F 생성 코드
                if f in partition:
                    F.append((orient,)) #partition에 F 의 원소가 하나라도 속하면, RDFA의 F로 넣는다
                    break
            for sigma in self.sig:
                dest = lastPartitionTable[list(partition)[0]].get(sigma)
                if dest == None: #정의되지 않은 경우에는 무시한다
                    continue
                deltaFunc.append(Arc(orient,str(dest), sigma))
                sig.add(sigma)# sigma가 실제로 사용되는 경우 넣는다
            count += 1
        return FA(Q,sig,deltaFunc,q0,F)    

    def NFA_to_RDFA(self):
        return self.NFA_to_DFA().DFA_to_RDFA()
