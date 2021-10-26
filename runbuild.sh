./premake5 gmake2
/home/jax/vulkan/1.2.189.0/x86_64/bin/glslc ./Trigon/shaders/simple.vert -o ./Trigon/shaders/simple.vert.spv
/home/jax/vulkan/1.2.189.0/x86_64/bin/glslc ./Trigon/shaders/simple.frag -o ./Trigon/shaders/simple.frag.spv
make config=debug
make config=release
(cd ./Trigon/bin/Debug; ./Trigon)

