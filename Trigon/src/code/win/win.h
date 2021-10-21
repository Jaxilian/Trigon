#ifndef WIN_H
#define WIN_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>

namespace win
{
    typedef void (*winCB)(int x, int y);

    enum mode
    {
        fullscreen,
        borderless,
        windowed
    };

    enum graphicsAPI
    {
        OpenGL,
        OpenGLES,
        Vulkan
    };


    //create window from current settings
    void createWin();

    //destroy active window
    void destroyWin();

    //release everything around window
    void release();

    //set window title name
    void setName(const char* name);

    //poll events from window
    void poll();

    //swap image buffer
    void swap();

    //set window width and height
    void setSize(int width, int height);

    //set random function as callback when window resizes
    void setCallback(winCB cb);

    //set window mode, such as windowed/fullscreen etc
    void setMode(mode m);

    //set target graphics api, example vulkan
    void setGraphicsAPI(graphicsAPI api);

    //set window MSAA samples, 2/4/16 x MSAA 
    void setWinSamples(int samples);

    //destroy and create window
    void recreateWin();

    //if client pressed the close button of the window
    bool shouldQuit();

    std::vector<const char *> getRequiredExtensions();

    //check if glfw extensions are available for vulkan
    void getVkExtensions();

    //returns handle to window
    GLFWwindow* getHandle();

    void createSurface(VkInstance instance, VkSurfaceKHR* surface);

    //returns true if the window is ready to be used
    bool isOk();
}
#endif