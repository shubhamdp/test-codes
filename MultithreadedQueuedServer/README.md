# MultithreadedQueuedServer
multiple threaded server functionality using pthread.

Create a Generic Linked List data structure library.
Use this library to create raw data linked list by reading the data from file with each line data as new node.
Send this raw data linked list to server app
Server App should sort this data and send the sorted linked list back to client
The client should display the sorted list.

Implemented above feature with multiple threaded server functionality using pthread.

The server should create a thread to process the request received from client.
Note, there should be at max N threads running at a time i.e. the server should wait if already N threads are running.

The server should maintain the statistics of the time required to process the request, which can be queried any time later.
