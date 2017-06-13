from algs.utils import numbers, is_sorted


class Heap:
    def __init__(self, numbers):
        self._numbers = [None] + numbers
        self.size = len(numbers)
        self.heapify()

    def heapify(self):
        for i in range(self.size // 2, 0, -1):
            self.sink(i)

    def sink(self, index, length=None):
        if length is None:
            length = self.size

        child_index = index * 2
        while child_index <= length:
            if child_index + 1 <= length and self._numbers[child_index] < self._numbers[child_index + 1]:
                child_index += 1

            if self._numbers[index] < self._numbers[child_index]:
                self._numbers[child_index], self._numbers[index] = self._numbers[index], self._numbers[child_index]
                index = child_index
                child_index = index * 2
            else:
                break

    def sort(self):
        length = self.size
        while length > 1:
            self._numbers[length], self._numbers[1] = self._numbers[1], self._numbers[length]
            length -= 1
            self.sink(1, length)
        self._numbers.pop(0)
        return self._numbers

    def __repr__(self):
        return "{0}".format(self._numbers)


if __name__ == "__main__":
    print(numbers)
    heap = Heap(numbers)
    print(heap)
    print(is_sorted(numbers, heap.sort()))
