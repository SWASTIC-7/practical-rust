#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int id;
    char* title;  // This is Heap allocated 
    bool done;
} Task;

typedef struct {
    Task** tasks;  // Array of pointers 
    int count;
    int capacity;
    int next_id;
} TaskManager;

TaskManager* manager_new() {
    TaskManager* m = malloc(sizeof(TaskManager));
    m->tasks = malloc(sizeof(Task*) * 10);
    m->count = 0;
    m->capacity = 10;
    m->next_id = 1;
    return m;
}

int manager_create(TaskManager* m, const char* title) {
    Task* task = malloc(sizeof(Task));
    task->id = m->next_id++;
    task->title = malloc(strlen(title) + 1);
    strcpy(task->title, title);
    task->done = false;
    
    m->tasks[m->count++] = task;
    return task->id;
}

Task* manager_get(TaskManager* m, int id) {
    for (int i = 0; i < m->count; i++) {
        if (m->tasks[i]->id == id) {
            return m->tasks[i];  // ⚠️ Returns internal pointer!
        }
    }
    return NULL;
}

void manager_delete(TaskManager* m, int id) {
    for (int i = 0; i < m->count; i++) {
        if (m->tasks[i]->id == id) {
            free(m->tasks[i]->title);
            free(m->tasks[i]);
            // Shift remaining tasks
            for (int j = i; j < m->count - 1; j++) {
                m->tasks[j] = m->tasks[j + 1];
            }
            m->count--;
            return;
        }
    }
}

void manager_free(TaskManager* m) {
    for (int i = 0; i < m->count; i++) {
        free(m->tasks[i]->title);
        free(m->tasks[i]);
    }
    free(m->tasks);
    free(m);
}

// ==================== BUG #1: USE AFTER FREE ====================
void bug_use_after_free() {
    printf("\n=== BUG #1: Use After Free ===\n");
    
    TaskManager* m = manager_new();
    int id = manager_create(m, "Learn C");
    
    Task* task = manager_get(m, id);  // Get pointer to task
    printf("Task: %s\n", task->title);  // Works fine
    
    manager_delete(m, id);  // Task is freed!
    
    // ❌ UNDEFINED BEHAVIOR - task points to freed memory
    printf("Task after delete: %s\n", task->title);  // 💥 Crash or garbage!
    
    manager_free(m);
}

// ==================== BUG #2: DOUBLE FREE ====================
void bug_double_free() {
    printf("\n=== BUG #2: Double Free ===\n");
    
    TaskManager* m = manager_new();
    int id = manager_create(m, "Learn memory safety");
    
    Task* task = manager_get(m, id);
    
    // Someone thinks they're being helpful and frees the task
    free(task->title);
    free(task);
    
    // Later, manager_free tries to free it again
    // ❌ DOUBLE FREE - undefined behavior, security vulnerability
    manager_free(m);  // 💥 Crash!
}

// ==================== BUG #3: MEMORY LEAK ====================
void bug_memory_leak() {
    printf("\n=== BUG #3: Memory Leak ===\n");
    
    TaskManager* m = manager_new();
    manager_create(m, "Task 1");
    manager_create(m, "Task 2");
    manager_create(m, "Task 3");
    
    // Oops, forgot to call manager_free(m)!
    // ❌ All memory leaked - tasks, titles, manager struct
    
    printf("Function returns without freeing... memory leaked!\n");
}

// ==================== BUG #4: DANGLING POINTER IN ARRAY ====================
void bug_dangling_in_collection() {
    printf("\n=== BUG #4: Dangling Pointer ===\n");
    
    TaskManager* m = manager_new();
    manager_create(m, "Task A");
    manager_create(m, "Task B");
    
    // Store pointers to tasks
    Task* first = manager_get(m, 1);
    Task* second = manager_get(m, 2);
    
    // Delete first task - array shifts!
    manager_delete(m, 1);
    
    // ❌ 'first' is now dangling
    // ❌ 'second' might still work, but its index changed
    
    printf("After delete, accessing 'first': ");
    // printf("%s\n", first->title);  // 💥 Would crash!
    printf("(would crash)\n");
    
    manager_free(m);
}

// ==================== BUG #5: WHO OWNS THIS STRING? ====================
char* bug_unclear_ownership() {
    printf("\n=== BUG #5: Unclear String Ownership ===\n");
    
    TaskManager* m = manager_new();
    manager_create(m, "Important task");
    
    Task* task = manager_get(m, 1);
    
    // Get the title... but who owns it?
    char* title = task->title;
    
    manager_free(m);  // Frees the title too!
    
    // ❌ 'title' is now dangling
    // printf("Title: %s\n", title);  // 💥 Would crash!
    
    return title;  // ❌ Returning dangling pointer!
}

// ==================== BUG #6: ALIASING MUTATION ====================
void bug_aliasing() {
    printf("\n=== BUG #6: Aliasing Mutation ===\n");
    
    TaskManager* m = manager_new();
    manager_create(m, "Original title");
    
    Task* task1 = manager_get(m, 1);
    Task* task2 = manager_get(m, 1);  // Same task, two pointers!
    
    // Modify through task1
    free(task1->title);
    task1->title = malloc(20);
    strcpy(task1->title, "New title");
    
    // task2 sees the change (aliasing)
    printf("task2->title: %s\n", task2->title);  // "New title"
    
    // But what if we freed through task1?
    // free(task1->title);
    // printf("%s\n", task2->title);  // 💥 Crash!
    
    manager_free(m);
}

// ==================== MAIN ====================
int main() {
    printf("╔════════════════════════════════════════╗\n");
    printf("║  C Ownership Bugs That Rust Prevents   ║\n");
    printf("╚════════════════════════════════════════╝\n");
    
    // Uncomment each to see the bug (some will crash!)
    
    // bug_use_after_free();      // 💥 Undefined behavior
    // bug_double_free();         // 💥 Crash
    bug_memory_leak();            // Silent corruption
    bug_dangling_in_collection(); // 💥 Potential crash
    bug_unclear_ownership();      // 💥 Returns dangling pointer
    bug_aliasing();               // Confusing shared state
    
    printf("\n✅ Program finished (some bugs are silent!)\n");
    return 0;
}