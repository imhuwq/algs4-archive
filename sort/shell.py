from utils import is_sorted, numbers


# class Shell:
#     n = 0
#
#     @staticmethod
#     def sort(nums):
#         length = len(nums)
#         k = 1
#         while k < length // 3:
#             k = k * 3 + 1
#
#         while k >= 1:
#             for index in range(k, length):  # 这里的步长是 1 不是 k， 这样才能一轮比较后形成 k-th sorted
#                 key = nums[index]
#                 insert_index = index
#                 for inner_index in range(index - k, -1, -k):
#                     Shell.n += 1
#                     compared_key = nums[inner_index]
#                     if key < compared_key:
#                         nums[inner_index + k] = compared_key
#                         insert_index = inner_index
#                     else:
#                         break
#                 nums[insert_index] = key
#             k = k // 3
#
#         return nums


class Shell:
    n = 0

    @staticmethod
    def sort(nums):
        length = len(nums)
        k = 1
        while k < length // 3:
            k = k * 3 + 1

        while k >= 1:
            for outer_index in range(k, length):
                key_index = outer_index
                key = nums[key_index]
                for inner_index in range(outer_index - k, -1, -k):
                    compared = nums[inner_index]
                    Shell.n += 1
                    if key < compared:
                        nums[inner_index + k] = compared
                        key_index = inner_index
                    else:
                        break
                nums[key_index] = key
            k = k // 3

        return nums

if __name__ == "__main__":
    print(numbers)

    sorted_numbers = Shell.sort(numbers[:])
    print(sorted_numbers)
    print(is_sorted(numbers, sorted_numbers))
    print(Shell.n)
