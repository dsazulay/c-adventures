#include "base/base_tester.h"
#include "base/base_string.h"
#include "meta/meta_core.h"

Reflect()
typedef struct
{
    String name;
    i32 age;
} Person;

Reflect()
typedef struct
{
    String lable;
    f32 size;
} Button;

#include "meta_generated.h"

void testMeta()
{
    Person p = {
        .name = S("Diego"),
        .age = 27,
    };

    Person p2 = {
        .name = S("Taiane"),
        .age = 47,
    };

    Button b = {
        .lable = S("Cancel"),
        .size = 0.5f,
    };

    metaPrint(p);
    metaPrint(p2);
    metaPrint(b);
}

TestRun("Meta", 1, TestCase(testMeta));
