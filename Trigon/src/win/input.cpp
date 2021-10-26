#include "input.h"
#include "win.h"

 bool 
 input::getKey(KeyCode kc)
 {
     return glfwGetKey(win::get(), kc);
 }