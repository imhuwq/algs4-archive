# encoding: utf-8

"""
    sort.sort_selection

    ~~~~~~

    使用 Python 实现的 selection sort

    compare: N ** 2 / 2
    exchange: N

    要求: 通过 index 快速获取元素

    优势: 交换次数最少
    劣势: 对原始数据的排序状况不敏感, compare 次数最好和最坏情况都是 N ** 2

"""

from sort.utils import get_numbers, swap, is_sorted


class SelectionSort:
    @staticmethod
    def sort(array=None):
        if array is None:
            array = []
        else:
            assert isinstance(array, list)

        length = len(array)

        for index in range(length):
            min_num_index = index
            for inner_index in range(index + 1, length):
                if array[inner_index] < array[min_num_index]:
                    min_num_index = inner_index
            swap(array, index, min_num_index)


if __name__ == "__main__":
    numbers = get_numbers()
    print(numbers)
    SelectionSort.sort(numbers)
    if is_sorted(numbers):
        print(numbers)
    else:
        print("fail to sort numbers")
