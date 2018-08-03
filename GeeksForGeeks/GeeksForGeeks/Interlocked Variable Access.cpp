/*

Applications must synchronize access to variables that are shared by multiple threads. 
Applications must also ensure that operations on these variables are performed atomically 
(performed in their entirety or not at all.)

Simple reads and writes to properly-aligned 32-bit variables are atomic operations.
In other words, you will not end up with only one portion of the variable updated; 
all bits are updated in an atomic fashion. 
However, access is not guaranteed to be synchronized. 
If two threads are reading and writing from the same variable, 
you cannot determine if one thread will perform its read operation before the other 
performs its write operation.

Simple reads and writes to properly aligned 64-bit variables are atomic on 64-bit Windows.					IMP
Reads and writes to 64-bit values are not guaranteed to be atomic on 32-bit Windows.						IMP
Reads and writes to variables of other sizes are not guaranteed to be atomic on any platform.				IMP

The Interlocked API
The interlocked functions provide a simple mechanism for synchronizing access to a variable					IMP - MultiThread
that is shared by multiple threads. They also perform operations on variables in 
an atomic manner. The threads of different processes can use these functions if the variable				IMP - across process
is in shared memory.

InterlockedIncrement
InterlockedDecrement 
The InterlockedIncrement and InterlockedDecrement functions combine the steps involved in 
incrementing or decrementing a variable into an atomic operation. This feature is useful 
in a multitasking operating system, in which the system can interrupt one thread's execution
to grant a slice of processor time to another thread. Without such synchronization, two threads
could read the same value, increment it by 1, and store the new value for a total increase of
1 instead of 2. The interlocked variable-access functions protect against this kind of error.				IMP - ++a, --a

InterlockedExchange 
InterlockedExchangePointer 
InterlockedExchangeAdd
The InterlockedExchange and InterlockedExchangePointer functions atomically exchange the					IMP - SwapVal,SwapPtr
values of the specified variables. The InterlockedExchangeAdd function combines two							IMP - a+=b;
operations: adding two variables together and storing the result in one of the variables.

InterlockedCompareExchange
InterlockedCompare64Exchange128
InterlockedCompareExchangePointer
The InterlockedCompareExchange, InterlockedCompare64Exchange128, and										IMP - A>B,A=C
InterlockedCompareExchangePointer functions combine two operations: 
comparing two values and storing a third value in one of the variables, based on the 
outcome of the comparison.

InterlockedAnd
InterlockedOr
InterlockedXor 
The InterlockedAnd, InterlockedOr, and InterlockedXor functions atomically perform AND,						IMP - &,|,^
OR, and XOR operations, respectively.

There are functions that are specifically designed to perform interlocked variable							IMP
access on 64-bit memory values and addresses, and are optimized for use on 64-bit Windows
. Each of these functions contains "64" in the name; for example, 
InterlockedDecrement64 and InterlockedCompareExchangeAcquire64.

Most of the interlocked functions provide full memory barriers on all Windows platforms						IMP-FullMemoryBarrier
. There are also functions that combine the basic interlocked variable access operations
with the acquire and release memory ordering semantics supported by certain processors.
Each of these functions contains the word "Acquire" or "Release" in their names; 
for example, InterlockedDecrementAcquire and InterlockedDecrementRelease. 

Acquire memory semantics specify that the memory operation being performed by the current					IMP-Protected Region
thread will be visible before any other memory operations are attempted. 
Release memory semantics specify that the memory operation being performed by the current 
thread will be visible after all other memory operations have been completed. 
These semantics allow you to force memory operations to be performed in a specific order. 
Use acquire semantics when entering a protected region and release semantics when leaving it.
*/
