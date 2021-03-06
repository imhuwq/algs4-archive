from py_backup.utils import is_sorted, numbers


# class Insertion:
#     n = 0
#
#     @staticmethod
#     def sort(nums):
#         length = len(nums)
#
#         for index in range(1, length):
#             key = nums[index]
#             insert_index = index
#             for inner_index in range(index - 1, -1, -1):
#                 Insertion.n += 1
#                 compared_key = nums[inner_index]
#                 if key < compared_key:
#                     nums[inner_index + 1] = compared_key
#                     insert_index = inner_index
#                 else:
#                     break
#             nums[insert_index] = key
#         return nums


class Insertion:
    n = 0

    @staticmethod
    def sort(nums):
        length = len(nums)
        for outer_index in range(1, length):
            key_index = outer_index
            key = nums[key_index]
            for inner_index in range(outer_index-1, -1, -1):
                compared = nums[inner_index]
                Insertion.n += 1
                if key < compared:
                    nums[inner_index+1] = compared
                    key_index = inner_index
                else:
                    break
            nums[key_index] = key

        return nums

if __name__ == "__main__":
    print(numbers)

    sorted_numbers = Insertion.sort(numbers[:])
    print(sorted_numbers)
    print(is_sorted(numbers, sorted_numbers))
    print(Insertion.n)
