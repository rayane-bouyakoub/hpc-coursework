import numpy as np
from time import time
import time
from concurrent.futures import ThreadPoolExecutor

#200000

np.random.RandomState(100)
arr = np.random.randint(0, 10, size=[200000, 5])
data = arr.tolist()
print(data[:5])

def howmany_within_range(rows, minimum, maximum):
    results = []
    for row in rows:
        count = 0
        for n in row:
            if minimum <= n <= maximum:
                count = count + 1
        results.append(count)
    return results

def howmany_within_range_2(row, minimum, maximum):
    count = 0
    for n in row:
        if minimum <= n <= maximum:
            count = count + 1
    return count

with ThreadPoolExecutor(5) as executor:
    f1 = executor.submit(howmany_within_range, data[0:40000], 4, 8)
    f2 = executor.submit(howmany_within_range, data[40000:80000], 4, 8)
    f3 = executor.submit(howmany_within_range, data[80000:120000], 4, 8)
    f4 = executor.submit(howmany_within_range, data[120000:160000], 4, 8)
    f5 = executor.submit(howmany_within_range, data[160000:200000], 4, 8)
    while (f1.done() == False or f2.done() == False or f3.done() == False or f4.done() == False or f5.done() == False): print("Waiting for one of the threads to finish!")
    results = f1.result() + f2.result() + f3.result() + f4.result() + f5.result()
    print(f"Results with parallelization: {results[:10]}")

results = []
for row in data:
    results.append(howmany_within_range_2(row, minimum=4, maximum=8))
print(f"Results without parallelization: {results[:10]}")