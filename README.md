# 📋 Task Scheduler — DSA Project

> A console-based **Task Scheduler** built in **C++** that puts three core data structures to real, practical use — not just theory.

---

## 🧠 Data Structures Used

| Structure | Role | Behavior |
|-----------|------|----------|
| **Queue** (Linked-list) | Task Inbox | Tasks are added and processed in order (**FIFO**) |
| **Stack** (Linked-list) | Undo History | Tracks the last add or complete action (**LIFO**) |
| **BST** (Binary Search Tree) | Completed Log | Stores finished tasks sorted by priority for fast search & ordered display |

---

## ✨ Features

- ➕ **Add tasks** with a name and priority level (`1 = High` → `5 = Least`)
- ✅ **Process tasks** — complete the next task in the inbox queue
- ↩️ **Undo** the last `add` or `complete` action
- 👁️ **View** inbox queue, undo history stack, and completed task log
- 🔍 **Search** completed tasks by priority using BST traversal
- 💾 **Persist data** — save and load all tasks to/from `tasks_data.txt`

---

## 🛠️ Tech Stack

- **Language:** C++
- **Data Structures:** Linked-list Queue · Linked-list Stack · Binary Search Tree
- **Other:** File I/O (`tasks_data.txt` for persistence across sessions)

---

## 🚀 Getting Started

### Compile

```bash
g++ -o task_scheduler main.cpp
```

### Run

```bash
./task_scheduler
```

> Tasks are automatically saved to `tasks_data.txt` and reloaded on the next run.

---

## 📁 Project Structure

```
task-scheduler/
├── main.cpp          # Entry point & menu logic
├── tasks_data.txt    # Persistent task storage (auto-generated)
└── README.md
```
---

## 📌 Priority Levels

| Level | Meaning |
|-------|---------|
| `1` | 🔴 High |
| `2` | 🟠 Medium-High |
| `3` | 🟡 Medium |
| `4` | 🟢 Low |
| `5` | ⚪ Least |

---

## 👤 Author

**Muhammad Zakria**
- 🔗 [GitHub](https://github.com/Md-zakria)
- 💼 [LinkedIn](https://linkedin.com/in/muhammad-zakria-9914a0325)

---

## 📚 About

This project was built as part of my **Data Structures & Algorithms** coursework to demonstrate real-world application of DSA concepts — moving beyond textbook examples and into a working, interactive system.
