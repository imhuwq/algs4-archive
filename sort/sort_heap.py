# encoding: utf-8

"""
    sort.sort_heap

    ~~~~~~

    使用 python 实现的 heap_sort

    获取最大值和插入值并保持顺序都要求 lgN 的操作

"""

from sort.utils import get_numbers


class Heap:
    def __init__(self, data):
        assert isinstance(data, list)
        self._data = [None]
        self.size = 0
        for number in data:
            self._data.append(number)
            self.size += 1
            self.swim(self.size)

    def sink(self, number_index):
        while number_index * 2 <= self.size:
            new_parent_index = number_index * 2
            if new_parent_index < self.size and self._data[new_parent_index] < self._data[new_parent_index + 1]:
                new_parent_index += 1

            if self._data[number_index] < self._data[new_parent_index]:
                self._data[number_index], self._data[new_parent_index] = self._data[new_parent_index], self._data[
                    number_index]
                number_index = new_parent_index
            else:
                break

    def swim(self, number_index):
        while number_index > 1 and self._data[number_index // 2] < self._data[number_index]:
            self._data[number_index // 2], self._data[number_index] = self._data[number_index], self._data[
                number_index // 2]
            number_index //= 2

    @property
    def max(self):
        return self._data[1]

    def pop_max(self):
        if self.size < 1:
            return None
        rv = self._data[1]
        self._data[1] = self._data[-1]
        self.sink(1)
        return rv

    def push(self, number):
        self._data.append(number)
        self.size += 1
        self.swim(self.size)

    def __repr__(self):
        return "%s" % self._data[1:]


if __name__ == "__main__":
    numbers = get_numbers()
    print(numbers)
    heap = Heap(numbers)
    print(heap)
    print(heap.pop_max())
    print(heap)
    heap.push(1000000)
    print(heap)
