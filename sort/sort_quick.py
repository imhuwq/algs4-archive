# encoding: utf-8

"""
    sort.sort_quick

    ~~~~~~

    使用 python 实现的 quick sort

"""

import random

from sort.utils import get_numbers, is_sorted


class QuickSort:
    @staticmethod
    def partition(array, lo, hi):
        head_index = lo + 1
        tail_index = hi
        key = array[lo]

        while True:
            # scan left
            while array[head_index] < key:
                head_index += 1
                if head_index == hi:
                    break

            # scan right
            while array[tail_index] > key:
                tail_index -= 1
                if tail_index == lo:
                    break

            # index crossed
            if tail_index <= head_index:
                break

            # exchange head_index and tail_index, so they are on the right side
            array[head_index], array[tail_index] = array[tail_index], array[head_index]

        # exchange the key and the tail_index
        # tail index is where key belongs to
        array[lo], array[tail_index] = array[tail_index], array[lo]
        return tail_index

    @staticmethod
    def _sort(array, lo, hi):
        if hi <= lo:
            return
        index = QuickSort.partition(array, lo, hi)
        QuickSort._sort(array, lo, index - 1)
        QuickSort._sort(array, index + 1, hi)

    @staticmethod
    def sort(array):
        length = len(array)
        random.shuffle(array)
        QuickSort._sort(array, 0, length - 1)


if __name__ == "__main__":
    numbers = get_numbers()
    print(numbers)
    QuickSort.sort(numbers)
    if is_sorted(numbers):
        print("succeed to sort numbers")
    else:
        print("fail to sort numbers")
    print(numbers)
