import math
from concurrent.futures import ThreadPoolExecutor

PREMS=[
112272535095293,
112582705942171,
112272535095293,
115280095190773,
115797848077099,
1099726899285419]

def est_prem(nb):
    if nb % 2 == 0: return False
    racine = int(math.floor(math.sqrt(nb)))
    for i in range(3, racine + 1, 2):
        if nb % i == 0: return False
    return True

def main():
    with ThreadPoolExecutor(6) as executor:
        results = list(executor.map(est_prem, PREMS))
        for i in range(len(results)):
            print(f'Le nombre {PREMS[i]} est premier ? {results[i]}')

if __name__ == '__main__': 
    main()