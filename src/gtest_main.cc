#include <limits.h>
#include "gtest/gtest.h"


using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;


int main(int argc, char** argv) {
    InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}

