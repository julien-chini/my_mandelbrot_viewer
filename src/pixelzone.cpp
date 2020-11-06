#include "pixelzone.hpp"

pixelzone::pixelzone()
{
    clear();
}
void pixelzone::setpixel(color c ,int x,int y)
{
    if(x >=0 && x <512 &&y >=0 && y <512)
    {
        //m.lock();
        pixels[y][x]=c;
        //m.unlock();
    }
};

color pixelzone::getpixel(int x,int y)
{
    if(x >=0 && x <512 &&y >=0 && y <512)
    {
        //m.lock();
        return pixels[y][x];
        //m.unlock();
    }
    else
    {
        return palette::black();
    }
    
};
void pixelzone::clear()
{
    //m.lock();
    for(int iy=0;iy<512;iy++)
    {
        for(int ix=0;ix<512;ix++)
        {
            pixels[iy][ix] = palette::black();
        }
        rstatus[iy].reset();
    }
   // m.unlock();
};
void pixelzone::clearrows()
{
    //m.lock();
    for(int iy=0;iy<512;iy++)
    {
        rstatus[iy].reset();
    }
   // m.unlock();
};
void pixelzone::updatetexture(SDL_Texture * texture)
{
   // m.lock();
    SDL_UpdateTexture(texture,NULL,&(pixels[0][0]),sizeof(color)*512);
   // m.unlock();
}

pixelzone::rowstatus::rowstatus()
{
    taken=false;
};
bool pixelzone::rowstatus::trytake()
{
    bool b;
    m.lock();
    if(taken)
    {
        b = false;
    }
    else
    {
        b=true;
        taken = true;
    }
    m.unlock();
    return b;
};
void pixelzone::rowstatus::reset()
{
    taken=false;
};
bool pixelzone::trytakerow(int id)
{
    if(id >=0 && id < 512)
        return rstatus[id].trytake();
    else
        return false;
    
};