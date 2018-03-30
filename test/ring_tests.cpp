#include "ring_tests.h"

using namespace std;

void ring_test::test_constructor(){
    Ring<int, int> test;
    if(!test.is_empty())
        ring_test::error_messenger().report("is_empty() test constructor error");
    if(test.size())
        ring_test::error_messenger().report("size() test constructor error");

    Ring<int, int> test2{ {1, 1}, {2, 2}, {3, 3} };
    if(test2.size() != 3)
        ring_test::error_messenger().report("size() test init_list constructor error");

    stringstream expected_output("1 1\n2 2\n3 3\n");
    stringstream output_received;
    output_received << test2;
    if(output_received.str() != expected_output.str())
        ring_test::error_messenger().report("init_list constructor error");
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

void ring_test::test_equals_operator(){
    Ring<int, int> first;
    Ring<int, int> second;

    if(!(first == second))
        ring_test::error_messenger().report("op== test1 error");

    first.push(1, 1);
    if(first == second)
        ring_test::error_messenger().report("op== test2 error");

    second.push(1, 1);
    if(!(first == second))
        ring_test::error_messenger().report("op== test3 error");
}

void ring_test::test_remove_method(){
    Ring<int, int> my_tested;

    //basic test
    my_tested.push(1, 1);
    my_tested.remove(1);

    if(!my_tested.is_empty())
        ring_test::error_messenger().report("remove() test error - is_empty() == true");
    if(my_tested.size())
        ring_test::error_messenger().report("remove() test error - size() != 0");

    //test sequence's length management
    my_tested.push(1, 1);
    my_tested.push(2, 1);
    my_tested.push(1, 1);
    my_tested.remove(1);

    if(my_tested.size() != 2)
        ring_test::error_messenger().report("remove() test error - length != 1");

    //test of seq modification
    auto test_seq_output_stream = [&](const std::string& proper_output)->void{
        stringstream expected_output(proper_output);
        stringstream output_received;
        output_received << my_tested;
        if(output_received.str() != expected_output.str())
            ring_test::error_messenger().report("remove() test error - wrong stream output");
    };

    test_seq_output_stream("2 1\n1 1\n");

    my_tested.push(3, 1);
    my_tested.remove(2);

    test_seq_output_stream("1 1\n3 1\n");

    //test of proper throwing exception
    auto test_throwing_except = [&](int loc)->void{
        try{
            my_tested.remove(loc);
            ring_test::error_messenger().report("test_throwing_except exception should be thrown");
        }
        catch(Ring<int, int>::RingInvalidArgument& ex){
        }
    };

    test_throwing_except(0);
    test_throwing_except(30);
}

void ring_test::test_swap_method(){
    Ring<int, int> my_tested;
    for(int i = 0; i < 10 ; i++)
        my_tested.push(i, i);
    Ring<int, int> second;

    my_tested.swap(second);
    if(!my_tested.is_empty())
        ring_test::error_messenger().report("test swap method - my_tested should be empty");
    if(second.is_empty())
        ring_test::error_messenger().report("test swap method - second should not be empty");
}

void ring_test::test_merge_and_binary_op(){
    Ring<int, int> my_tested;

    auto test_seq_output_stream = [&](const std::string& proper_output, const Ring<int, int>& seq)->void{
        stringstream expected_output(proper_output);
        stringstream output_received;
        output_received << seq;
        if(output_received.str() != expected_output.str())
            ring_test::error_messenger().report("merge() test error - wrong stream output");
    };

    for(auto i = 0; i < 3; i++)
        my_tested.push(i, i);


    const Ring<int, int> copied(my_tested);
    Ring<int, int> merged_seq1 = my_tested.merge(copied);

    test_seq_output_stream("0 0\n1 1\n2 2\n0 0\n1 1\n2 2\n", merged_seq1);

    Ring<int, int> merged_seq2 = my_tested + copied;
    test_seq_output_stream("0 0\n1 1\n2 2\n0 0\n1 1\n2 2\n", merged_seq2);

    Ring<int, int> merged_seq3;
    merged_seq3 += my_tested;
    merged_seq3 += copied;
    test_seq_output_stream("0 0\n1 1\n2 2\n0 0\n1 1\n2 2\n", merged_seq3);
}

void ring_test::test_iterator_class_first(){
    Ring<int, int> my_tested;
    Ring<int, int>::iterator iter = my_tested.iter();
    Ring<int, int>::const_iterator const_iter1 = my_tested.iter();

    //checking iter() return nullptr
    if(iter != nullptr || const_iter1 != nullptr)
        ring_test::error_messenger().report("iterator test !nullptr");

    my_tested.push(1, 1);
    //checking iter() return any
    iter = my_tested.iter();
    Ring<int, int>::const_iterator const_iter2 = my_tested.iter();

    if(iter == nullptr || const_iter2 == nullptr)
        ring_test::error_messenger().report("iterator test =nullptr");

    //checking contain value
    auto node = *iter;

    if(node.key != 1 || node.info != 1)
        ring_test::error_messenger().report("iterator test contain value not equal to proper one");

    (*iter).key = 3;
    Ring<int, int>::iterator iter_bis = my_tested.iter();
    if(iter_bis->key != 3)
        ring_test::error_messenger().report("iterator test wrong modification");

    my_tested.push(2, 2);
    iter++;
    if(iter->key != 2)
        ring_test::error_messenger().report("iterator test wrong op++");
}
