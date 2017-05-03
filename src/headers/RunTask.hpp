#ifndef RUNTASK_HPP
#define RUNTASK_HPP
#include <functional>
#include <queue>

template<typename Task>
inline void runTask(Task init,::std::function<void(Task,::std::function<void(Task)>)> processer){
	::std::queue<Task> tasks;
	auto addTask=[&tasks](Task t){tasks.push(t);};
	addTask(init);
	while(!tasks.empty()){
		Task t=tasks.front();
		tasks.pop();
		processer(t,addTask);
	}
}

#endif //RUNTASK_HPP