#include "cache.hh"
#include <cassert>
#include <iostream>
#include <cstring>
using size_type = uint32_t;
/*
 * Some basic unit tests for Cache objects.
 * The documentation expected behavior of each method is copied directly from cache.hh
 * There's no test for the constructor / destructor, since these are basic for all other tests
 * In general, there's some overlap between the tests for each method, since we need getting to test setting, etc.
 * But, the tests are still divided conceptually, to ensure that everything gets tested properly.
 */

void test_set(){
    // Expected behavior for Cache::set(key_type key, val_type val, size_type size):
    // Add a <key, value> pair to the cache.
    // If key already exists, it will overwrite the old value.
    // Both the key and the value are to be deep-copied (not just pointer copied).
    // Eviction rules are covered in later tests.
    Cache c = Cache(20);
    std::string key_1 = "Item 1";
    std::string key_2 = "Item 2";
    const char *val_1 = "3.14159";
    const char *val_2 = "pi";
    const char *val_3 = "tau / 2";
    size_type val_1_size = strlen(val_1) + 1;
    size_type val_2_size = strlen(val_2) + 1;
    size_type val_3_size = strlen(val_3) + 1;
    // testing that Cache::set(...) works and items can be retrieved unaltered
    c.set(key_1, val_1, val_1_size);
    c.set(key_2, val_2, val_2_size);
    assert(strcmp(c.get(key_1, val_1_size), val_1) == 0);
    assert(strcmp(c.get(key_2, val_2_size), val_2) == 0);
    // testing that Cache::set(k, ...) overwrites if k is already in the cache
    c.set(key_1, val_3, val_3_size);
    assert(strcmp(c.get(key_1, val_3_size), val_3) == 0);
    assert(strcmp(c.get(key_1, val_1_size), val_1) != 0);
    // testing that Cache::set deep-copies values
    auto cval1 = c.get(key_2, val_2_size);
    assert(cval1 != val_2);
    c.set(key_1, val_2, val_2_size);
    assert(c.get(key_1, val_2_size) != cval1);
    // testing that Cache::set deep-copies keys
    key_2.replace(0, key_2.length() + 1, key_1);
    assert(strcmp(c.get("Item 2", val_2_size), val_2) == 0);

}
void test_get(){
    // Expected behavior for Cache::get(key_type key, size_type& val_size):
    // Retrieve a pointer to the value associated with key in the cache,
    // or nullptr if not found.
    // Sets the actual size of the returned value (in bytes) in val_size.
    // Const method, so should never change the cache when called.
    Cache c = Cache(20);
    std::string key_1 = "Item 1";
    std::string key_2 = "Item 2";
    const char *val_1 = "3.14159";
    const char *val_2 = "pi";
    size_type val_1_size = strlen(val_1) + 1;
    size_type val_2_size = strlen(val_2) + 1;
    // testing that Cache::get(...) returns nullptr on an empty cache, or with a key that's not in the cache
    assert(c.get(key_1, val_1_size) == nullptr);
    c.set(key_1, val_1, val_1_size);
    assert(c.get(key_2, val_2_size) == nullptr);
    // testing that Cache::get(...) retrieves the right pointer when the key is in the cache
    c.set(key_2, val_2, val_2_size);
    assert(strcmp(c.get(key_1, val_1_size), val_1) == 0);
    assert(strcmp(c.get(key_2, val_2_size), val_2) == 0);
    // note: missing test to ensure that get does not change the cache
}
void test_del(){
    // Expected behavior for Cache::del(key_type key):
    // Delete an object from the cache, if it's still there
    // Should return True if the key was found and deleted
    Cache c = Cache(20);
    std::string key_1 = "Item 1";
    std::string key_2 = "Item 2";
    const char *val_1 = "3.14159";
    const char *val_2 = "pi";
    size_type val_1_size = strlen(val_1) + 1;
    size_type val_2_size = strlen(val_2) + 1;
    assert(c.del(key_1) == false);
    c.set(key_1, val_1, val_1_size);
    c.set(key_2, val_2, val_2_size);
    assert(c.del(key_1) == true);
    assert(c.del(key_2) == true);
    assert(c.del(key_1) == false);
    assert(c.del(key_2) == false);
    assert(c.get(key_2, val_2_size) == nullptr);
}
void test_space(){
    // Expected behavior for Cache::space_used():
    // Compute the total amount of memory used up by all cache values (not keys)
    Cache c = Cache(20);
    std::string key_1 = "Item 1";
    std::string key_2 = "Item 2";
    const char *val_1 = "3.14159";
    const char *val_2 = "pi";
    const char *val_3 = "tau / 2";
    size_type val_1_size = strlen(val_1) + 1;
    size_type val_2_size = strlen(val_2) + 1;
    size_type val_3_size = strlen(val_3) + 1;
    assert(c.space_used() == 0);
    c.set(key_1, val_1, val_1_size);
    assert(c.space_used() == val_1_size);
    c.set(key_2, val_2, val_2_size);
    assert(c.space_used() == val_1_size + val_2_size);
    c.set(key_2, val_3, val_3_size);
    assert(c.space_used() == val_1_size + val_3_size);
    c.del(key_1);
    assert(c.space_used() == val_3_size);
}
void test_reset(){
    // Expected behavior for Cache::reset():
    // Delete all data from the cache
    Cache c = Cache(20);
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
    c.set(key_2, val_2, val_2_size);
    c.set(key_3, val_3, val_3_size);
    c.reset();
    assert(c.space_used() == 0);
    assert(c.del(key_1) == false);
    assert(c.get(key_2, val_2_size) == nullptr);
}
// Evictor tests: these rules vary based on which evictor is used.
// They all follow the same pattern, only being called when a new value is inserted with Cache::set(...):
    // If maxmem capacity is exceeded, enough values will be removed
    // from the cache to accomodate the new value. If unable, the new value
    // isn't inserted to the cache.
void test_default_evictor(){
    // Expected behavior: set should silently fail if insufficient memory remains to store a given value
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
    assert(c.get(key_1, val_1_size) != nullptr);
    assert(c.get(key_2, val_2_size) != nullptr);
    assert(c.get(key_3, val_3_size) == nullptr);
    c.del(key_1);
    c.set(key_3, val_3, val_3_size);
    assert(c.get(key_3, val_3_size) != nullptr);
}
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
    /*
     * Notes for future developement: add command line args to disable tests by group
     */
    std::cout << "Starting unit tests" << std::endl;
    test_set();
    std::cout << "Passed tests for Cache::set" << std::endl;
    test_get();
    std::cout << "Passed tests for Cache::get" << std::endl;
    test_del();
    std::cout << "Passed tests for Cache::del" << std::endl;
    test_space();
    std::cout << "Passed tests for Cache::space_used" << std::endl;
    test_reset();
    std::cout << "Passed tests for Cache::reset" << std::endl;
    test_default_evictor();
    std::cout << "Passed tests for default evictor" << std::endl;
    std::cout << "All unit tests passed!" << std::endl;
    return 0;
}
