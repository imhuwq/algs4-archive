# encoding: utf-8

"""
    sort.sort_insertion

    ~~~~~~

    使用 python 实现的 insertion sort


    compare: 平均[N ** 2 / 4] 最坏[N ** 2 / 2] 最好[N-1]
    exchange: 平均[N ** 2 / 4] 最坏[N ** 2 / 2] 最好[0]

    要求: 通过 index 快速获取元素

    优势: 对部分排序的数列速度更快
    劣势: 更多的交换次数

"""

from sort.utils import get_numbers, is_sorted


class InsertionSort:
    @staticmethod
    def sort(array):
        length = len(array)
        for index in range(1, length):
            key = array[index]
            insert_index = index
            for inner_index in range(index - 1, -1, -1):
                inner_key = array[inner_index]
                if inner_key > key:
                    insert_index = inner_index
                    array[inner_index + 1] = inner_key
                else:
                    break
            array[insert_index] = key


if __name__ == "__main__":
    numbers = get_numbers()
    print(numbers)
    InsertionSort.sort(numbers)
    if is_sorted(numbers):
        print("succeed to sort numbers")
    else:
        print("fail to sort numbers")
    print(numbers)
