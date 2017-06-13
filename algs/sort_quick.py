from algs.utils import numbers, is_sorted


class QuickSort:
    @staticmethod
    def part(numbers, lo, hi):
        key = numbers[lo]

        head_index = lo
        tail_index = hi + 1

        while True:

            while True:
                head_index += 1
                if numbers[head_index] > key:
                    break
                if head_index == hi:
                    break

            while True:
                tail_index -= 1
                if numbers[tail_index] < key:
                    break
                if tail_index == lo:
                    break

            if tail_index <= head_index:
                break

            numbers[head_index], numbers[tail_index] = numbers[tail_index], numbers[head_index]

        numbers[lo], numbers[tail_index] = numbers[tail_index], numbers[lo]
        return tail_index

    @staticmethod
    def _sort(numbers, lo, hi):
        if hi <= lo:
            return

        index = QuickSort.part(numbers, lo, hi)
        QuickSort._sort(numbers, lo, index - 1)
        QuickSort._sort(numbers, index + 1, hi)

    @staticmethod
    def sort(numbers):
        numbers = numbers[:]

        length = len(numbers)
        QuickSort._sort(numbers, 0, length - 1)

        return numbers


if __name__ == "__main__":
    print(numbers)
    sorted_numbers = QuickSort.sort(numbers)
    print(sorted_numbers)
    print(is_sorted(numbers, sorted_numbers))
