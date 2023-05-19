#!/bin/bash

compiler="g++"
flag_mode=$(if [ "$1" = "debug" ]; then echo "-g -DDEBUG"; else echo "-O3"; fi)
flags="-Wall -Wextra -pedantic -std=c++17 $flag_mode"
bin_name="sorthem"
build_dir="./dist"
libs="-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio"
# if you installed SFML in a non standard path
linker_dir=""
include="-I./src/include"

case "$(uname -s)" in MINGW*)
    # for windows
    SFML_path='C:\SFML-2.5.1'
    include="$include -I$SFML_path\include"
    linker_dir="-L$SFML_path\lib"
esac

units=$(find ./src -name "*.cpp")

set -e
set -x

mkdir -p $build_dir
rm -rf $build_dir/*

for unit in $units; do
    dest=$build_dir/$(basename $unit .cpp).o
    $compiler -c $unit -o $dest $include $flags
done

objs=$(find $build_dir -name "*.o")
$compiler $linker_dir $objs -o $build_dir/$bin_name $flags $libs

if [ "$1" = "run" ]; then
    $build_dir/$bin_name
fi
