from utils import is_sorted, numbers


# class Selection:
#     n = 0
#
#     @staticmethod
#     def sort(nums):
#         length = len(nums)
#         for index in range(length):
#             key_index = index
#             key = nums[index]
#             for inner_index in range(index + 1, length):
#                 Selection.n += 1
#                 compared_key = nums[inner_index]
#                 if key > compared_key:
#                     key_index = inner_index
#                     key = compared_key
#             nums[index], nums[key_index] = nums[key_index], nums[index]
#         return nums


class Selection:
    n = 0

    @staticmethod
    def sort(nums):
        length = len(nums)
        for outer_index in range(length):
            key_index = outer_index
            key = nums[key_index]
            for inner_index in range(outer_index + 1, length):
                compared = nums[inner_index]
                Selection.n += 1
                if key > compared:
                    key_index = inner_index
                    key = nums[key_index]
            nums[outer_index], nums[key_index] = nums[key_index], nums[outer_index]

        return nums


if __name__ == "__main__":
    print(numbers)

    sorted_numbers = Selection.sort(numbers[:])
    print(sorted_numbers)
    print(is_sorted(numbers, sorted_numbers))
    print(Selection.n)
