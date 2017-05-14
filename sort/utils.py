import random


def gen_numbers():
    with open("numbers.txt", "w") as f:
        for i in range(100000):
            number = random.randint(0, 100000)
            f.writelines(str(number) + "\n")


def get_numbers():
    numbers = []
    with open("numbers.txt", "r") as f:
        lines = f.readlines()
        for line in lines:
            number = int(line)
            numbers.append(number)
    return numbers


def swap(array, index_a, index_b):
    array[index_a], array[index_b] = array[index_b], array[index_a]


if __name__ == "__main__":
    gen_numbers()
