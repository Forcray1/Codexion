*This project has been created as part of the 42 curriculum by <login1>.*

# Codexion

## Description
Codexion is a concurrency simulation project where multiple coders compete for limited USB dongles in a shared co-working hub. Each coder must regularly compile quantum code using two dongles, while also debugging and refactoring. The challenge is to orchestrate resource sharing and scheduling using POSIX threads, mutexes, and condition variables, ensuring no coder burns out due to lack of access. The project models real-world issues of resource contention, synchronization, and fairness in collaborative environments.

## Instructions
- **Compilation:**
  - Run `make` in the project root to build the program.
  - The Makefile supports the rules: `all`, `clean`, `fclean`, `re`.
- **Execution:**
  - Usage:
    ```sh
    ./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
    ```
  - Example:
    ```sh
    ./codexion 4 800 200 200 200 3 100 fifo
    ```
  - `scheduler` must be either `fifo` (First In, First Out) or `edf` (Earliest Deadline First).
- **Requirements:**
  - All arguments are mandatory and must be valid (positive integers, valid scheduler).
  - The program logs coder actions and burnout events with precise timestamps.

## Blocking cases handled
- **Deadlock prevention:** To finish.
- **Starvation prevention:** To finish.
- **Cooldown handling:** Argument parsing and validation coded, logic to finish.
- **Precise burnout detection:** Monitor thread structure present, logic to finish.
- **Log serialization:** To finish.

## Thread synchronization mechanisms
- **Mutexes (`pthread_mutex_t`):** Used for dongle access and stop condition. More logic to finish.
- **Condition variables (`pthread_cond_t`):** To finish.
- **Monitor thread:** Structure present, logic to finish.
- **Thread-safe communication:** To finish.
## Project status
- Argument parsing and validation: implemented (`main.c`, `check_value.c`)
- Environment and coder structure: present (`codexion.h`)
- Dongle acquisition and release: basic logic present (`simulation.c`)
- Monitor thread: structure present (`monitor.c`)
- Utility functions: implemented (`utils.c`)
- Cleanup: stub present (`cleanup.c`)
- Logging and full simulation logic: to finish

## Resources
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [Beej’s Guide to POSIX Mutexes](https://beej.us/guide/bgc/html/split/pthread.html)
- [Concurrency (Wikipedia)](https://en.wikipedia.org/wiki/Concurrency_(computer_science))
- [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- **AI usage:**
  - AI was strictly used for suggestion of resources, and as a teaching tool for new notions.

## Example log output
```
0 1 has taken a dongle
1 1 has taken a dongle
1 1 is compiling
201 1 is debugging
401 1 is refactoring
402 2 has taken a dongle
403 2 has taken a dongle
403 2 is compiling
603 2 is debugging
803 2 is refactoring
1204 3 burned out
```

