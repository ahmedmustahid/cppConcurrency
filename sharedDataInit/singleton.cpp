#include "singleton.h"

// Singleton *Singleton::get_single()
//{
//     if (single == nullptr)
//         single = new Singleton;
//     return single;
// }
Singleton &get_single()
{
    static Singleton single;
    return single;
}
