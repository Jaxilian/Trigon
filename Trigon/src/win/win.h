#ifndef WIN_H
#define WIN_H
#include <vector>

enum KeyCode
{
	KEY_0 = 48, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
	A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	ESCAPE = 256, ENTER, TAB, BACKSPACE, INSERT, DELETE, RIGHT, LEFT, DOWN, UP, PAGE_UP,
	PAGE_DOWN, HOME, END, CAPS_LOCK, SCROLL_LOCK, NUM_LOCK, PAUSE,
	F1 = 290, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F25,
	KEY_PAD_0 = 320, KEY_PAD_1, KEY_PAD_2, KEY_PAD_3, KEY_PAD_4, KEY_PAD_5, KEY_PAD_6, KEY_PAD_7, KEY_PAD_8,
	KEY_PAD_9, KEY_PAD_DECIAMAL, KEY_PAD_DIVIDE, KEY_PAD_MULTIPLY, KEY_PAD_SUBTRACT, KEY_PAD_ADD,
	KEY_PAD_ENTER, KEY_PAD_EQUAL, LEFT_SHIFT = 340, LEFT_CONTROL, LEFT_ALT, LEFT_SUPER, RIGHT_SHIFT, RIGHT_CONTROL,
	RIGHT_ALT, RIGHT_SUPER, MENU, SPACE = 32
};

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
    void* get();

    //requires VkInstance instance & VkSurfaceKHR* surface
    void createSurface(void* instance, void* surface);

    //returns true if the window is ready to be used
    bool isOk();

    //returns the time of session
    double time();

    //update delta time
    void updateDelta();

    //returns delta time
    float deltaTime();

    //get window width
    float getHeight();
    
    //get window height
    float getWidth();

    //returns selected graphics api
    graphicsAPI getGraphicsAPI();
}


namespace input
{
    bool getKey(KeyCode kc);
}
#endif