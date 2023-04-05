#!/bin/bash

compiler="g++"
flags="-Wall -Wextra -pedantic"
bin_name="sorthem"
build_dir="./dist"
libs="-lsfml-graphics -lsfml-window -lsfml-system"
# if you installed SFML in a non standard path
linker_dir=""
include=""

case "$(uname -s)" in MINGW*)
    # for windows
    SFML_path='C:\SFML-2.5.1'
    include="-I$SFML_path\include"
    linker_dir="-L$SFML_path\lib"
esac

set -e
set -x

units=$(find ./src -name "*.cpp")

mkdir -p $build_dir

for unit in $units; do
    dest=$build_dir/$(basename $unit .cpp).o
    $compiler -c $unit -o $dest $flags $include
done

objs=$(find $build_dir -name "*.o")
$compiler $linker_dir $objs -o $build_dir/$bin_name $flags $libs

if [ "$1" = "run" ]; then
    shift 1
    cmd=$@
    $build_dir/$bin_name "$cmd"
fi
