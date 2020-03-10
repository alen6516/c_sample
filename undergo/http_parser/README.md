* mode
    * choose select/poll/epoll for now

* data storage
    * fd => in array
        * only store fd
    * thr_node => in array
        * store thread info
        * including parse_buf
    * conn_node => hash_table
        * fd as key for each node
        * store conn states
