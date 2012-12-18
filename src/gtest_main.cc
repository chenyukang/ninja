#include <limits.h>
#include "gtest/gtest.h"

#include <string.h>
#include <vector>

using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using namespace std;

int main(int argc, char** argv) {
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    std::string str;
    for(std::string::iterator it = str.begin();
        it != str.end(); ++it) {
        std::cout << *it << std::endl;
    }
    vector<std::string> vec;
    vec.push_back(10);
    return 0;
}

int test() {
    std::vector<int> vec;
    for(std::vector<int>::iterator iter = vec.begin(); iter!=vec.end(); ++iter) {
        std::cout<< *iter << std::endl;
    }
}

