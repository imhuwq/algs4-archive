from algs.utils import numbers, is_sorted


class MergeSort:
    @staticmethod
    def merge(numbers, aux_numbers, lo, mid, hi):
        left_index = lo
        right_index = mid + 1

        for index in range(lo, hi + 1):
            if left_index > mid:
                numbers[index] = aux_numbers[right_index]
                right_index += 1

            elif right_index > hi:
                numbers[index] = aux_numbers[left_index]
                left_index += 1

            elif aux_numbers[left_index] < aux_numbers[right_index]:
                numbers[index] = aux_numbers[left_index]
                left_index += 1

            else:
                numbers[index] = aux_numbers[right_index]
                right_index += 1

    @staticmethod
    def _sort(numbers, aux_numbers, lo, hi):
        if lo >= hi:
            return
        mid = (lo + hi) // 2

        MergeSort._sort(aux_numbers, numbers, lo, mid)
        MergeSort._sort(aux_numbers, numbers, mid + 1, hi)

        if aux_numbers[mid] < aux_numbers[mid + 1]:
            numbers[lo:hi + 1] = aux_numbers[lo:hi + 1]
        else:
            MergeSort.merge(numbers, aux_numbers, lo, mid, hi)

    @staticmethod
    def sort(numbers):
        numbers = numbers[:]
        aux_numbers = numbers[:]

        length = len(numbers)

        MergeSort._sort(numbers, aux_numbers, 0, length - 1)

        return numbers


class MergeUpSort:
    @staticmethod
    def merge(numbers, lo, mid, hi):
        left_index = lo
        right_index = mid + 1

        aux_array = numbers[:]
        for index in range(lo, hi + 1):
            if left_index > mid:
                numbers[index] = aux_array[right_index]
                right_index += 1
            elif right_index > hi:
                numbers[index] = aux_array[left_index]
                left_index += 1
            elif aux_array[right_index] > aux_array[left_index]:
                numbers[index] = aux_array[left_index]
                left_index += 1
            else:
                numbers[index] = aux_array[right_index]
                right_index += 1

    @staticmethod
    def sort(numbers):
        numbers = numbers[:]

        length = len(numbers)

        size = 1
        while size < length:
            lo = 0
            while lo < length - size:
                mid = lo + size - 1
                hi = min(mid + size, length - 1)
                MergeUpSort.merge(numbers, lo, mid, hi)

                lo += size * 2

            size *= 2

        return numbers


if __name__ == "__main__":
    print(numbers)
    sorted_numbers = MergeUpSort.sort(numbers)
    print(sorted_numbers)
    print(sorted(numbers))
    print(is_sorted(numbers, sorted_numbers))
