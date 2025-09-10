from concurrent.futures import ThreadPoolExecutor

list = [1, 2, 3, 4, 5, 6]

def square_element(i):
    print(list[i]*list[i])

with ThreadPoolExecutor(3) as executor:
    executor.map(square_element, (0, 1, 2, 3, 4, 5))