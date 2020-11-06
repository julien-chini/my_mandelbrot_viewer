

#include "threadpool.hpp"
#include "utils.hpp"

void threadfunc(pixelzone * pzone,ensemble * e,threadpool::stopstatus * status)
{
    int row=0;
    while(row < 512)
    {
        if(pzone->trytakerow(row))
        {
            //dorow
            int x=0;
            while(x < 512)
            {
                //dopixel
                if(status->hastostop())
                {
                    return;
                }
                if(palette::isblack(pzone->getpixel(x,row)))
                {
                    std::complex<double> point = e->getbycoord(x,row);
                    
                    ensemble::ensparam p = e->inititer(point);
                    std::complex<double> z= p.z0;
                    std::complex<double> c= p.c;
                    int iter=0;

                    while(std::abs(z) < 2.0 && iter <= e->numiter)
                    {
                        z = z * z + c;
                        iter++;

                    }
                    if(iter < e->numiter)
                    {
                        pzone->setpixel(palette::getcolor(iter),x,row);
                    }
                    else
                    {
                        pzone->setpixel(palette::black(),x,row); 
                    }
                }
                x++;
            }
        }
        row++;
    }
}
void threadpool::init(pixelzone * pzone,ensemble * e)
{
    status.init();
    int numthreads = std::thread::hardware_concurrency();
    for(int i = 0;i<numthreads;i++)
    {
        threadvector.push_back(new std::thread(threadfunc,pzone,e,&status));
    }
};
void threadpool::stop()
{
    status.stop();
    for(auto i = threadvector.begin();i != threadvector.end();i++)
    {
        (*i)->join();
        delete (*i);
    }
    threadvector.clear();
};

threadpool::stopstatus::stopstatus()
{
    b= false;
};
void threadpool::stopstatus::stop()
{
    m.lock();
    b=true;
    m.unlock();
};
void threadpool::stopstatus::init()
{
    m.lock();
    b=false;
    m.unlock();
};
bool threadpool::stopstatus::hastostop()
{
    bool h;
    m.lock();
    h=b;
    m.unlock();
    return h;
};
