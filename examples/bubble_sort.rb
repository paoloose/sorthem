#!/usr/bin/env ruby

# This is the example provided in the README.md file

# Pssst, instead of doing `swap i j`, try the complex way:
# puts "set #{j} #{arr[j+1]}"
# puts "set #{j+1} #{arr[j]}"

# should be the same, right?

arr = [3, 9, 1, 8, 6, 10, 4, 7, 2, 5]

puts "[ #{arr.join(' ')} ]"

for i in 0..arr.length - 2 do
    for j in 0..arr.length - i - 2 do
        left = arr[j]
        right = arr[j + 1]

        # ⬇️ Here!
        puts "compare #{j} #{j + 1}"
        if left > right
            # ⬇️ And here!
            puts "swap #{j} #{j + 1}"
            arr[j], arr[j + 1] = right, left
        end
    end
end
