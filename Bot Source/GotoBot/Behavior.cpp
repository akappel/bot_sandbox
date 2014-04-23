#include "Behavior.h"

///////////////////////////////
///Behavior
///////////////////////////////
Status Behavior::Tick() {
	if (m_eStatus != BH_RUNNING) {
		OnInitialize();
	}

	m_eStatus = Update();

	if (m_eStatus != BH_RUNNING) {
		OnTerminate(m_eStatus);
	}

	return m_eStatus;
}

void Behavior::Reset() {
	m_eStatus = BH_INVALID;
}

void Behavior::Abort() {
	OnTerminate(BH_ABORTED);
	m_eStatus = BH_ABORTED;
}

bool Behavior::IsTerminated() const {
	return m_eStatus == BH_SUCCESS || m_eStatus == BH_FAILURE;
}

bool Behavior::IsRunning() const {
	return m_eStatus == BH_RUNNING;
}

Status Behavior::GetStatus() const {
	return m_eStatus;
}


//////////////////////////////////
///Composite
//////////////////////////////////
void Composite::ClearChildren() {
	typedef std::list<Behavior*>::iterator BehaviorIterator;
	for (BehaviorIterator it = m_Children.begin(); it != m_Children.end(); ++it) {
		delete (*it);
	}
	m_Children.clear();
}


/////////////////////////////////
///Sequence
/////////////////////////////////
Status Sequence::Update() {
	while (true) {
		Status s = (*m_currentChild)->Tick();

		if (s != BH_SUCCESS) {
			return s;
		}

		if (++m_currentChild == m_Children.end()) {
			return BH_SUCCESS;
		}
	}
}


//////////////////////////////////
///Selector
//////////////////////////////////
Status Selector::Update() {
	while (true) {
		Status s = (*m_currentChild)->Tick();

		if (s != BH_FAILURE) {
			return s;
		}

		if (++m_currentChild == m_Children.end()) {
			return BH_FAILURE;
		}
	}
}