#include "../test/ring_tests.h"

using namespace std;

int main()
{
    ring_test::test_constructor();
    ring_test::test_push();
    ring_test::test_clear_and_assign_op();
    ring_test::test_contain_method();
    ring_test::test_compare_method();
    ring_test::test_equals_operator();
    ring_test::test_remove_method();
    ring_test::test_swap_method();
    ring_test::test_merge_and_binary_op();

    ring_test::error_messenger().print_report(std::cout);
    return 0;
}
