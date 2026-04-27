Task Scheduler — DSA Project

A console-based Task Scheduler built in C++ that demonstrates the practical use of three core data structures:

Queue (FIFO) — Acts as an inbox where tasks are added and processed in order
Stack (LIFO) — Tracks action history to support undo functionality (add/complete)
Binary Search Tree (BST) — Stores completed tasks sorted by priority for efficient searching and ordered display
Features:

Add tasks with a name and priority level (1=High to 5=Least)
Process (complete) the next task in the inbox queue
Undo the last add or complete action
View inbox queue, undo history, and completed task log
Search completed tasks by priority using BST
Save and load all data to/from a text file (tasks_data.txt) for persistence across sessions
Tech: C++ · Linked-list Queue · Linked-list Stack · Binary Search Tree · File I/O
