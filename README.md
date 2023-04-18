# Sorthem

Sorthem is a language-agnostic tool that enables you to visualize **your**
sorting algorithms easily.

## How does it work?

Sorthem is simple. You have a sorting algorithm, written in **whatever
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

- **swap**: for swapping the values of two indexes

  usage: `swap i j`

- **get**: for consulting the value at some index

  usage: `get i`

- **set**: for setting an index to a value

  usage: `set i value`, where `0 <= value <= max_value`

`i` and `j` must be valid zero-based indexes.

## Semantic Colors

- ![#ffffff](https://placehold.co/15x15/ffffff/ffffff.png) `#ffffff`: an iddle bar
- ![#f33232](https://placehold.co/15x15/f33232/f33232.png) `#f33232`: two bars being swaped
- ![#9b54c3](https://placehold.co/15x15/9b54c3/9b54c3.png) `#9b54c3`: getting the value of the bar
- ![#2d43db](https://placehold.co/15x15/2d43db/2d43db.png) `#2d43db`: setting the value of the bar
- ![#e79933](https://placehold.co/15x15/e79933/e79933.png) `#e79933`: two bars are being compared
