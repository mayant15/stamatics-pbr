# A small helper script to render and display the output. I wrote this only for myself, may not work for you.
# Usage: . ./run.sh

cd build
cmake --build .
./bin/pbr
open ./out.png
cd ..

