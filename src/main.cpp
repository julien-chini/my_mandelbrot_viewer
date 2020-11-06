#include <SDL2/SDL.h>

#include "fenetre.hpp"
#include "ensemble.hpp"


int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);

    bool done = false;
    SDL_Event event;
    
    mandelbrot * m= new mandelbrot;
    julia * j = new julia;

    fenetre *fenetrem = new fenetre(std::string("Mandelbrot"),m);
    fenetre *fenetrej = new fenetre(std::string("Julia"),j);
 
    fenetrem->movewby(-260,0);
    fenetrej->movewby(260,0);

    int mousex,mousey;
    while(!done)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                done=true;
            };
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                done=true;
            };
            if(event.type == SDL_MOUSEMOTION)
            {
                mousex = event.motion.x;
                mousey = event.motion.y;
                    
            }
            if(event.type == SDL_MOUSEWHEEL)
            {
                //zoom
                if(event.wheel.y > 0)
                {
                    //zoom in
                    if(event.wheel.windowID == fenetrem->getid())
                    {
                        fenetrem->zoomin(mousex,mousey);
                    }
                    else if(event.wheel.windowID == fenetrej->getid())
                    {
                        fenetrej->zoomin(mousex,mousey);
                    }
                }
                else
                {
                    //zoom out
                    if(event.wheel.windowID == fenetrem->getid())
                    {
                        fenetrem->zoomout(mousex,mousey);
                    }
                    else if(event.wheel.windowID == fenetrej->getid())
                    {
                        fenetrej->zoomout(mousex,mousey);
                    }
                }
            }
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.windowID == fenetrem->getid())
            {
                j->setcon(fenetrem->getbycoord(event.button.x,event.button.y));
                fenetrej->initzoom();
                fenetrej->resetiter();
                fenetrej->clearpixels();
                fenetrej->startdraw();
            }
            if(event.type == SDL_KEYDOWN )
            {
                if(event.key.keysym.sym == SDLK_SPACE)
                {
                    //reinit 
                    j->setcon(std::complex<double>(0.0,0.0));
                    fenetrem->initzoom();
                    fenetrej->initzoom();
                    fenetrem->resetiter();
                    fenetrej->resetiter();
                    fenetrem->clearpixels();
                    fenetrej->clearpixels();
                    fenetrem->startdraw();
                    fenetrej->startdraw();
                }
                else if (event.key.keysym.sym == SDLK_p)
                {
                    if(event.key.windowID == fenetrem->getid())
                        fenetrem->plusiters();
                    if(event.key.windowID == fenetrej->getid())
                        fenetrej->plusiters();
                }
                else if (event.key.keysym.sym == SDLK_m)
                {
                    if(event.key.windowID == fenetrem->getid())
                        fenetrem->minusiters();
                    if(event.key.windowID == fenetrej->getid())
                        fenetrej->minusiters();
                }
                else if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_z)
                {
                    if(event.key.windowID == fenetrem->getid())
                        fenetrem->move(0,-1);
                    if(event.key.windowID == fenetrej->getid())
                        fenetrej->move(0,-1);
                }
                else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
                {
                    if(event.key.windowID == fenetrem->getid())
                        fenetrem->move(0,1);
                    if(event.key.windowID == fenetrej->getid())
                        fenetrej->move(0,1);
                }
                else if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q)
                {
                    if(event.key.windowID == fenetrem->getid())
                        fenetrem->move(-1,0);
                    if(event.key.windowID == fenetrej->getid())
                        fenetrej->move(-1,0);
                }
                else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
                {
                    if(event.key.windowID == fenetrem->getid())
                        fenetrem->move(1,0);
                    if(event.key.windowID == fenetrej->getid())
                        fenetrej->move(1,0);
                }
                else if (event.key.keysym.sym == SDLK_i)
                {
                    if(event.key.windowID == fenetrem->getid())
                        fenetrem->zoomin(256,256);
                    if(event.key.windowID == fenetrej->getid())
                        fenetrej->zoomin(256,256);;
                }
                else if (event.key.keysym.sym == SDLK_o)
                {
                    if(event.key.windowID == fenetrem->getid())
                        fenetrem->zoomout(256,256);
                    if(event.key.windowID == fenetrej->getid())
                        fenetrej->zoomout(256,256);
                }
                else if (event.key.keysym.sym == SDLK_RETURN)
                {
                    if(event.key.windowID == fenetrem->getid())
                    {
                        j->setcon(fenetrem->getbycoord(256,256));
                        fenetrej->initzoom();
                        fenetrej->resetiter();
                        fenetrej->clearpixels();
                        fenetrej->startdraw();
                    }
                }

            }
        
        }
        //draw
       fenetrem->render();
       fenetrej->render();
    }
    delete fenetrem;
    delete fenetrej;
    delete m;
    delete j;

    return 0;
}