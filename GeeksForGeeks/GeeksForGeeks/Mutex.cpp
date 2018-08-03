/*
//https://docs.microsoft.com/en-us/windows/desktop/sync/mutex-objects

A mutex object is a synchronization object whose state is set to				IMP
signaled when it is not owned by any thread, and nonsignaled when 
it is owned. 

Only one thread at a time can own a mutex object, whose name comes				IMP
from the fact that it is useful in coordinating mutually 
exclusive access to a shared resource. 

A thread uses the CreateMutex or CreateMutexEx function to create a			
mutex object. 
The creating thread can request immediate ownership of the mutex object			IMP
and can also specify a name for the mutex object. 
It can also create an unnamed mutex. 

Threads in other processes can open a handle to an existing named mutex 
object by specifying its name in a call to the OpenMutex function. 
To pass a handle to an unnamed mutex to another process, 
use the DuplicateHandle function or parent-child handle inheritance.

Any thread with a handle to a mutex object can use one of the wait 
functions to request ownership of the mutex object. 
If the mutex object is owned by another thread, the wait function blocks 
the requesting thread until the owning thread releases the mutex object 
using the ReleaseMutex function. 
The return value of the wait function indicates whether the function 
returned for some reason other than the state of the mutex being set to signaled.

If more than one thread is waiting on a mutex, a waiting thread is selected. 
Do not assume a first-in, first-out (FIFO) order.									V-IMP
External events such as kernel-mode APCs can change the wait order.

After a thread obtains ownership of a mutex, it can specify the same mutex 
in repeated calls to the wait-functions without blocking its execution.				IMP
This prevents a thread from deadlocking itself while waiting for a mutex 
that it already owns. To release its ownership under such circumstances, 
the thread must call ReleaseMutex once for each time that the mutex 
satisfied the conditions of a wait function.

If a thread terminates without releasing its ownership of a mutex object,			IMP		Abandoned
the mutex object is considered to be abandoned. 
A waiting thread can acquire ownership of an abandoned mutex object,					can reuse abondend mutex
but the wait function will return WAIT_ABANDONED to indicate that the mutex object 
is abandoned. An abandoned mutex object indicates that an error has 
occurred and that any shared resource being protected by the mutex object 
is in an undefined state. If the thread proceeds as though the mutex 
object had not been abandoned, it is no longer considered abandoned after 
the thread releases its ownership. 
This restores normal behavior if a handle to the mutex object is 
subsequently specified in a wait function.

Note that critical section objects provide synchronization similar					IMP
to that provided by mutex objects, except that 
critical section objects can be used only by the threads of a single process.



*/