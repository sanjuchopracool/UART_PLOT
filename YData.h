#ifndef YDATA_H
#define YDATA_H
class YData
{
public:
    double data[20000];
    YData()
    {
        for(int i=0 ;i<20000;i++)
            data[i]=0;
    }
};

#endif // YDATA_H
