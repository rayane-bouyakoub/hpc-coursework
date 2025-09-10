import numpy as np
import time
from concurrent.futures import ThreadPoolExecutor

va = np.random.randint(1,10, 100000)
vb = np.random.randint(1,10, 100000)

def produit_scalaire(thread_id):
    if thread_id == 0:
        return np.dot(va[:50000], vb[:50000])
    else:
        return np.dot(va[50000:], vb[50000:])

with ThreadPoolExecutor(2) as executor:
    f1 = executor.submit(produit_scalaire, 0)
    f2 = executor.submit(produit_scalaire, 1)
    while (f1.done() == False or f2.done() == False): print("Waiting for both threads to finish!")

somme = f1.result() + f2.result()
print(f"Produit scalaire avec parallélisation: {somme}")
print(f"Produit scalaire sans parallélisation: {np.dot(va, vb)}")

