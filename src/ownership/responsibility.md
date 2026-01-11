# Ownership is Responsibility, Not Memory

For understanding Ownership, it is very vital to understand why it is important in first place.

Well we should know stack and Heap for a better understanding, you can check this blog out;

You know that Rust is known for its memory safety -- where ownership is one way to maintain it

Lets try to make a CRUD app in C and then in Rust, to see why having multiple owner to same value is an issue.

consider this c code 
```c
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
```
 
Well This is a basic Crud application in C, where ```TaskManger``` manages the dynamic lists of ```Task``` pointers, while the functions manager_create(), manager_get(), manager_delete(), manager_free()  performs the crud operations.

Now look at this function
```c

void bug_use_after_free() {
    TaskManager* m = manager_new();
    int id = manager_create(m, "I will be freed");
    
    Task* task = manager_get(m, id);  // Get pointer to task
    printf("Task: %s\n", task->title);  // Works fine
    
    manager_delete(m, id);  // Task is freed!
    printf("Task after delete: %s\n", task->title); 
    
    manager_free(m);
}

int main() {
    bug_use_after_free();     

    return 0;
}
```

This function looks normal at first, but notice we have freed the task using manager_delete(), and then we will try to access that. Well there will be no compiler error for this code though when you will run it you will see something like this

```bash
Task: Learn C
Segmentation fault (core dumped)
```



Now lets look into another funtion 
```c
void bug_memory_leak() {
    
    TaskManager* m = manager_new();
    int id1 = manager_create(m, "Task 1");
    int id2 = manager_create(m, "Task 2");
    int id3 = manager_create(m, "Task 3");
    
    printf("Memory allocated at these addresses:\n");
    printf("  TaskManager: %p\n", (void*)m);
    printf("  Tasks array: %p\n", (void*)m->tasks);

}

int main() {
    bug_memory_leak();     

    return 0;
}
```
In this function we can see that we created the task but did not freed it, normally looks like no big deal and normally developer forgets to free the pointers, but we could still access the values at pointer. In this case I have explicitly leaked the address of pointer though there are multiple way to get the address, but lets not go into this.
While runnig this code you will see something like this

```bash
Memory allocated at these addresses:
  TaskManager: 0x564c94d842a0
  Tasks array: 0x564c94d842c0
```

on gdb when you will try to check on the address value you can easily find it 
```bash
gef➤  print m
$3 = (TaskManager *) 0x5555555592a0
gef➤  x/s m->tasks[0]->title
0x555555559340: "Task 1"
```


There is a one more common string 

