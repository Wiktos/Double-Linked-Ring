#pragma once
#include <sstream>

#include "../templates/ring.h"
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

}
