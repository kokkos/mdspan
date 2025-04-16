#!/usr/bin/env bash

if [[ $# -lt 1 ]]; then
  echo "Usage: test_install SOURCE_DIRECTORY [BUILD_OR_INSTALL_DIRECTORY]"
  exit 1
fi

examples_dir=$1/examples

set -e

example_build_dir=/tmp/build-mdspan-examples

if [[ -z "$2" ]]; then
  cmake -S $examples_dir -B $example_build_dir
else
  cmake -S $examples_dir -B $example_build_dir -Dmdspan_ROOT=$2
fi
cmake --build $example_build_dir
rm -rf $example_build_dir