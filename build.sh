#!/bin/bash

compiler="g++"
flags="-Wall -Wextra -pedantic"
libs="-lsfml-graphics -lsfml-window -lsfml-system"
bin_name="sorthem"

set -e
set -x

objs=$(find ./src -name "*.cpp")

for obj in $objs; do
    $compiler -c $obj -o ${obj%.cpp}.o $flags
done

objs=$(find ./src -name "*.o")

$compiler $objs -o $bin_name $flags $libs

if [ $1 = "run" ]; then
    ./$bin_name
fi
