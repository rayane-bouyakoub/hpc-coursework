import _thread

list = [1, 2, 3, 4, 5, 6]

def square_element(i):
    print(list[i]*list[i])

for i in range(len(list)):
    _thread.start_new_thread(square_element, (i,))

while 1:
    pass