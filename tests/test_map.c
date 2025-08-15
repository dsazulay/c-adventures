#include "base/base_tester.h"
#include "base/base_map.h"

void testMap()
{
    MapStrI32 map = {0};
    mapReserve(&map, 2);
    Check(map.maxSize == 1);
    Check(map.capacity == 2);

    mapInsert(&map, S("Diego"), 10);
    Check(map.count == 1);
    Check(map.maxSize == 1);

    mapInsert(&map, S("Azul"), 20);
    Check(map.count == 2);
    Check(map.maxSize == 3);
    Check(map.capacity == 4);

    mapInsert(&map, S("Blue"), 30);
    Check(map.count == 3);

    mapInsert(&map, S("Taiane"), 40);
    Check(map.count == 4);
    Check(map.maxSize == 6);
    Check(map.capacity == 8);

    KVStrI32 *ptr = mapFind(&map, S("Diego"));
    Check(ptr->value == 10);

    ptr = mapErase(&map, S("Azul"));
    Check(ptr->value == 10);

    ptr = mapErase(&map, S("Diego"));
    Check(ptr->value == 40);

    ptr = mapFind(&map, S("Test"));
    Check(ptr == NULL);

    mapRelease(&map);
    Check(map.count == 0);
    Check(map.maxSize == 0);
    Check(map.capacity == 0);
}

TestRun("Map", 1, TestCase(testMap));
