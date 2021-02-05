#
#   Code is poetry.
#   Created by Nick aka black-dragon74 on 05-FEB-2021
#

# This function is used to print a single based on two params
# Param 1 being the middle element and param 2 being the largest number in pattern
# The forumula to print spaces is relatively simple, it is: max_num - middle_elem
# You can also notice that the number of spaces on each line is symmetrical, so we call the space loop twice
# Also while printing the numbers, we start printing in reverse, coz let's say max_num is 3, then pattern should be
# 12321, notice how it printed in reverse from the max_num until 1. That's it, no rocket science.
def printLineFor(mid_elem, max_num):
    numSpaces = max_num - mid_elem

    # Print leading spaces
    for spaces in range(0, numSpaces):
        print(" ", end="")

    # Print numbers in ascension
    for num in range(0, mid_elem):
        print(num + 1, end="")

        # If last iteration, start printing in reverse
        if num + 1 == mid_elem:
            for rev in range(num, 0, -1):
                print(rev, end="")

    # Print trailing spaces
    for spaces in range(0, numSpaces):
        print(" ", end="")


# This function is the driver fuction for printLineFor function defned above, the reeason for separation of
# Two functions is, you can make the program dynamic, like try with passing 10 as a max_num param to this func
# It will still print a diamond and ajust everything dynamically.
def printDiamondLikePattern(max_num):
    start = 1
    flag = True

    while start <= max_num:
        printLineFor(start, max_num)
        print()

        # If last iter, reverse
        if start == max_num and flag:
            # Unset the flag, forgetting to do this will result in a infinite loop. You figure out why.
            flag = False

            # Start printing the pattern in reverse now, remember we start reversing from max_num - 1
            for revNum in range(max_num - 1, 0, -1):
                printLineFor(revNum, max_num)
                print()

        # As this is not a range based loop, increment the counter
        start += 1


def run():
    printDiamondLikePattern(4)


if __name__ == '__main__':
    run()
