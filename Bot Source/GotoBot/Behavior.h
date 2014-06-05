#pragma once

#include <list>
#include "DllEntry.h"

//Draws directly from BTSK, copyright alexjc

enum Status {
	BH_INVALID,
	BH_SUCCESS,
	BH_FAILURE,
	BH_RUNNING,
	BH_ABORTED,
};


///Behavior: Base class for actions, conditions, and composites.
class Behavior {
public:
	Status m_eStatus;
	const sEntInfo *botInfo;
	const sWorldInfo *worldInfo;
	
public:
	//Behavior() {}
	virtual ~Behavior() {}

	virtual void OnInitialize() {}
	virtual Status Update() = 0;
	virtual void OnTerminate(Status) {}

	Status Tick();
	void Reset();
	void Abort();

	bool IsTerminated() const;
	bool IsRunning() const;
	Status GetStatus() const;
};


///Composite
class Composite : public Behavior {
public:
	typedef std::list<Behavior*> Behaviors;
	Behaviors m_Children;

public:
	virtual ~Composite() {
		ClearChildren();
	}

	void AddChild(Behavior *child);
	void RemoveChild(Behavior *child);
	void ClearChildren();

};


///Sequence: Return success if all children return success
class Sequence : public Composite {
public:
	Sequence() {}
	~Sequence() {}

public:
	Behaviors::iterator m_currentChild;

	void OnInitialize();
	Status Update();

};


///Selector: return success at first child's success
class Selector : public Composite {
public:
	Selector() {}
	~Selector() {}

protected:
	Behaviors::iterator m_currentChild;

	void OnInitialize();
	Status Update();

};

/*
///Decorator: Behavior wrapper for behaviors
class Decorator : public Behavior {

protected:
Behavior* m_pChild;

public:
Decorator(Bot& b, Behavior* child) : m_pChild(child), Behavior(b) {}
};*/