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

## update in 5/31
decide to use select.
poll version is main.c and select version is server.c
