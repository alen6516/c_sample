* TCP chat room
## Function
* multiple user chat room, no limit on the number of the users
* once enter the room, user need to log their name
* use TCP
* use select
    * next step we can use non-blocking socket

## File
* server.c
    * target server code
* client.c
    * target client code
* client_table.c client_table.h
    * for server to store client info, including socket and name
* _server.c
    * old server code

* poll dir
    * old poll example, deprecated
* test dir
    * put some test code

## update in 5/31
decide to use select.
poll version is main.c and select version is server.c

## Next
use libevent
