from random import choice

NUMBER = [102, 1000, 10000, 100000, 250000, 500000, 750000, 1000000, 9999900]

length_of_list = len(NUMBER)

def write_n():
    file.write(str(n))

for i in range(length_of_list):
    n = NUMBER[i] + choice(range(-100, 100))
    if (NUMBER[i] == 102):
        with open('test_100.t', 'w') as file:
            write_n()
    elif (NUMBER[i] == 9999900):
        with open(f'test_10000000.t', 'w') as file:
            write_n()
    else:
        with open(f'test_{NUMBER[i]}.t', 'w') as file:
            write_n()