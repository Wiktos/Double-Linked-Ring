#include "../test/ring_tests.h"

using namespace std;

int main()
{
    ring_test::test_constructor();
    ring_test::test_push();

    ring_test::error_messenger().print_report(std::cout);
    return 0;
}
