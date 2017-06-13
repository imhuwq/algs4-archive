from algs.utils import numbers, is_sorted


class SelectionSort:
    @staticmethod
    def sort(numbers):
        numbers = numbers[:]
        length = len(numbers)
        for i in range(0, length):
            key = i
            for j in range(i + 1, length):
                if numbers[key] > numbers[j]:
                    key = j
            numbers[key], numbers[i] = numbers[i], numbers[key]
        return numbers

if __name__ == "__main__":
    print(numbers)

    sorted_numbers = SelectionSort.sort(numbers)

    print(sorted_numbers)
    print(is_sorted(numbers, sorted_numbers))
