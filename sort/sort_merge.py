# encoding: utf-8

"""
    sort.sort_merge

    ~~~~~~

    使用 python 实现的 merge sort


    compare: [0.5 * N * lgN, N * lgN]
    access: 6 * N * lgN

    merge sort 不交换而是复制元素

"""

from sort.utils import get_numbers, is_sorted
from sort.sort_insertion import InsertionSort


class MergeSort:
    @staticmethod
    def merge(array, aux_array, lo, mid, hi):
        left_index = lo
        right_index = mid + 1

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
    def sort(array, aux_array=None, lo=None, hi=None):
        length = len(array)

        if length <= 15:
            InsertionSort.sort(array)
            return

        if lo is None:
            lo = 0
        if hi is None:
            hi = length - 1

        if lo >= hi:
            return

        # 复制 array 到 aux_array
        if aux_array is None:
            aux_array = array[:]

        mid = (lo + hi) // 2

        # 交换 aux_array 和 array, 排序后 aux_array 左右两侧分别为已经排好序的状态
        MergeSort.sort(aux_array, array, lo, mid)
        MergeSort.sort(aux_array, array, mid + 1, hi)

        # 如果 aux_array 左侧和右侧已经完全排好序, 则不用再 merge, 直接把 aux_array 复制到 array
        if aux_array[mid] < aux_array[mid + 1]:
            array[lo:hi+1] = aux_array[lo:hi+1]

        # 否则把 aux_array 已经排好序的左右两侧 merge 到 array
        else:
            MergeSort.merge(array, aux_array, lo, mid, hi)


if __name__ == "__main__":
    numbers = get_numbers()
    print(numbers)
    MergeSort.sort(numbers)
    if is_sorted(numbers):
        print("succeed to sort numbers")
    else:
        print("fail to sort numbers")
    print(numbers)
