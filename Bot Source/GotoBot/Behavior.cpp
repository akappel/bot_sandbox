#include "Behavior.h"


///////////////////////////////////////////
//****Task****/////////////////////////////
///////////////////////////////////////////
//Set this up once so that derived class delete children tasks
BTTask::~BTTask() {
	for (TaskIterator t = children.begin(); t != children.end(); ++t) {
		delete (*t);
	}
}


///////////////////////////////////////////
//****Selector****/////////////////////////
///////////////////////////////////////////
BTSelector::BTSelector(sEntInfo & bot, const sWorldInfo & world) {
	pBotInfo = &bot;
	pWorldInfo = &world;
}

bool BTSelector::Run() {
	//Handle no child nodes
	if (children.empty()) {
		printf("NO CHILDREN TASKS PRESENT");
		return false;
	}

	//Return first child to return true
	for (TaskIterator t = children.begin(); t != children.end(); ++t) {
		if ((*t)->Run()) {
			return true;
		}
	}

	//Return false otherwise
	return false;
}


///////////////////////////////////////////
//****Sequence****/////////////////////////
///////////////////////////////////////////

BTSequence::BTSequence(sEntInfo & bot, const sWorldInfo & world) {
	pBotInfo = &bot;
	pWorldInfo = &world;
}

bool BTSequence::Run() {
	//Handle no child nodes
	if (children.empty()) {
		printf("NO CHILDREN TASKS PRESENT");
		return false;
	}

	//Return false at first occurence of child returning false
	for (TaskIterator t = children.begin(); t != children.end(); ++t) {
		if (!(*t)->Run()) {
			return false;
		}
	}

	//Return true otherwise
	return true;
}
