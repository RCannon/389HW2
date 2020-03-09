CSCI 389 HW2

Authors: Reilly Cannon and James McCaull

This github repo should include all of the required files for this assignment, as well as the extra credit LRU Evictor files, all of which should be functioning. 

We placed our tests for each part of this assignment into the test_cache_lib.cc file. To run this test file, construct test_cache_lib.exe using the included Makefile. 

We utilized the standard template library unordered_map container throughout this project, and we used its various methods extensively in each part. This helped us ensure that all operations run in asymptotically constant time, as requested. 

Collision resolution is handled natively by the unordered_map. We chose to stick with the native implementation because it is simplier and most likely better performing and less bug-ridden than anything we could write.

Dynamic resizing as also handled natively by the unordered map. We can pass the desired maximum load factor to the map as an argument when first creating our cache, and the map will resize without lossing data whenever that load factor is reached.

We implemented a FIFO eviction policy by inheriting from the given evictor class. The class contains a std::queue that we use to hold the keys of the next items to be evicted.
Touching the key simply pushes it onto the back of the queue, and calling the eviction function simply pops the first key off the front, and returns it to the caller.

Finally, for extra credit we implemented a LRU evictor. To do this, used a doubly-linked list to store the keys in the order of least recently used to most recently used. We then used another instance of std::unordered_map to store pointers to each of the nodes in the linked list. This allowed for constant time access of any node in the list, as well as constant time rearrangement of elements based on which key has just been touched. This workes because we are merely changing what nodes the pointers point to, and at most we have to change a constant number of pointers to rearrange a single element in the list.


