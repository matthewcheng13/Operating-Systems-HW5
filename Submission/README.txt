Command to compile the thread-safe linked list with mutex:

make thread-safe

This will make a file called test2 where if you want to run the file you must do ./testMUTEX to run main.c.

Command to compile the lock-free linked list with CAS:

make lock-free

This will make a file called test1 where if you want to run the file you must do ./testCAS to run main_CAS.c.

You can remove the files made by Makefile by calling this command:

make clean