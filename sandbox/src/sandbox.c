#include <core.h>
//#include <core\core_logger.h>

int main()
{
    SFATAL("A test message: %f", 3.14f);
    SERROR("A test message: %f", 3.14f);
    SWARN("A test message: %f", 3.14f);
    SINFO("A test message: %f", 3.14f);
    SDEBUG("A test message: %f", 3.14f);
    STRACE("A test message: %f", 3.14f);
    
    
    
    return 0;
}
