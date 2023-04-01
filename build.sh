#!/bin/bash

compiler="g++"
flags="-Wall -Wextra -pedantic"
libs="-lsfml-graphics -lsfml-window -lsfml-system"
bin_name="sorthem"
build_dir="./dist"

set -e
set -x

units=$(find ./src -name "*.cpp")

mkdir -p $build_dir

for unit in $units; do
    dest=$build_dir/$(basename $unit .cpp).o
    $compiler -c $unit -o $dest $flags
done

objs=$(find $build_dir -name "*.o")
$compiler $objs -o $build_dir/$bin_name $flags $libs

if [ $1 = "run" ]; then
    ./$build_dir/$bin_name
fi
