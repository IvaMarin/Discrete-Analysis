from random import choice

NUMBER_OF_LINES = [100, 1000, 10000, 100000, 250000, 500000, 750000, 1000000, 10000000]

length_of_list = len(NUMBER_OF_LINES)

for j in range(length_of_list):
    with open(f'test_{NUMBER_OF_LINES[j]}.t', 'w') as file:
        file.write(str(NUMBER_OF_LINES[j]) + '\n')
        for i in range(0, NUMBER_OF_LINES[j]):
            l = choice(range(-1000, 1000))
            r = l + (choice(range(1, 10)))
            file.write(str(l) + ' ' + str(r) +'\n')
        file.write(str(choice(range(1000))))