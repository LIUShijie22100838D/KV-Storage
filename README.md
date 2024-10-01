The kv-storage supports SET, GET, MOD, DEL, EXIST command. You can specify which storage engine you want to use. 
The options are Red Black Tree, Hash Table and Array. If you want to use Red Black Tree to SET, type RSEET. If you want to use Hash Table to SET, type HSET. If you want to use array to SET, just type SET. So do GET, MOD, EXIST, DEL. 

Navigate to folder `kv`
Enter `make`
You may found that there are two executable files one is `kvstore`, one is `testcase`
Enter ./kvstore {port number} 
Open another terminal,navigate to the kv folder
Enter ./kvstore {IP address} {port number} {option} to execute the testcase (optional). 
If the option is 0, 90000 commands, which is made up from 10000 same groups with 9 commands. will be executed, and the storage engine is Red Black Tree.
If the option is 1, 30000 commands, which is made up from 10000 different groups with 3 commands will be executed. The storage engine is also Red Black Tree. 
If the option is 2, 90000 commands, which is made up from 10000 same groups with 9 commands. will be executed, and the storage engine is Array.
If the option is 3, 9 commands will be executed. The storage engine is Hash map.
You can also define your own test case in testcase.c
You can also do testing with py-test.py or network assistant. You can also define test cases in Java, Go, Rust et al. 

