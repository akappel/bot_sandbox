#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <list>
#include "DllEntry.h"

//Typedef the iterator for ease of use
class BTTask;
typedef std::list<BTTask*>::const_iterator TaskIterator;

///Task: Abstract base class, to be subclassed for implementation.
class BTTask {

protected:

	//Pointer to world and bot data, later encapsulate in Blackboard structure
	sEntInfo * pBotInfo;
	const sWorldInfo * pWorldInfo;
	std::list<BTTask*> children;

public:
	//Let each derived class use this destructor to destroy children list
	~BTTask();

	void AddChildTask(BTTask* subtask) { children.push_back(subtask); }

	//Precondition and execution all wrapped in one for now
	virtual bool Run() = 0;

};


///Selector: Return first subtask that returns true
class BTSelector : public BTTask {

public:
	BTSelector(sEntInfo & bot, const sWorldInfo & world);
	~BTSelector() {}

	bool Run();
	
};


///Sequence: Return true only if all subtasks do
class BTSequence : public BTTask {

public:
	BTSequence(sEntInfo & bot, const sWorldInfo & world);
	~BTSequence() {}

	bool Run();

};


#endif