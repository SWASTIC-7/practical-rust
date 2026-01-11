#[derive(Debug, Clone)]
struct Task {
    id: u32,
    title: String,
    done: bool,
}

struct TaskManager {
    tasks: Vec<Task>,
    next_id: u32,
}

impl TaskManager {
    fn new() -> Self {
        TaskManager { tasks: vec![], next_id: 1 }
    }
    
    fn create(&mut self, title: String) -> u32 {
        let id = self.next_id;
        self.next_id += 1;
        self.tasks.push(Task { id, title, done: false });
        id
    }
    
    fn get(&self, id: u32) -> Option<&Task> {
        self.tasks.iter().find(|t| t.id == id)
    }
    
    fn list(&self) -> &[Task] {
        &self.tasks
    }
    
    fn mark_done(&mut self, id: u32) -> bool {
        match self.tasks.iter_mut().find(|t| t.id == id) {
            Some(task) => { task.done = true; true }
            None => false
        }
    }
    
    fn delete(&mut self, id: u32) -> Option<Task> {
        self.tasks
            .iter()
            .position(|t| t.id == id)
            .map(|pos| self.tasks.remove(pos))
    }
}

fn main() {
    let mut manager = TaskManager::new();
    
    
    
}