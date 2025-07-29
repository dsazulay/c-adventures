#include "base/base_tester.h"
#include "base/base_dynarray.h"

void testDynArray()
{
    ArrayF32 array = {0};
    dynArrayReserve(&array, 2);
    Check(array.capacity == 2);

    dynArrayPush(&array, 23.f);
    Check(array.count == 1);

    dynArrayPush(&array, 25.f);
    Check(array.count == 2);

    dynArrayPush(&array, 27.f);
    Check(array.count == 3);
    Check(array.capacity == 4);

    f32 test = dynArrayPop(&array);
    Check(array.count == 2);
    Check(array.capacity == 4);

    dynArrayRelease(&array);
    Check(array.count == 0);
    Check(array.capacity == 0);
}

TestRun("DynArray", 1, TestCase(testDynArray))
