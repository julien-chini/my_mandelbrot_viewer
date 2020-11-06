#include "utils.hpp"
#include <cmath>
double interp(double min, double max, double inter)
{
    double c = inter * inter * inter * ( 10.0 + inter * ( 6.0 * inter -15.0 ));
    return min*(1.0-c)+max*c;
};

palette * palette::p = nullptr;

palette::palette()
{
    for(int i=0;i<360;i++)
    {
        colors[i].r=0;
        colors[i].g=0;
        colors[i].b=0;
        colors[i].a=255;
    }
    for(int i = 0;i< 60;i++)
    {
        double inter= (double)i / 60.0;
        unsigned char interup = interp(0.0,255.0,inter);
        unsigned char interdown = interp(255.0,0.0,inter);

        colors[i].r = 255;
        colors[i].g = interup;

        colors[i+60].r = interdown;
        colors[i+60].g = 255;
        
        colors[i+120].g = 255;
        colors[i+120].b = interup;

        colors[i+180].g = interdown;
        colors[i+180].b = 255;

        colors[i+240].r = interup;
        colors[i+240].b = 255;

        colors[i+300].r = 255;
        colors[i+300].b = interdown;
    }
}
int indice(int id)
{
    if(id <360)
    {
        return id;
    }
    else
    {
        return (int)(log2((double)id/360.0)*360.0);
    }
    
}

color palette::getcolor(int id)
{
    if(p == nullptr)
    {   
        p = new palette;
    }
    return p->colors[indice(id) % 360];
};
color palette::black()
{
    color b;
    b.r=b.g=b.b=0;
    b.a = 255;
    return b;
};
bool palette::isblack(color c)
{
    if( c.r==0 && c.g == 0 && c.b ==0 )
        return true;
    else
        return false;
};