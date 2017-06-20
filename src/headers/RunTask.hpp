#ifndef RUNTASK_HPP
#define RUNTASK_HPP
#include <functional>
#include <queue>
#include <stack>

template<typename Task>
inline void runTaskFIFO(Task init,::std::function<void(Task,::std::function<void(Task)>)> processer){
	::std::queue<Task> tasks;
	auto addTask=[&tasks](Task t){tasks.push(t);};
	addTask(init);
	while(!tasks.empty()){
		Task t=tasks.front();
		tasks.pop();
		processer(t,addTask);
	}
}

template<typename Task>
inline void runTaskLIFO(Task init,::std::function<void(Task,::std::function<void(Task)>)> processer){
	::std::stack<Task> tasks;
	auto addTask=[&tasks](Task t){tasks.push(t);};
	addTask(init);
	while(!tasks.empty()){
		Task t=tasks.top();
		tasks.pop();
		processer(t,addTask);
	}
}

#endif //RUNTASK_HPP