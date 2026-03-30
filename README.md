*This project has been created as part of the 42 curriculum by mlorenzo.*

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
- **Deadlock prevention:** Coders never enter a deadlock state when acquiring dongles. Coffman’s conditions are broken by careful scheduling and resource acquisition order.
- **Starvation prevention:** Both FIFO and EDF scheduling prevent coders from being indefinitely denied access to dongles.
- **Cooldown handling:** After release, each dongle enforces a cooldown period before it can be acquired again.
- **Precise burnout detection:** A dedicated monitor thread checks coder states and logs burnout within 10ms of occurrence.
- **Log serialization:** All output is protected by a mutex to prevent interleaved or corrupted log messages.

## Thread synchronization mechanisms
- **Mutexes (`pthread_mutex_t`):** Protect each dongle’s state and the logging output. Ensure atomic access to shared resources and prevent race conditions.
- **Condition variables (`pthread_cond_t`):** Used to implement waiting queues for dongles and to signal availability after cooldown.
- **Monitor thread:** Continuously checks for coder burnout and simulation end conditions.
- **Thread-safe communication:** Coders and the monitor interact only through shared, mutex-protected state and condition variables, ensuring safe coordination without global variables.

## Project status
- Argument parsing and validation: implemented (`main.c`, `check_value.c`)
- Environment and coder structure: present (`codexion.h`)
- Dongle acquisition and release: implemented (`simulation.c`)
- Monitor thread: implemented (`monitor.c`)
- Utility functions: implemented (`utils.c`, `utils2.c`)
- Cleanup: implemented but not tested (`cleanup.c`)
- Logging and full simulation logic: implemented (`scheduler.c`)

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