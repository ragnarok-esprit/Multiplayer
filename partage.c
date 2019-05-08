#include "partage.h"

void init_splitscreen(image* I1,image *I2,int screenw)
{
int int_screenw=screenw/2;
I1->positionc.w=int_screenw;
I2->positionc.w=int_screenw;
I2->positiond.x=int_screenw;
}
