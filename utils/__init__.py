import random
from collections import Counter
from itertools import tee
from operator import le


def gen_numbers():
    nums = []
    for i in range(1000):
        nums.append(random.randint(1, 10000))
    return nums


def has_the_same_items(origin_numbers, sorted_numbers):
    return Counter(origin_numbers) == Counter(sorted_numbers)


def is_sorted(origin_numbers, sorted_numbers):
    a, b = tee(sorted_numbers)
    next(b, None)
    if has_the_same_items(origin_numbers, sorted_numbers):
        return all(map(le, a, b)), "has the same items"
    else:
        return all(map(le, a, b)), "does not have the same items"


numbers = gen_numbers()
