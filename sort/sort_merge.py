# encoding: utf-8

"""
    sort.sort_merge

    ~~~~~~

    使用 python 实现的 merge sort


    compare:
    exchange:

"""

from sort.utils import get_numbers, is_sorted


class MergeSort:
    @staticmethod
    def merge(array, lo, mid, hi):
        left_index = lo
        right_index = mid + 1

        aux_array = array[:]

        for index in range(lo, hi + 1):
            if left_index > mid:
                array[index] = aux_array[right_index]
                right_index += 1

            elif right_index > hi:
                array[index] = aux_array[left_index]
                left_index += 1

            elif aux_array[right_index] > aux_array[left_index]:
                array[index] = aux_array[left_index]
                left_index += 1

            else:
                array[index] = aux_array[right_index]
                right_index += 1

    @staticmethod
    def sort(array, lo=None, hi=None):
        length = len(array)

        if lo is None:
            lo = 0
        if hi is None:
            hi = length - 1

        if lo >= hi:
            return

        mid = (lo + hi) // 2
        MergeSort.sort(array, lo, mid)
        MergeSort.sort(array, mid + 1, hi)
        MergeSort.merge(array, lo, mid, hi)


if __name__ == "__main__":
    numbers = get_numbers()
    print(numbers)
    MergeSort.sort(numbers)
    if is_sorted(numbers):
        print("succeed to sort numbers")
    else:
        print("fail to sort numbers")
    print(numbers)
