from py_backup.utils import is_sorted, numbers


# class Heap:
#     n = 0
#
#     @staticmethod
#     def sink(nums, index, end):
#         child_index = index * 2
#         while child_index <= end:
#             Heap.n += 2
#             if child_index + 1 <= end and nums[child_index + 1] > nums[child_index]:
#                 child_index += 1
#
#             if nums[child_index] > nums[index]:
#                 nums[index], nums[child_index] = nums[child_index], nums[index]
#                 index = child_index
#                 child_index = index * 2
#             else:
#                 break
#         return nums
#
#     @staticmethod
#     def sort(nums):
#         nums.insert(0, None)
#
#         size = len(nums) - 1
#         for index in range(size // 2, 0, -1):
#             Heap.sink(nums, index, size)
#
#         while size > 1:
#             nums[1], nums[size] = nums[size], nums[1]
#             size -= 1
#             Heap.sink(nums, 1, size)
#
#         nums.pop(0)
#         return nums


class Heap:
    n = 0

    @staticmethod
    def sink(nums, index, end):
        child_index = index * 2
        Heap.n += 2

        while child_index <= end:
            if child_index + 1 <= end and nums[child_index] < nums[child_index + 1]:
                child_index += 1

            if nums[index] < nums[child_index]:
                nums[index], nums[child_index] = nums[child_index], nums[index]
                index = child_index
                child_index = index * 2
            else:
                break

    @staticmethod
    def sort(nums):
        size = len(nums)

        nums.insert(0, None)
        for index in range(size // 2, 0, -1):
            Heap.sink(nums, index, size)

        while size > 1:
            nums[1], nums[size] = nums[size], nums[1]
            size -= 1
            Heap.sink(nums, 1, size)
        nums.pop(0)
        return nums


if __name__ == "__main__":
    print(numbers)

    sorted_numbers = Heap.sort(numbers[:])
    print(sorted_numbers)
    print(is_sorted(numbers, sorted_numbers))
    print(Heap.n)
