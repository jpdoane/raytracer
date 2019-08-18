#include "Rt.h"

int main(void)
{
        Rt* rt = new Rt(500, 500);
        rt->render();
        delete rt;
        return 0;
}
