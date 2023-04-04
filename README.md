# Sorthem

Sorthem is a language-agnostic tool that enables you to visualize **your**
sorting algorithms easily.

## How does it work?

Sorthem is... simple. You have a sorting algorithm, written in **whatever
language you like**. Let's say, a **bubble sort** implementation in **Ruby**:

```ruby
arr = [3, 9, 1, 8, 6, 10, 4, 7, 2, 5]

for i in 0..arr.length - 2 do
    for j in 0..arr.length - i - 2 do
        left = arr[j]
        right = arr[j + 1]

        if left > right
            arr[j], arr[j + 1] = right, left
        end
    end
end
```

Almost all algorithms are made up with [basic operations](#basic-operations)
like comparing two values, swapping them, etc.

Sorthem needs to know two things:

- what are the values you're sorting
- what are the operations you're doing in order to sort those values

An all you need to do is to **print** that information to the standard output.

```ruby
arr = [3, 9, 1, 8, 6, 10, 4, 7, 2, 5]

# Print the array in the format [ 3 9 1 8 6 10 4 7 2 5 ]
puts "[ #{arr.join(' ')} ]"

for i in 0..arr.length - 2 do
    for j in 0..arr.length - i - 2 do
        left = arr[j]
        right = arr[j + 1]

        # Tell Sorthem that you're comparing two values
        puts "compare #{j} #{j + 1}"
        if left > right
            # Tell Sorthem that you're swapping two values
            puts "swap #{j} #{j + 1}"
            arr[j], arr[j + 1] = right, left
        end
    end
end
```

With these three lines of code, you now have a **visualizer** for your
algorithm. You can run it with:

```bash
ruby bubble_sort.rb | sorthem
```

<!-- TODO: add a gif here -->

Note that `compare` isn't actually needed. Only `swap` does the job of sorting
the array. `compare` is simply a helpful operation for visualization.

Of course, there are more types of operations for more **complex** algorithms,
each associated with [semantic color](#semantic-colors).

We have [many examples](./examples/) on many programming languages,
check them out!

## Basic operations

- **compare**: for comparing to indexes

  usage: `compare i j`

- **swap**: for swapping values at position i and j

  usage: `swap i j`

- **get i**: for consulting the value at index i

  usage: `get i`

- **set i j**: for consulting the value at index i

  usage: `set i value`, where `0 <= value <= max_value`

`i` and `j` must be valid zero-based indexes.

## Semantic Colors

- ![#fff](https://placehold.co/15x15/fff/fff.png) `#fff`: an iddle bar
- ![#f00](https://placehold.co/15x15/f00/f00.png) `#f00`: two bars being swaped
- ![#0ff](https://placehold.co/15x15/0ff/0ff.png) `#0ff`: getting the value of the bar
- ![#00f](https://placehold.co/15x15/00f/00f.png) `#00f`: setting the value of the bar
- ![#0f0](https://placehold.co/15x15/0f0/0f0.png) `#0f0`: two bars are being compared
