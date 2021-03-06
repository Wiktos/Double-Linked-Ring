#pragma once
#include <sstream>

#include "../templates/ring.h"
#include "../templates/ring_iter.h"
#include "../templates/produce.h"
#include "error_messenger.h"

namespace ring_test{

    auto error_messenger = []()->ErrorMessenger&{
        return ErrorMessenger::get_instance();
    };

    void test_constructor();
    void test_push();
    void test_clear_and_assign_op();
    void test_contain_method();
    void test_compare_method();
    void test_equals_operator();
    void test_remove_method();
    void test_swap_method();
    void test_merge_and_binary_op();
    void test_iterator_class();
    void test_produce_method();

}
