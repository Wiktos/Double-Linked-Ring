#include "ring_tests.h"

using namespace std;

void ring_test::test_constructor(){
    Ring<int, int> test;
    if(!test.is_empty())
        ring_test::error_messenger().report("is_empty() test constructor error");
    if(test.size())
        ring_test::error_messenger().report("size() test constructor error");
}

void ring_test::test_push(){
    Ring<int, int> test;
    test.push(1, 1);
    test.push(2, 2);

    if(test.is_empty())
        ring_test::error_messenger().report("is_empty() test1 pushing error");
    if(test.size() != 2)
        ring_test::error_messenger().report("size() test1 pushing error");

    test.push(3, 3);
    test.push(4, 4);

    if(test.size() != 4)
        ring_test::error_messenger().report("size() test2 pushing error");

    stringstream expected_output("1 1\n2 2\n3 3\n4 4\n");
    stringstream output_received;
    output_received << test;
    if(output_received.str() != expected_output.str())
        ring_test::error_messenger().report("operator << test pushing error");
}

void ring_test::test_clear_and_assign_op(){
    Ring<int, int> test;
    test.push(1, 1);
    test.push(1, 1);
    test.push(1, 1);

    Ring<int, int> sec = test;

    test.clear();
    if(test.size())
        ring_test::error_messenger().report("clear() doesn't set lenght = 0");

    stringstream expected_output("1 1\n1 1\n1 1\n");
    stringstream output_received;
    output_received << sec;
    if(output_received.str() != expected_output.str())
        ring_test::error_messenger().report("operator = error");
}

void ring_test::test_contain_method(){
    Ring<int, int> my_tested;

    my_tested.push(1, 1);
    if(!my_tested.contain(1))
        ring_test::error_messenger().report("contain test fail - key exist");
    if(my_tested.contain(2))
        ring_test::error_messenger().report("contain test fail - key does not exist");
}

void ring_test::test_compare_method(){
    Ring<int, int> first;
    Ring<int, int> second;
    bool compare_res = first.compare(second, [](const Ring<int, int> first, const Ring<int, int> second) ->bool{
                        return first.size() > second.size();
                     });

    if(compare_res)
        ring_test::error_messenger().report("compare method error");
}
