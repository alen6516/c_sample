## weekly meeting time

- Tue 3 pm with mentor
- Fri 09:30 am with HQ

## scope 

- methods to implemented
    - GET
    - HEAD
    - POST
    - DELETE
    - PUT
- status code to implemented
    - 200 OK
    - 204 No Content
    - 400 Bad Request
    - 404 Not Found
    - 500 Internal Server Error
- log
    - access log
        - save in www/log/access.log
        - record normal request and reply
    - error log
        - save in www/log/error.log
        - record errors during the runtime of the server
- counter
    - Server Uptime
    - connections
    - requests

## weekly objective

- week 1 (10/1 ~ 10/4)
    - basic request-reply architecture
    - method: GET
    - status code: 200, 404
- week 2 (10/7 ~ 10/9)
    - basic logging and counter module
    - http persistent connection
- week 3 (10/14 ~ 10/18)
    - methods: HEAD, POST, DELETE, PUT
    - status code: 
- week 4 (10/21 ~ 10/24)

## how to test

- how to test each functions
    - a table (functionality and script)
    - what function support and how to test

| function                 | script     | expected behavior                           |
| ------------------------ | ---------- | ------------------------------------------- |
| GET an existing file     | GET_200.sh | receive 200 OK with the file data           |
| GET an non-existing file | GET_404.sh | receive 404 Not Found with the default page |
|                          |            |                                             |


