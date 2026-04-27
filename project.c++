#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//  TASK — holds data for one task

struct Task {
    string name;
    int    priority;   // 1=High  2=Medium  3=Low  4=Very Low  5=Least
};

//  DATA STRUCTURE 1 — QUEUE  (Inbox, FIFO)
//  enqueue() adds to back, dequeue() removes from front.

struct QNode {
    Task  task;
    QNode* next;
};

class Queue {
private:
    QNode* frontPtr;
    QNode* backPtr;
    int    cnt;

public:
    Queue()  { 
        frontPtr = NULL;
        backPtr = NULL;
        cnt = 0;
        }

    ~Queue() { 
        while (!isEmpty()) dequeue();
     }

    bool isEmpty() { 
        return frontPtr == NULL;
    }
    int  size()    { 
        return cnt; 
    }

    void enqueue(Task t) {
        QNode* n  = new QNode();
        n->task   = t;
        n->next   = NULL;
        if (backPtr == NULL) { 
            frontPtr = n; 
            backPtr = n; 
        }
        else { 
            backPtr->next = n; 
            backPtr = n; 
        }
        cnt++;
    }

    Task dequeue() {
        Task t   = frontPtr->task;
        QNode* tmp = frontPtr;
        frontPtr = frontPtr->next;
        if (frontPtr == NULL) backPtr = NULL;
        delete tmp;
        cnt--;
        return t;
    }

    Task peekFront() { 
        return frontPtr->task; 
    }

    void display() {
        if (isEmpty()) { 
            cout << "  [Queue is empty]\n"; 
            return; 
        }
        cout << "  " << left;
        cout.width(4);  cout << "#";
        cout.width(26); cout << "Task Name";
        cout << "Priority\n";
        cout << "  " << string(44, '-') << "\n";
        QNode* curr = frontPtr;
        int i = 1;
        while (curr != NULL) {
            cout << "  ";
            cout.width(4);  cout << i;
            cout.width(26); cout << curr->task.name;
            cout << "P" << curr->task.priority;
            if (i == 1) cout << "   <-- FRONT (next to process)";
            cout << "\n";
            curr = curr->next;
            i++;
        }
    }

    // ---- file handling ----
    void saveToFile(ofstream& f) {
        f << "QUEUE " << cnt << "\n";
        QNode* curr = frontPtr;
        while (curr != NULL) {
            f << curr->task.name     << "\n";
            f << curr->task.priority << "\n";
            curr = curr->next;
        }
    }

    void loadFromFile(ifstream& f, int n) {
        for (int i = 0; i < n; i++) {
            Task t;
            getline(f, t.name);
            f >> t.priority;
            f.ignore();
            enqueue(t);
        }
    }
};

//  DATA STRUCTURE 2 — STACK  (Undo History, LIFO)
//  push() adds to top, pop() removes from top.

struct SNode {
    string actionType;   // "ADD" or "COMPLETE"
    Task   task;
    SNode* next;
};

class Stack {
private:
    SNode* topPtr;
    int    cnt;

public:
    Stack()  { topPtr = NULL; 
        cnt = 0; 
    }
    ~Stack() { 
        while (!isEmpty()) pop(); 
    }

    bool isEmpty() { 
        return topPtr == NULL; 
    }

    int  size()    { 
        return cnt; 
    }

    void push(string actionType, Task t) {
        SNode* n      = new SNode();
        n->actionType = actionType;
        n->task       = t;
        n->next       = topPtr;
        topPtr        = n;
        cnt++;
    }

    SNode pop() {
        SNode data = *topPtr;
        SNode* tmp = topPtr;
        topPtr     = topPtr->next;
        delete tmp;
        cnt--;
        return data;
    }

    SNode peek() { 
        return *topPtr; 
    }

    void display() {
        if (isEmpty()) { 
            cout << "  [Stack is empty]\n"; 
            return; 
        }
        cout << "  " << left;
        cout.width(4);  cout << "#";
        cout.width(12); cout << "Action";
        cout << "Task Name\n";
        cout << "  " << string(44, '-') << "\n";
        SNode* curr = topPtr;
        int i = 1;
        while (curr != NULL) {
            cout << "  ";
            cout.width(4);  cout << i;
            cout.width(12); cout << curr->actionType;
            cout << curr->task.name;
            if (i == 1) cout << "   <-- TOP (will be undone)";
            cout << "\n";
            curr = curr->next;
            i++;
        }
    }

    // ---- file handling ----
    void saveToFile(ofstream& f) {
        f << "STACK " << cnt << "\n";
        SNode* curr = topPtr;
        while (curr != NULL) {
            f << curr->actionType    << "\n";
            f << curr->task.name     << "\n";
            f << curr->task.priority << "\n";
            curr = curr->next;
        }
    }

    void loadFromFile(ifstream& f, int n) {
        // Items saved top-first; push in reverse to restore original order
        string types[200];
        Task   tasks[200];
        for (int i = 0; i < n; i++) {
            getline(f, types[i]);
            getline(f, tasks[i].name);
            f >> tasks[i].priority;
            f.ignore();
        }
        for (int i = n - 1; i >= 0; i--) push(types[i], tasks[i]);
    }
};

//  DATA STRUCTURE 3 — BST  (Completed Log)

struct BSTNode {
    Task     task;
    BSTNode* left;
    BSTNode* right;
};

class BST {
private:
    BSTNode* root;

    BSTNode* insertRec(BSTNode* node, Task t) {
        if (node == NULL) {
            BSTNode* n = new BSTNode();
            n->task    = t;
            n->left    = NULL;
            n->right   = NULL;
            return n;
        }
        if (t.priority < node->task.priority) node->left  = insertRec(node->left,  t);
        else                                   node->right = insertRec(node->right, t);
        return node;
    }

    void inorderPrint(BSTNode* node, int& i) {
        if (node == NULL) return;
        inorderPrint(node->left, i);
        cout << "  ";
        cout.width(4);  cout << i;
        cout.width(26); cout << node->task.name;
        cout << "P" << node->task.priority << "\n";
        i++;
        inorderPrint(node->right, i);
    }

    void inorderCollect(BSTNode* node, Task arr[], int& i) {
        if (node == NULL) return;
        inorderCollect(node->left, arr, i);
        arr[i++] = node->task;
        inorderCollect(node->right, arr, i);
    }

    BSTNode* searchRec(BSTNode* node, int p) {
        if (node == NULL)           return NULL;
        if (p == node->task.priority) return node;
        if (p <  node->task.priority) return searchRec(node->left,  p);
        return searchRec(node->right, p);
    }

    void destroy(BSTNode* node) {
        if (node == NULL) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST()  { 
        root = NULL; 
    }
    ~BST() { destroy(root); }

    void clear() { 
        destroy(root); 
        root = NULL; 
    }

    void insert(Task t) { 
        root = insertRec(root, t);
    }

    void display() {
        if (root == NULL) { 
            cout << "  [No completed tasks yet]\n"; 
            return; 
        }
        cout << "  " << left;
        cout.width(4);  cout << "#";
        cout.width(26); cout << "Task Name";
        cout << "Priority\n";
        cout << "  " << string(44, '-') << "\n";
        int i = 1;
        inorderPrint(root, i);
    }

    void search(int p) {
        BSTNode* res = searchRec(root, p);
        if (res) cout << "\n  Found: '" << res->task.name << "'  [P" << res->task.priority << "]\n";
        else     cout << "\n  No completed task with priority P" << p << ".\n";
    }

    // Collect all nodes into array (in-order)
    int collect(Task arr[]) {
        int i = 0;
        inorderCollect(root, arr, i);
        return i;
    }

    // ---- file handling ----
    void saveToFile(ofstream& f) {
        Task arr[200];
        int  n = collect(arr);
        f << "BST " << n << "\n";
        for (int i = 0; i < n; i++) {
            f << arr[i].name     << "\n";
            f << arr[i].priority << "\n";
        }
    }

    void loadFromFile(ifstream& f, int n) {
        for (int i = 0; i < n; i++) {
            Task t;
            getline(f, t.name);
            f >> t.priority;
            f.ignore();
            insert(t);
        }
    }
};

//  HELPER FUNCTIONS

void printHeader(string title) {
    cout << "\n" << string(50, '=') << "\n";
    cout << "   " << title << "\n";
    cout << string(50, '=') << "\n";
}

void printMenu() {
    printHeader("TASK SCHEDULER  —  MAIN MENU");
    cout << "  1.  Add new task        \n";
    cout << "  2.  Process next task   \n";
    cout << "  3.  Undo last action    \n";
    cout << "  4.  View inbox queue\n";
    cout << "  5.  View undo history   \n";
    cout << "  6.  View completed log  \n";
    cout << "  7.  Search completed    \n";
    cout << "  8.  Save data to file\n";
    cout << "  9.  Load data from file\n";
    cout << "  0.  Exit\n";
    cout << string(50, '-') << "\n";
}

int getIntInput(string prompt, int lo, int hi) {
    int v;
    while (true) {
        cout << prompt;
        cin  >> v;
        cin.ignore();
        if (v >= lo && v <= hi) return v;
        cout << "  Please enter a number between " << lo << " and " << hi << ".\n";
    }
}

void saveData(Queue& q, Stack& s, BST& b) {
    ofstream f("tasks_data.txt");
    if (!f.is_open()) { cout << "  [Error: cannot open file for saving]\n"; return; }
    q.saveToFile(f);
    s.saveToFile(f);
    b.saveToFile(f);
    f.close();
    cout << "\n  [Data saved to tasks_data.txt]\n";
}

void loadData(Queue& q, Stack& s, BST& b) {
    ifstream f("tasks_data.txt");
    if (!f.is_open()) { cout << "  [No save file found. Starting fresh.]\n"; return; }
    string section;
    int cnt;
    f >> section >> cnt; 
    f.ignore(); 
    if (section == "QUEUE") q.loadFromFile(f, cnt);
    
    f >> section >> cnt; 
    f.ignore(); 
    if (section == "STACK") s.loadFromFile(f, cnt);
    
    f >> section >> cnt; 
    f.ignore(); 
    if (section == "BST")   b.loadFromFile(f, cnt);
    
    f.close();
    cout << "  [Data loaded from tasks_data.txt]\n";
}

//  MAIN — runs in a loop until the user exits

int main() {
    Queue inbox;
    Stack undoHist;
    BST   doneLog;

    printHeader("Welcome to Task Scheduler");
    cout << "  Save file  : tasks_data.txt\n";
    cout << "\n";

    loadData(inbox, undoHist, doneLog);   // auto-load on startup

    char choice;

    // ────────────────── MAIN LOOP ──────────────────────────
    while (true) {
        printMenu();
        cout << "  Enter choice (0-9): ";
        cin  >> choice;
        cin.ignore();

        // ── 1. ADD TASK ────────────────────────────────────
        if (choice == '1') {
            printHeader("Add New Task");
            Task t;
            cout << "  Task name: ";
            getline(cin, t.name);
            if (t.name.empty()) {
                cout << "  Task name cannot be empty.\n";
            } else {
                t.priority = getIntInput(
                    "  Priority (1=High  2=Medium  3=Low  4=Very Low  5=Least): ",
                    1, 5
                );
                inbox.enqueue(t);
                undoHist.push("ADD", t);
                cout << "\n  Added: '" << t.name << "'  [P" << t.priority << "]  to inbox queue.\n";
                cout << "  Queue size: " << inbox.size() << "\n";
            }
        }

        // ── 2. PROCESS NEXT TASK ───────────────────────────
        else if (choice == '2') {
            printHeader("Process Next Task");
            if (inbox.isEmpty()) {
                cout << "  Inbox is empty. No tasks to process.\n";
            } else {
                Task t = inbox.dequeue();
                doneLog.insert(t);
                undoHist.push("COMPLETE", t);
                cout << "\n  Completed : '" << t.name << "'  [P" << t.priority << "]\n";
                cout << "  Moved to completed log.\n";
                cout << "  Remaining in queue: " << inbox.size() << "\n";
            }
        }

        // ── 3. UNDO LAST ACTION ────────────────────────────
        else if (choice == '3') {
            printHeader("Undo Last Action");
            if (undoHist.isEmpty()) {
                cout << "  Nothing to undo.\n";
            } else {
                SNode action = undoHist.pop();

                if (action.actionType == "ADD") {
                    // Remove that task from the queue
                    Queue temp;
                    while (!inbox.isEmpty()) {
                        Task t = inbox.dequeue();
                        if (t.name != action.task.name) temp.enqueue(t);
                    }
                    while (!temp.isEmpty()) inbox.enqueue(temp.dequeue());
                    cout << "  Undid ADD: '" << action.task.name << "' removed from queue.\n";

                } else if (action.actionType == "COMPLETE") {
                    // Collect BST tasks, rebuild without the undone one
                    Task allDone[200];
                    int  n = doneLog.collect(allDone);
                    doneLog.clear();
                    for (int i = 0; i < n; i++) {
                        if (allDone[i].name != action.task.name)
                            doneLog.insert(allDone[i]);
                    }
                    // Put task back at front of queue
                    Queue temp;
                    temp.enqueue(action.task);
                    while (!inbox.isEmpty()) temp.enqueue(inbox.dequeue());
                    while (!temp.isEmpty())  inbox.enqueue(temp.dequeue());
                    cout << "  Undid COMPLETE: '" << action.task.name << "' restored to queue front.\n";
                }
            }
        }

        // ── 4. VIEW QUEUE ──────────────────────────────────
        else if (choice == '4') {
            printHeader("Inbox Queue  (FIFO Order)");
            inbox.display();
        }

        // ── 5. VIEW STACK ──────────────────────────────────
        else if (choice == '5') {
            printHeader("Undo History  (LIFO Stack)");
            undoHist.display();
        }

        // ── 6. VIEW COMPLETED ──────────────────────────────
        else if (choice == '6') {
            printHeader("Completed Log  (BST In-Order by Priority)");
            doneLog.display();
        }

        // ── 7. SEARCH BST ──────────────────────────────────
        else if (choice == '7') {
            printHeader("Search Completed Tasks (BST)");
            int p = getIntInput("  Enter priority to search (1-5): ", 1, 5);
            doneLog.search(p);
        }

        // ── 8. SAVE ────────────────────────────────────────
        else if (choice == '8') {
            saveData(inbox, undoHist, doneLog);
        }

        // ── 9. LOAD ────────────────────────────────────────
        else if (choice == '9') {
            printHeader("Load Data from File");
            Queue freshQ; 
            Stack freshS; 
            BST freshB;
            
            inbox    = Queue();
            undoHist = Stack();
            doneLog.clear();
            loadData(inbox, undoHist, doneLog);
        }

        // ── 0. EXIT ────────────────────────────────────────
        else if (choice == '0') {
            printHeader("Goodbye!");
            char sc;
            cout << "  Save data before exit? (y/n): ";
            cin  >> sc;
            if (sc == 'y' || sc == 'Y') saveData(inbox, undoHist, doneLog);
            cout << "  Exiting Task Scheduler. Bye!\n\n";
            break;
        }

        // ── INVALID ────────────────────────────────────────
        else {
            cout << "  Invalid choice. Please enter 0-9.\n";
        }

        cout << "\n  Press Enter to continue...";
        cin.ignore();
    }

    return 0;
}
