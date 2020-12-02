#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
echo "current dir is:" $DIR

rm -rf $DIR/build
rm -f server client
mkdir -p  build
cd $DIR/build
 cmake -DCMAKE_BUILD_TYPE=Release ../
make -j4
cp server ../
cp client ../

echo "Compile Finished"

