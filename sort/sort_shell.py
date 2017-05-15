# encoding: utf-8

"""
    sort.sort_shell

    ~~~~~~

    使用 python 实现的 shell sort


    shell sort 基于 insertion sort
    它通过更大的 step 来生成部分排序的数列, 利用了 insertion sort 对已经部分排序的数列的优势

"""

from sort.utils import get_numbers, is_sorted


class ShellSort:
    @staticmethod
    def sort(array):
        length = len(array)
        h = 1
        while h < length // 3:
            h = 3 * h + 1

        while h >= 1:
            for index in range(h, length):
                key = array[index]
                insert_index = index
                for inner_index in range(index - h, -1, -h):
                    inner_key = array[inner_index]
                    if inner_key > key:
                        insert_index = inner_index
                        array[inner_index + h] = inner_key
                    else:
                        break
                array[insert_index] = key
            h //= 3


if __name__ == "__main__":
    numbers = get_numbers()
    print(numbers)
    ShellSort.sort(numbers)
    if is_sorted(numbers):
        print("succeed to sort numbers")
    else:
        print("fail to sort numbers")
    print(numbers)
