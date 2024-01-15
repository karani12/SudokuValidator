## Sudoku Validator

This is a sudoku validator. I am learning about OS and all about
threading and concurrency. The sudoku validator will create two threads.
The concept of threading and concurrency are very important in understanding some concepts in software engineering.

> A thread is basically a unit of work in a cpu

- Multicore systems allow for parallelism i.e multiple threads making progress simultaneously.
- Single core systems allow for concurrency when multiple threads are making progress.

**AIM**
- To learn more about creating threads in an operating system


### Some problems with threading
- Data sharing
- Balancing work
- identifying any data dependencies

### User vs Kernel threads
Users basically create threads that must be mapped to kernel threads. Usually these
kernel threads will perform the syscall. There are different modes of mapping user threads to kernel thread.

### An example of threading pseudo

```
Task(problem)
if problem is small enough
solve the problem directly
else
subtask1 = fork(new Task(subset of problem)
subtask2 = fork(new Task(subset of problem)
result1 = join(subtask1)
result2 = join(subtask2)
return combined results
```


