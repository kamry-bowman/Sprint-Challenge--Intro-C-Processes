**1. List all of the main states a process may be in at any point in time on a standard Unix system. Briefly explain what each of these states means.**

- Created: when a process is created but has not yet begun to run
- user-mode, running: when a regular process not part of the kernel is running with normal user privileges
- kernel-mode, running: when a process needs to make a system call and so transfers to kernel
- Sleep: when a process needs something to occur before it can continue, so the process puts it to sleep, and will reinitialize when needed.
- Zombie: when a process has exited but its parent has not read its exit code.

**2. What is a zombie process?**
A zombie process is a child process that has exited, and is no longer running, but still has its exit value to return to its parent process.

**3. How does a zombie process get created? How does one get destroyed?**
A zombie process is created when a child process exits, and its parent hasn't read its exit code. A parent process can read the child's exit code with a `wait()` call, which will destroy the zombie process. Otherwise, once the parent exits, the child will be adopted by the init process, which will then reap them and allow the child process to leave zombie state and be destroyed. However, if the parent process never exits, this could create a scenario where child processes continue in zombie state long term.

**4. What are some of the benefits of working in a compiled language versus a non-compiled language? More specifically, what benefits are there to be had from taking the extra time to compile our code?**
The code can then be written in a way that is easy for humans to parse and reason about, but then converted to a format that is maximally efficient for the computer hardware to consume.
