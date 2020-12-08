#include <stdio.h>

#include "subset.h"


int main(int argc, char* argv[])
{
    // Generate Subsets of given "string".
    //
    // Algorithm:
    //  1. Given P("abc")
    //  2. Remove one character from P in order.
    //     P("bc"), P("ac"), P("ab")
    //  3. Do "2." to each element.
    //  4. Merge the result of "3."
    //  5. Repeat each unique element "1-4" until empty string meets.
    //  6. Print unique elements

    do_subset();
}
