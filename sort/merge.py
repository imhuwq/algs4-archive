from utils import is_sorted, numbers


# class Merge:
#     n = 0
#
#     @staticmethod
#     def merge(nums, aux_nums, start, mid, end):
#         left_index = start
#         right_index = mid + 1
#
#         for index in range(start, end + 1):
#             Merge.n += 1
#             if left_index > mid:
#                 nums[index] = aux_nums[right_index]
#                 right_index += 1
#             elif right_index > end:
#                 nums[index] = aux_nums[left_index]
#                 left_index += 1
#             elif aux_nums[left_index] < aux_nums[right_index]:
#                 nums[index] = aux_nums[left_index]
#                 left_index += 1
#             else:
#                 nums[index] = aux_nums[right_index]
#                 right_index += 1
#
#     @staticmethod
#     def _sort(nums, aux_nums, start, end):
#         if start >= end:
#             return
#
#         mid = (end + start) // 2
#
#         Merge._sort(aux_nums, nums, start, mid)
#         Merge._sort(aux_nums, nums, mid + 1, end)
#
#         if aux_nums[mid] < aux_nums[mid + 1]:
#             nums[start:end + 1] = aux_nums[start:end + 1]
#         else:
#             Merge.merge(nums, aux_nums, start, mid, end)
#
#     @staticmethod
#     def sort(nums):
#         length = len(nums)
#         aux_nums = nums[:]
#
#         Merge._sort(nums, aux_nums, 0, length - 1)
#         return nums


class Merge:
    n = 0

    @staticmethod
    def merge(nums, aux_nums, start, mid, end):
        left_index = start
        right_index = mid + 1

        for index in range(start, end + 1):
            Merge.n += 1
            if left_index > mid:
                nums[index] = aux_nums[right_index]
                right_index += 1
            elif right_index > end:
                nums[index] = aux_nums[left_index]
                left_index += 1
            elif aux_nums[left_index] > aux_nums[right_index]:
                nums[index] = aux_nums[right_index]
                right_index += 1
            else:
                nums[index] = aux_nums[left_index]
                left_index += 1

    @staticmethod
    def _sort(nums, aux_nums, start, end):
        if start >= end:
            return

        mid = (start + end) // 2
        Merge._sort(aux_nums, nums, start, mid)
        Merge._sort(aux_nums, nums, mid + 1, end)

        Merge.n += 1
        if aux_nums[mid] < aux_nums[mid + 1]:
            nums[start:end + 1] = aux_nums[start:end + 1]
        else:
            Merge.merge(nums, aux_nums, start, mid, end)

    @staticmethod
    def sort(nums):
        aux_nums = nums[:]
        start = 0
        end = len(nums) - 1
        Merge._sort(nums, aux_nums, start, end)
        return nums


if __name__ == "__main__":
    print(numbers)

    sorted_numbers = Merge.sort(numbers[:])
    print(sorted_numbers)
    print(is_sorted(numbers, sorted_numbers))
    print(Merge.n)
