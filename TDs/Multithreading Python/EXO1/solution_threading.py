import threading

list = [1, 2, 3, 4, 5, 6]

def square_element(i):
    print(list[i]*list[i])

for i in range(len(list)):
    t = threading.Thread(target = square_element, args=(i,))
    t.start()
    t.join()