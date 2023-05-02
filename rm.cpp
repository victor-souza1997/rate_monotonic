#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <limits.h>
#include <iostream>



#define T_SAMPLE 0.01
#define TOTAL_TIME 100
struct Task {
    int id;
    int period;
    double execution_time;
    bool active;
    double processing_execution_time;
    double waiting_time;
};

struct Grant {
    int vector;
    double change_time;
};



void print_tasks(const std::vector<Task>& tasks){
    
    for (auto& tasks : tasks) {
        std::cout << "Task id: " << tasks.id << std::endl;
        std::cout << "Period: " << tasks.period << std::endl;
        std::cout << "waiting_time: " << tasks.waiting_time << std::endl;
        std::cout << "Execution Time: " << tasks.execution_time << std::endl;
        std::cout << "Processing Time: " << tasks.processing_execution_time << std::endl;
        std::cout << "Active: " << tasks.active << std::endl;
        std::cout << std::endl; 
    }

};

std::vector<Grant> increment_vector(std::vector<Grant>& vec, int num, double time) {
    if (vec.empty() || vec.back().vector != num) {
        vec.push_back({num, time});
        //std::cout<<num<<std::endl;
    } 
    return vec;
}

int find_task_with_smallest_period(const std::vector<Task>& tasks) {
    int smallest_period = INT_MAX;
    int smallest_period_task_id = -1;

    for (const auto& task : tasks) {
        if (task.active && task.period < smallest_period) {
            smallest_period = task.period;
            smallest_period_task_id = task.id;
        }
    }

    return smallest_period_task_id;
}

double calculates_processing(const std::vector<Task>& tasks){

    double sum = 0.0;


    for (auto& tasks : tasks) {
        
        sum +=static_cast<double>(tasks.execution_time)/static_cast<double>(tasks.period);

    }
    return sum;
}

std::vector<Task> update_tasks(std::vector<Task> tasks) {
    for (int i = 0; i < tasks.size(); i++) {
        if (!tasks[i].active) {
            
            if (tasks[i].waiting_time >= tasks[i].period) {
               // std::cout<< i << " ";
               // std::cout<< tasks[i].waiting_time << " " << tasks[i].period;
                //std::cout<<std::endl;
                tasks[i].waiting_time = 0;
                tasks[i].active = true;
            }
            else{
                tasks[i].waiting_time+=T_SAMPLE;
            }
        }
    }
    return tasks;
}


void rate_monotonic(std::vector<Task>& tasks) {
    std::vector<Grant> grant;

    double time = 0.0 ;
    
    while (time < TOTAL_TIME){
        int n_turn;
        
        //std::cout<<"time: " << time << std::endl;
        n_turn = find_task_with_smallest_period(tasks) - 1;
        
        if (n_turn < 0){
            grant = increment_vector(grant, 0, time);      
        }
        else{
            //std::cout<<"n_turn " << n_turn << std::endl;
            grant = increment_vector(grant, n_turn+1, time);   
            //std::cout<<"n_turn: " << n_turn << " processing " << tasks[n_turn].processing_execution_time << std::endl;
            if (tasks[n_turn].processing_execution_time >= tasks[n_turn].execution_time){
                tasks[n_turn].processing_execution_time = 0;
                tasks[n_turn].active = false;
                //print_tasks(tasks);
            }
            else{
                tasks[n_turn].processing_execution_time += T_SAMPLE;
            }
             
        }
        time += T_SAMPLE;
        tasks = update_tasks(tasks);
       // print_tasks(tasks);
        //std::cout<<time<<std::endl;
    }
    std::cout<<"diagrama de grant:"<<std::endl;
    for(int i=0; i<grant.size(); i++) {
        //std::cout << "("<<grant[i].vector<< ", ";
        //std::cout << grant[i].change_time<<"), ";
        std:: cout << "task_id:" << grant[i].vector<<" ";   
    }
    std::cout << time<< std::endl;
}


int main() {
    int n;
    std::vector<Task> tasks;
    std::cout << "Input the number of tasks: ";
    //std::cin >> n;
    n = 3;
    /*
    
    for (int i = 0; i < n; i++) {
        Task t;
        std::cout << "Input the period of the task " << i+1 << ": ";
        std::cin >> t.period;
        std::cout << "input the processing time " << i+1 << ": ";
        std::cin >> t.execution_time;
        t.id = i+1;
        t.active = true;
        t.waiting_time = 0.0;
        t.processing_execution_time = 0.0;
        tasks.push_back(t);
    }
    */
    tasks = {
        {1,  25, 6.25, true, 0, 0},
        {2,  50, 6.25, true, 0, 0},
        {3,  100, 40, true, 0, 0}

    };
    //print_tasks(tasks);
    double sum = calculates_processing(tasks);

    double maximum_sum = n*(pow(2, 1/n)-1);
    //std::cout << sum << std::endl;
    //std::cout << maximum_sum <<std::endl;
    bool is_scalable;
    if (sum<=maximum_sum){
        is_scalable = true;
        std::cout<<"O conjunto de tarefas sao escalaveis" << std::endl;
        std::cout<<"U = " << sum << " <= " << maximum_sum << std::endl; 
    }
    else{
        is_scalable = false;
        std::cout<<"O conjunto de tarefas falharam no teste de escabilidade, no entando, ainda podem ser escalaveis" << std::endl;
        std::cout<<"U = " << sum << " > " << maximum_sum << std::endl;
    } 

    rate_monotonic(tasks);
    return 0;
}
