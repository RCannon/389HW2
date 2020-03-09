CSCI 389 HW2

Authors: Reilly Cannon (reicannon@reed.edu ) and James McCaull (jamccaull@reed.edu)

This repository contains all the required files for this assignment, as well as the extra credit LRU Evictor files. We've included a makefile to make compiling our testing file (test_cache_lib) easier.

Part 1: basic cache operations

We implemented Cache::del(key), Cache::set(key), and Cache::get(key) using the stl unordered_map container to make lookup, insertion and deletion constant time. The map also handles dynamic resizing for us by default (which still leaves us with constant amortized runtime of set). We decided to store our values on the heap, which lets us deep-copy them. However, when we return values from get, we give a pointer directly to the value in the cache. We thought about whether it was better to trust the user not to write using this pointer versus trusting the user to delete the new pointer they were given, and decided that the first one was better.


Part 2: Testing

We put all of our tests into test_cache_lib.cc, which runs a series of smaller test scripts to put each method and feature promised in cache.hh through its paces. Each method has its own separate routine to keep the tests simple and ensure that they're complete. Our tests all use cstrings as data, but the methods tested will work for any data type. 

Please note that test_fifo_evictor.cc is out of date with the current implementation and is not used for any of our tests.

Part 3: Performance

Using an unordered_map as the basis for our cache operations gives us the required performance for free. Since the stl unordered map allows the user to set the hash function, we just take the hash function provided when the cache is initialized and pass it to the map.

Part 4: Collision resolution

The stl unordered_map handles collision automatically, so we don't need to worry about that beyond making sure that we are using the map correctly.

Part 5: Dynamic resizing

The stl unordered_map handles dynamic resizing automatically. Again, this means we don't need to worry about resizing as long as we base our operations on the map. This is a major factor in why we chose to use the stl unordered_map instead of our own map implementation.

Part 6: Eviction policy

We implemented a FIFO eviction policy in fifo_evictor.hh and .cc, based on the guidelines suggested in the project description. This evictor uses a std::queue that holds the keys of items in our cache. Touching a key pushes it onto the back of the queue, and calling evict() pops the first key off the front, and returns it to the caller. Since we're using a queue, all of the relevant operations remain constant time. The tests for our FIFO evictor are in test_cache_lib, set to run automatically after our basic tests.
One (perhaps) notable design choice we made here was to check for overwriting before calling the evictor, which can save unnecessary eviction in the case of an overwrite with Cache::set().

Part 7: LRU

For extra credit we implemented a LRU evictor. It uses a doubly-linked list to store the keys in the order of least recently used (the front of the list) to most recently used (the back of the list). We then used another unordered_map to link keys to the corresponding nodes in the linked list. This gives us constant time access of any node in the list, while the list structure gives us constant time removal and insertion. This lets us use the evictor while keeping all the relevant operations in constant time. The evictor itself stores an unordered_map and a linked list, each with a number of elements equal to the number of items stored in the cache.
