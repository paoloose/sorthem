#!/usr/bin/env ruby

# Selection sort implementation

# Note that this is a recursive implementation

# - find the min value in the array, with index i
# - move that min value to the beginning of the array (swap)
# - repeat for the rest, skipping the first (i=1 to i=n-1)

# Since this generates partitions of the array, we need to track
# the depth of the recursion to get the correct index for the
# output.

$depth = 0

def selection_sort(arr)
    size = arr.length
    return arr if size <= 1

    # find the min index
    min_index = 0

    (0...size).each do |i|
        puts "compare #{i + $depth} #{min_index + $depth}"
        if arr[i] < arr[min_index]
            min_index = i
        end
    end

    # move it to the beginning
    puts "swap #{min_index + $depth} #{0 + $depth}"
    arr[0], arr[min_index] = arr[min_index], arr[0]

    # repeat for the rest of the array
    $depth += 1
    arr[0..0] + selection_sort(arr[1..-1])
end

arr = [135, 138, 22, 23, 60, 139, 71, 86, 120, 34, 82, 137, 154, 17, 148, 103, 110, 43, 107, 46, 190, 157, 199, 101, 151, 3, 169, 73, 162, 77, 7, 108, 182, 159, 33, 116, 95, 31, 53, 28, 32, 57, 6, 133, 131, 167, 94, 76, 111, 93, 75, 125, 171, 126, 41, 102, 58, 193, 16, 132, 123, 62, 124, 80, 8, 172, 146, 2, 70, 115, 147, 24, 128, 47, 79, 29, 180, 50, 195, 184, 166, 36, 155, 118, 141, 64, 122, 178, 100, 168, 38, 78, 119, 161, 143, 165, 179, 145, 90, 12, 35, 56, 142, 89, 149, 114, 106, 150, 152, 188, 87, 191, 153, 4, 127, 11, 61, 92, 74, 19, 173, 186, 200, 88, 99, 136, 170, 55, 112, 69, 91, 39, 63, 185, 121, 144, 14, 197, 97, 130, 83, 163, 37, 134, 51, 96, 30, 129, 140, 5, 187, 84, 21, 181, 98, 81, 65, 189, 72, 15, 13, 109, 117, 66, 59, 198, 158, 25, 9, 49, 1, 176, 67, 192, 52, 113, 104, 54, 105, 26, 183, 164, 27, 196, 177, 10, 68, 45, 44, 40, 156, 85, 42, 20, 175, 174, 18, 48, 194, 160]

puts "[ #{arr.join(' ')} ]"

selection_sort(arr)

# if you want to see the output:
# puts "[ #{selection_sort(arr).join(' ')} ]"
