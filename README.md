# Sorthem

A language agnostic tool to visualize your sorting algorithms easily.

Bring your sorting algorithms to life with real-time visualization. Just sort
them.

## Basic operations

- **compare i j**: for comparing to indexes
- **swap i j**: for swapping values at position i and j
- **get i**: for consulting the value at index i
- **set i j**: for consulting the value at index i

## Semantic Colors

- ![#fff](https://placehold.co/15x15/fff/fff.png) `#fff`: an iddle bar
- ![#f00](https://placehold.co/15x15/f00/f00.png) `#f00`: two bars being swaped

  usage: `swap i j`

- ![#0ff](https://placehold.co/15x15/0ff/0ff.png) `#0ff`: looking up the value of a bar

  usage: `get i`

- ![#00f](https://placehold.co/15x15/00f/00f.png) `#00f`: setting the value of a bar

  usage: `set i value`, where `0 < value < max_value`

- ![#0f0](https://placehold.co/15x15/0f0/0f0.png) `#0f0`: two bars are being compared

  usage: `compare i j`

## Notes for the user

- No negative values are supported
