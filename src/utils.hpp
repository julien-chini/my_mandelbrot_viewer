#ifndef __graph__utils__hpp__
#define __graph__utils__hpp__



struct color
{
    unsigned char r,g,b,a;
}; 
class palette
{
    public:
        static color getcolor(int id);
        static color black();
        static bool isblack(color c);
    private:
        static palette *p;
        palette();
        color colors[360];

};


double interp(double min, double max, double inter);





#endif