/*
 * Originally part of multi-file testing design that we decided to scrap.
 * Code from this file made it into test_cache_lib.cc, but this file isn't used in any test
 * and the tests in here don't work for the current version of the code.
 */



#include "cache.hh"
#include <cassert>
#include <iostream>
#include <cstring>
using size_type = uint32_t;

void test_fifo_evictor(){
    // Expected behavior for Cache::set when using a fifo evictor:
    // When not enough memory remains to store a value, the oldest items will be thrown out one by one until
    // enough space is freed to store the new value.
    // When attempting to store a value that is too large for the cache to store even with no other space used,
    // should fail silently without removing anything.
    Cache c = Cache(15);
    std::string key_1 = "Item 1";
    std::string key_2 = "Item 2";
    std::string key_3 = "Item 3";
    const char *val_1 = "3.14159";
    const char *val_2 = "pi";
    const char *val_3 = "tau / 2";
    size_type val_1_size = strlen(val_1) + 1;
    size_type val_2_size = strlen(val_2) + 1;
    size_type val_3_size = strlen(val_3) + 1;
    c.set(key_1, val_1, val_1_size);
    c.set(key_3, val_3, val_3_size);
    c.set(key_2, val_2, val_2_size);
    assert(c.get(key_1, val_1_size) == nullptr);
    assert(c.get(key_2, val_2_size) != nullptr);
    assert(c.get(key_3, val_3_size) != nullptr);
    c.set(key_1, val_1, val_1_size);
    assert(c.get(key_3, val_3_size) == nullptr);
    assert(c.get(key_1, val_1_size) != nullptr);
    assert(c.get(key_2, val_2_size) != nullptr);
    c.set(key_1, val_1, val_1_size);
    assert(c.get(key_1, val_1_size) != nullptr);
    assert(c.get(key_2, val_2_size) == nullptr);
    assert(c.get(key_3, val_3_size) == nullptr);
}

int main(){
    std::cout << "Starting FIFO evictor tests" << std::endl;
    test_fifo_evictor();
    std::cout << "Passed tests for FIFO evictor!" << std::endl;
    return 0;
}