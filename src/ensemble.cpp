#include "ensemble.hpp"

ensemble::ensemble()
{
    numiter = 360;
}
std::complex<double> ensemble::getbycoord(int x,int y)
{
    double pixelsize = size / 512.0;
    std::complex<double> c((x-256)* pixelsize,(y-256) * pixelsize);
    return center + c;
};
mandelbrot::mandelbrot()
{
    defaultcenter.real(-0.5);
    defaultcenter.imag(0.0);
    defaultsize = 2.0;
}
ensemble::ensparam mandelbrot::inititer(std::complex<double> i)
{
    ensemble::ensparam p;
    p.z0=0;
    p.c=i;
    return p;
}
julia::julia()
{
    defaultcenter.real(0.0);
    defaultcenter.imag(0.0);
    defaultsize = 4.0;
}
ensemble::ensparam julia::inititer(std::complex<double> i)
{
    ensemble::ensparam p;
    p.z0=i;
    p.c=con;
    return p;
}
void julia::setcon(std::complex<double> conn)
{
    con=conn;
}