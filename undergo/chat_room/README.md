* TCP chat room
## Function
* multiple user chat room, no limit on the number of the users
* once enter the room, user need to log their name
* use TCP

* directory structure
    * main.c
    * define.h
    * config.h
    * func.h
* data structure
    * fd => array
    * conn => hash_table
    * parse_buf + thr_list => thr_node_list
