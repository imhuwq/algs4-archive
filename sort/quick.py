from random import shuffle

from utils import is_sorted, numbers


# class Quick:
#     n = 0
#
#     @staticmethod
#     def _part(nums, start, end):
#         key = nums[start]
#
#         left_index = start
#         right_index = end + 1
#
#         while True:
#             while True:
#                 Quick.n += 1
#                 left_index += 1
#                 if nums[left_index] > key or left_index == end:
#                     break
#
#             while True:
#                 Quick.n += 1
#                 right_index -= 1
#                 if nums[right_index] < key or right_index == start:
#                     break
#
#             if right_index <= left_index:
#                 break
#
#             nums[left_index], nums[right_index] = nums[right_index], nums[left_index]
#         nums[start], nums[right_index] = nums[right_index], nums[start]
#
#         return right_index
#
#     @staticmethod
#     def _sort(nums, start, end):
#         if start >= end:
#             return
#
#         index = Quick._part(nums, start, end)
#         Quick._sort(nums, start, index)
#         Quick._sort(nums, index + 1, end)
#
#     @staticmethod
#     def sort(nums):
#         length = len(nums)
#         shuffle(nums)
#
#         Quick._sort(nums, 0, length - 1)
#         return nums


class Quick:
    n = 0

    @staticmethod
    def part(nums, start, end):
        part_index = start
        part_value = nums[start]

        head_index = start
        tail_index = end + 1
        while True:
            while True:
                head_index += 1
                if nums[head_index] > part_value or head_index == end:
                    break

            while True:
                tail_index -= 1
                if nums[tail_index] < part_value or tail_index == start:
                    break

            if tail_index <= head_index:
                break

            nums[head_index], nums[tail_index] = nums[tail_index], nums[head_index]

        nums[part_index], nums[tail_index] = nums[tail_index], nums[part_index]

        return tail_index

    @staticmethod
    def _sort(nums, start, end):
        if start >= end:
            return

        part_index = Quick.part(nums, start, end)
        Quick._sort(nums, start, part_index)
        Quick._sort(nums, part_index + 1, end)

    @staticmethod
    def sort(nums):
        length = len(nums)
        shuffle(nums)
        Quick._sort(nums, 0, length - 1)

        return nums


if __name__ == "__main__":
    print(numbers)

    sorted_numbers = Quick.sort(numbers[:])
    print(sorted_numbers)
    print(is_sorted(numbers, sorted_numbers))
    print(Quick.n)
