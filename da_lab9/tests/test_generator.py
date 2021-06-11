from random import randint

NUMBER = [5, 500, 1000, 1500, 2000, 2500, 3000]

length_of_list = len(NUMBER)

for i in range(length_of_list):
    start = 1
    end = NUMBER[i]
    from_vertex = 1
    to_vertex = 1
    max_weight = 20

    with open(f'test_{NUMBER[i]}.t', "w+") as file:
        file.write(f'{end} {end * end}\n')
        for i in range(1, end * end):
            from_vertex = randint(start, end)
            to_vertex = randint(start, end)
            w = randint(1, max_weight)
            while from_vertex >= to_vertex:
                from_vertex = randint(start, end)
                to_vertex = randint(start, end)
            file.write(f'{from_vertex} {to_vertex} {w}\n')