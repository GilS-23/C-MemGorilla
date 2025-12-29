C-MemGorilla: Lightweight Memory Leak Tracker
A robust, minimal memory tracking utility for C programs. Designed to help developers detect memory leaks, prevent double-free crashes, and handle allocation failures gracefully.

🚀 Features
Leak Detection: Tracks all active allocations and reports them at exit.

Double-Free Protection: Prevents program crashes by validating pointers before deallocation.

Realloc Safety: Correctly handles realloc edge cases, ensuring tracking remains accurate even if memory is moved or allocation fails.

Detailed Reports: Provides the exact file name and line number for every leaked block.

Minimal Overhead: Uses an efficient Linked List with Double Pointer logic for fast insertions and deletions.

🛠 How it Works
The tracker uses C Preprocessor Macros to transparently wrap standard library functions (malloc, calloc, realloc, free).

Technical Highlights:
Avoiding Recursion: Uses a specific implementation flag (MEM_TRACKER_IMPLEMENTATION) to ensure the tracker calls the real malloc and not its own wrapper.

Defensive Programming: Implements manual null-termination for file names to prevent buffer overflows.

Double Pointer Optimization: The remove_node function utilizes MemoryNode** to handle list head modifications and middle-element deletions in a single, elegant loop.

📦 Usage
Include the files: Add mem_tracker.h and mem_tracker.c to your project.

Include the Header: Add #include "mem_tracker.h" to your source files.

Report: Call print_leak_report() at the end of your main() function.