#include "win/win.h"
#include "vk/device.h"
#include "vk/pipeline.h"

#include <iostream>
int main()
{
    std::cout << "=====================================" << std::endl;
    win::createWin();

    vkpipe::createPipe("/home/jax/Wildsoft/Trigon/Trigon/bin/Debug/simple.vert.spv","/home/jax/Wildsoft/Trigon/Trigon/bin/Debug/simple.frag.spv");

    device::create();
  
    win::destroyWin();
    win::release();
    
    return 0;
}