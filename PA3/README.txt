Program: P3
Class: CS370
Author: Sadie Henry
Date: 11/10/2015

TO RUN THE PROGRAM: java Main <buffer size> <number of items> <max wait time>

Main.java:
This class contains the main method for the entire program. It creates a bounded buffer
and runs a producer then a consumer in non-parallel. It then creates, starts, and joins
2 producer threads and 1 consumer thread. This class handles error checking for invalid arguments.

BoundedBuffer.java:
This class creates a bounded buffer that is FIFO. The add and remove methods are synchronized so
that only one thread can access each of them at a time. This provides mutual exclusion and helps
with preventing deadlock.

Consumer.java:
This class removes items from the given bounded buffer in either a parallel or a non-parallel fashion.
If the consumer is not parallel and is told to consume more items than are in the buffer, it will print that 
it is unable to consume once and then finish. Handling for this case was not specified in the assignment, 
so this is how I chose to handle it. All buffer access in this class is synchronized.

Producer.java:
This class adds random doubles to the given bounded buffer in either a parallel or a non-parallel 
fashion. If the producer is not parallel and is told to produce more items than the size of the buffer, it will print
that it is unable to produce once and then finish. Handling for this case was not specified in the assignment, 
so this is how I chose to handle it. All buffer access in this class is synchronized. 

NOTE: I did not use the Buffer Size which was passed to the Consumer and Producer. I could find no use for it.
