./premake5 gmake2
make clean
make config=debug
make config=release
(cd ./Trigon/bin/Debug; ./Trigon)
