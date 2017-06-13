from algs.utils import numbers, is_sorted


class ShellSort:
    @staticmethod
    def sort(numbers):
        numbers = numbers[:]
        length = len(numbers)
        h = 1
        while h < length // 3:
            h = h * 3 + 1

        while h >= 1:
            for index in range(h, length):
                key = numbers[index]
                insert_index = index
                for inner_index in range(index - h, -1, -h):
                    if numbers[inner_index] > key:
                        numbers[inner_index + h] = numbers[inner_index]
                        insert_index = inner_index
                    else:
                        break
                numbers[insert_index] = key
            h = h // 3

        return numbers


if __name__ == "__main__":
    print(numbers)
    sorted_numbers = ShellSort.sort(numbers)
    print(sorted_numbers)
    print(is_sorted(numbers, sorted_numbers))
