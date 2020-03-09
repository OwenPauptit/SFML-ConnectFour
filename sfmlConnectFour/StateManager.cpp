#include "StateManager.hpp"

namespace Aesel {

	// Set some booleans and assign the new state to be processed in:   void StateMachine::ProcessStateChanged(){}
	void StateManager::AddState(StateRef newState, bool isReplacing) {
		this->_isAdding = true;
		this->_isReplacing = isReplacing;

		this->_newState = std::move(newState);
	}

	// Set a boolean to be processed in:   void StateMachine::ProcessStateChanged(){}
	void StateManager::RemoveState() {
		this->_isRemoving = true;
	}

	void StateManager::ProcessStateChanges() {

		// if a state is being removed, and there are states in the stack, then remove the top state from the stack
		if (this->_isRemoving && !this->_states.empty()) {
			this->_states.pop();

			// If there are still states in the stack, resume the top state
			if (!this->_states.empty()) {
				this->_states.top()->Resume();
			}

			// To avoid unwanted recursion
			this->_isRemoving = false;
		}

		// if a state is being added to the stack
		if (this->_isAdding) {
			// if there are states in the stack
			if (!this->_states.empty()) {
				//if a state is being replaced, remove the top state
				if (this->_isReplacing) {
					this->_states.pop();
				}
				//otherwise pause the state at the top of the stack
				else {
					this->_states.top()->Pause();
				}
			}

			//add the new state to the stack, and tell compiler that the value in _newState can be deleted
			this->_states.push(std::move(this->_newState));
			//initialise the new state
			this->_states.top()->Init();
			// To avoid unwanted recursion
			this->_isAdding = false;
		}
	}

	// Returns the state at the top of the stack
	StateRef& StateManager::GetActiveState() {
		return this->_states.top();
	}
}