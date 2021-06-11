import sys
import random
import string

TEST_COUNT = 8
def get_random_string():
    WORDS = (" cat", " jumble", " easy", " difficult", " answer",  " xylophone")
    length = random.randint(0, 1000)
    random_list = [ random.choice(WORDS) for _ in range(length) ]
    return "".join(random_list)
'''
def get_random_string():
    length = random.randint(0, 16)
    random_list = [ random.choice(string.ascii_letters) for _ in range(length) ]
    return "".join(random_list)
'''
def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <test directory>")
        sys.exit(1)

    test_dir = sys.argv[1]

    lines = [0]
    lines.extend([ 10 ** i for i in range(TEST_COUNT) ])

    for enum, test_count in enumerate(range(1, TEST_COUNT+1)):
        test = []

        line_count = lines[enum]
        for _ in range(line_count):
            value = get_random_string()
            test.append(value)

        test_name = "{}/{:02d}".format(test_dir, test_count)
        with open(f'{test_name}.t', 'w') as ftest:
            for value in test:
                ftest.write(f'{value}\n')
main()