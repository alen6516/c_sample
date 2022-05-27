* gen_rand_str.sh
    * script to generate random strings to file "text"

* hash_table.c

* hash_table.h

* unit_test.c
    * unit test each API of the node and the hash table

* test_table.c
    * a single thread tool to simulate a user to operate the hash table

* test.c
    * user program to simulate multiple insertion and deletion

* string hash comed from this page: https://stackoverflow.com/questions/7666509/hash-function-for-string

 
/*
 * implement a hash table to store strings
 * struct:
 *  node
 *  table
 * api:
 *  get_hash_key
 *  get_hash_code
 *  table_insert
 *  table_search
 *  table_dump
 *
 * todo:
 *  Phase 1: build arch
 *  1. (Done) read string from file
 *  2. (Skip) make Table/Node object-oriented
 *  3. (Done) write unit_test.c
 *  3. (Done) isolate table.h and make unit_test.c
 *  4. (Done) write Makefile
 *  5. (Ongo) write test.c
 *
 *  Phase 2: thread-safe
 *  1. make it thread-safe
 *  2. write user thread to test
 *
 *  Phase 3: performance tune
 *  1. use perf to test performance
 */  
