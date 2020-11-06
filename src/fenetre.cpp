#include "fenetre.hpp"

fenetre::fenetre(std::string n,ensemble * e)
{
    ens = e;
    name = n;
    window = SDL_CreateWindow("",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,512,512,SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA32,SDL_TEXTUREACCESS_STREAMING,512,512);
    initzoom();
    clearpixels();
    startdraw();
}
fenetre::~fenetre()
{
    stopdraw();
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
void fenetre::clearpixels()
{
    pz.clear();
}
void fenetre::render()
{
    pz.updatetexture(texture);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,texture,NULL,NULL);
    SDL_RenderPresent(renderer);
}
unsigned int fenetre::getid()
{
    return SDL_GetWindowID(window);
}
std::complex<double> fenetre::getbycoord(int x,int y)
{
    return ens->getbycoord(x,y);
};
void fenetre::zoomin(int x,int y)
{
    ens->center = (getbycoord(x,y)+ens->center)/2.0;
    ens->size /= 2;
    stopdraw();
    clearpixels();
    startdraw();
    updatetitle();
};
void fenetre::zoomout(int x,int y)
{
    ens->center = (2.0*ens->center) - getbycoord(x,y);
    ens->size *= 2;
    stopdraw();
    clearpixels();
    startdraw();
    updatetitle();
};
void fenetre::startdraw()
{
    
    pool.init(&pz,ens);
}
void fenetre::stopdraw()
{
    pool.stop();
}
void fenetre::initzoom()
{
    ens->center = ens -> defaultcenter;
    ens->size = ens -> defaultsize;
    updatetitle();
}
void fenetre::updatetitle()
{
    double zoom = 2.0 / ens->size;
    std::string s;
    if( zoom < 1.0)
        s = std::string("1 / ") + std::to_string((long long int) (1.0 / zoom));
    else
        s = std::to_string((long long int) zoom);
    s = name + std::string("; zoom : ") + s + std::string("; iterations : ") + std::to_string(ens->numiter);
    SDL_SetWindowTitle(window,s.c_str());

}
void fenetre::plusiters()
{
    ens->numiter *=2.0;
    stopdraw();
    //clearpixels();
    pz.clearrows();
    startdraw();
    updatetitle();
};
void fenetre::minusiters()
{
    if(ens->numiter > 360)
    {
        ens->numiter /=2.0;
        stopdraw();
        clearpixels();
        startdraw();
        updatetitle();
    }
};
void fenetre::movewby(int x,int y)
{
    int wx,wy;
    SDL_GetWindowPosition(window,&wx,&wy);
    SDL_SetWindowPosition(window,x+wx,y+wy);
};
void fenetre::resetiter()
{
    ens->numiter = 360;
    updatetitle();
}
void fenetre::move(int x,int y)
{
    std::complex<double> by(x*ens->size/8.0,y*ens->size/8.0);
    ens->center += by;
    stopdraw();
    clearpixels();
    startdraw();
};