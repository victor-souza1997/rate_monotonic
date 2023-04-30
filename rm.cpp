#include <iostream>
#include <vector>
#include <string>


struct Task {
    int id;
    int period;
    int execution_time;
};

void print_tasks(const std::vector<Task>& tasks){
    
    for (auto& tasks : tasks) {
        std::cout << "Task id: " << tasks.id << std::endl;
        std::cout << "Period: " << tasks.period << std::endl;
        std::cout << "Execution Time: " << tasks.execution_time << std::endl;
        std::cout << std::endl; // add a blank line between each person
    }

};

int main() {
    int n;
    std::vector<Task> tasks;
    std::cout << "Input the number of tasks: ";
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        Task t;
        std::cout << "Input the period of the task " << i+1 << ": ";
        std::cin >> t.period;
        std::cout << "input the processing time " << i+1 << ": ";
        std::cin >> t.execution_time;
        t.id = i+1;
        tasks.push_back(t);
    }

    print_tasks(tasks);

   
    return 0;
}
