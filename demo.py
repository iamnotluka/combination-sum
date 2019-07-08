import time

def createData(input_file):
    use_data = []
    for line in open(input_file).readlines():
        use_data.append([int(x) for x in line.split()])

    return use_data

def generateCandidates(n):
    candidates = []
    size = n+1
    for i in range(1, size):
        candidates.append(i)

    for i in range(2, size):
        for number in range(i+1, size):
            if number%i is 0:
                if number in candidates:
                    candidates.pop(candidates.index(number))

    if n in candidates:
        return candidates[::-1]
    else:
        candidates.append(n)
        return candidates[::-1]

def combinations(candidates, target, index, current, combos, low_bound, up_bound):
    print("Comb:",current, "\nTarget:" ,target, "\nIndex:", index,"\nCandidates:", candidates)
        
    if target <= 0:
        
        if target is 0 and len(current) >= low_bound:
            combos[0] = combos[0] + 1
            
            print("Target is 0, Solution", combos[0], "found, backtrack.")

            return
        
        print("No solution. Backtrack")
        return
    
    if len(current) in range(0, up_bound):
        if index < len(candidates):
            value = candidates[index]
            current.append(value)
            
            print("\n ||")
            print(" ||    add", value)
            print("\  /")
            print(" \/\n")
            
            combinations(candidates, target-value, index, current, combos, low_bound, up_bound)
            
            print("\n ||")
            print(" ||     pop", value)
            print("\  /")
            print(" \/\n")
            
            current.pop()
            combinations(candidates, target, index+1, current, combos, low_bound, up_bound)

    return combos

for line in createData(input("Path: ")):
    print("Press Enter to solve ", line, "?", sep='')
    prompt = input()
    length = len(line)
    
    start = time.time()
    n = line[0]
    candidates = generateCandidates(n)

    if length is 1:
        low_bound = 1
        up_bound = n
    elif length is 2:
        low_bound = line[1]
        up_bound = line[1]
    elif length is 3:
        low_bound = line[1]
        up_bound = line[2]
    else:
        print("Invalid input.")

    timer = time.time()-start
    print("Input:",n,low_bound, up_bound)
    print()
    solution = combinations(candidates, n, 0, [], [0], low_bound, up_bound)
    print("\n input:", n)
    print("  time:", time.time()-start)
    print("result:", solution[0])
    print()
    

a = input()
