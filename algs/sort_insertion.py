from algs.utils import numbers, is_sorted


class InsertionSort:
    @staticmethod
    def sort(numbers):
        numbers = numbers[:]
        length = len(numbers)
        for index in range(1, length):
            key = numbers[index]
            insert_index = index
            for inner_index in range(index - 1, -1, -1):
                target = numbers[inner_index]
                if key < target:
                    insert_index = inner_index
                    numbers[inner_index + 1] = target
                else:
                    break
            numbers[insert_index] = key
        return numbers


if __name__ == "__main__":
    print(numbers)
    sorted_numbers = InsertionSort.sort(numbers)
    print(sorted_numbers)
    print(is_sorted(numbers, sorted_numbers))
