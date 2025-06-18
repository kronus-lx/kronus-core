# Multithreading 

std::thread				==> represents a single thread of execution
std::mutex				==> is a synchronisation primitive that can be used to protect shared data from teh accessed by multiple threads
std::condition_variable ==> is something used with mutexs - To block one or more threads, until another thread does two things
		- Modify a shared variable
		- Notifies the condition_variable

# Perfect Forwarding

std::forward	   ==> is used to implement perfect forwarding. Perfect forwarding is the process of forwarding arguments in such a way that contains its original value type.
std::bind		   ==> class is used for partial function application, meaning if the arguments are pre-specified, it generates a forwarding call wrapper for hte function.
std::future		   ==> provides a method to access the results of asynchronous operations. They are associated with a shared state and can be constructed by using std::packaged_task.
std::packaged_task ==> wraps any callable target so it can be called asynchronously