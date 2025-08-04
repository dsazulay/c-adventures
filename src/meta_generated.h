#include "meta/meta_core.h"

StructMember membersOfPerson[] =
{
    { Meta_String, "name", (u64)&((Person *)0)->name },
    { Meta_i32, "age", (u64)&((Person *)0)->age },
};

StructMember membersOfButton[] =
{
    { Meta_String, "lable", (u64)&((Button *)0)->lable },
    { Meta_f32, "size", (u64)&((Button *)0)->size },
};

#define _getMembersArray(x) _Generic((x), \
    Person: membersOfPerson, \
    Button: membersOfButton \
)

#define metaPrint(x) _metaPrint((void *)&x, _getMembersArray(x), arrayCount(_getMembersArray(x)))

