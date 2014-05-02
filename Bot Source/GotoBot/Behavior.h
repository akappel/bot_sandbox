#pragma once

#include <list>
#include "DllEntry.h"

class Bot;

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

protected:
	Status m_eStatus;
	Bot* m_pBot;
	
public:
	Behavior() {}
	Behavior(Bot& b) : m_eStatus(BH_INVALID), m_pBot(&b) {}
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


///Decorator: Behavior wrapper for behaviors
class Decorator : public Behavior {

protected:
	Behavior* m_pChild;

public:
	Decorator(Bot& b, Behavior* child) : m_pChild(child), Behavior(b) {}
};


///Composite
class Composite : public Behavior {

protected:
	typedef std::list<Behavior*> Behaviors;
	Behaviors m_Children;

public:
	Composite() {}

	virtual ~Composite() {
		ClearChildren();
	}

	void AddChild(Behavior* child) { m_Children.push_back(child); }
	void RemoveChild(Behavior* child) { m_Children.remove(child); }
	void ClearChildren();

};


///Sequence: Return success if all children return success
class Sequence : public Composite {
public:
	Sequence() {}
	virtual ~Sequence() {}

protected:
	Behaviors::iterator m_currentChild;

	virtual void OnInitialize() { m_currentChild = m_Children.begin(); }
	virtual Status Update();

};


///Sequence: return success at first child's success
class Selector : public Composite {
public:
	Selector() {}
	virtual ~Selector() {}

protected:
	Behaviors::iterator m_currentChild;

	virtual void OnInitialize() { m_currentChild = m_Children.begin(); }
	virtual Status Update();

};
