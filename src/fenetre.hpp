#ifndef __graph__fenetre__hpp__
#define __graph__fenetre__hpp__

#include <SDL2/SDL.h>

#include "utils.hpp"
#include "ensemble.hpp"
#include "pixelzone.hpp"
#include "threadpool.hpp"
#include <complex>
#include <string>

class fenetre
{
    public:
        fenetre(std::string n,ensemble * e);
        ~fenetre();
        void clearpixels();
        void zoomin(int x,int y);
        void zoomout(int x,int y);
        std::complex<double> getbycoord(int x,int y);
        void render();
        void startdraw();
        void stopdraw();
        unsigned int getid();
        void initzoom();
        void plusiters();
        void minusiters();
        void resetiter();
        void movewby(int x,int y);
        void move(int x,int y);
    private:
        std::string name;
        SDL_Window * window;
        SDL_Renderer * renderer;
        SDL_Texture * texture;
        ensemble * ens;
        pixelzone pz;
        threadpool pool;
        void updatetitle();


};





#endif