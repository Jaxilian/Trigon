#ifndef APPLICATION_H
#define APPLICATION_H

class Application
{
public:
    static bool s_running;

    virtual void OnConfig() = 0;
    void OnLaunch();
    virtual void OnAwake()  = 0;
    virtual void OnStart()  = 0;
    void PreUpdate();
    virtual void OnUpdate() = 0;
    void PostUpdate();
    virtual void OnQuit() = 0;
    void PostQuit();
};


#endif