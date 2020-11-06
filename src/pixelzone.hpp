#ifndef __graph__pixelzone__hpp__
#define __graph__pixelzone__hpp__

#include <mutex>
#include <SDL2/SDL.h>
#include "utils.hpp"

class pixelzone
{
    public:
        pixelzone();
        void updatetexture(SDL_Texture * texture);
        void setpixel(color c ,int x,int y);
        color getpixel(int x,int y);
        void clear();
        void clearrows();
        bool trytakerow(int id);
    private:
        class rowstatus
        {
            public:
                rowstatus();
                bool trytake();
                void reset();
            private:
                bool taken;
                std::mutex m;
        };
        color pixels[512][512];
       // std::mutex m;
        rowstatus rstatus[512];
};

#endif
