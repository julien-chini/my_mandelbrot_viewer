#ifndef __graph__ensemble__hpp__
#define __graph__ensemble__hpp__

#include <complex>


class ensemble
{
    public:
        struct ensparam
        {
            std::complex<double> z0;
            std::complex<double> c;
        };
        ensemble();
        virtual ensparam inititer(std::complex<double> i)=0;
        std::complex<double> center,defaultcenter;
        double size,defaultsize;
        std::complex<double> getbycoord(int x,int y);
        int numiter;
};
class mandelbrot : public ensemble
{
    public:
        mandelbrot();
        ensparam inititer(std::complex<double> i);
};
class julia : public ensemble
{
    public:
        julia();
        void setcon(std::complex<double> conn);
        ensparam inititer(std::complex<double> i);
    private:
        std::complex<double> con;
};

#endif