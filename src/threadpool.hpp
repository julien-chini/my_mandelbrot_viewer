#ifndef __graph__threadpool__hpp__
#define __graph__threadpool__hpp__

#include <thread>
#include <mutex>
#include <vector>
#include "pixelzone.hpp"
#include "ensemble.hpp"

class threadpool
{
    public:
        void init(pixelzone * pzone,ensemble * e);
        void stop();
        class stopstatus
        {
            public:
                stopstatus();
                void init();
                void stop();
                bool hastostop();
            private:
                bool b;
                std::mutex m;
        };
    private:
        std::vector<std::thread *> threadvector;
        stopstatus status;

};


#endif