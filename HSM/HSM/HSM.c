/*!
* \file HSM.c
* This file implements the Hierarchical StateMachine
* \author    Ajith Padman Magneti Marelli GmbH
* \version   1.0
* \date      29.09.2014
*  
*/

#include "hsm.h"
#ifdef SYSTEM_SIMULATION
#include <conio.h>
#endif
#ifndef NULL
#define NULL 0
#endif
/*! \var hsm_stateList
 * The main statelist provided by the user
 */
state *hsm_stateList;//pointer to an array of States
/*! \var hsm_currentState
 * Global variable used to store the current state information
 */
state *hsm_currentState;
/*! \var hsm_nextState
 * Global variable used to store the current destination state during a state transition
 */
state *hsm_nextState;
/*! \var hsm_EntryRoute
 * stack used to trace back the state entry path
 */
Stack hsm_EntryRoute;

void hsm_ProcessEvent(EventID eventId);
unsigned int hsm_isEventConsumed(state *currentState, EventID eventId,unsigned int *transitionIndex);
void hsm_doTransition(unsigned int transitionID,state *currentState);
void executeEntry(void);
void executeExit(void);
void prepareEntryTable(state commonParent);
unsigned int checkIsParent(state currentParent,state nextState);

/*! \fn void hsm_create(state *stateList,unsigned int noOfStates) 
*  \brief This function creates the HSM
*  \param *stateList The pointer to the statelist.
*  \param noOfStates Number of states in the HSM
*  \return void
*/
void hsm_create(state *stateList,unsigned int noOfStates)
{
	unsigned int stateID = 0;
	unsigned int parentID = 0;
	hsm_stateList = stateList;

	for (stateID = 0; stateID <= noOfStates ;stateID++)
	{
		parentID = hsm_stateList[stateID].parentID;
		hsm_stateList[stateID].parentState = &hsm_stateList[parentID];
		//printf(" state = %d  ",hsm_stateList[stateID].stateID);
		//printf(" state parent = %d \n ",(hsm_stateList[stateID].parentState)->stateID);

	}
	if(noOfStates > 0)
	{
		hsm_currentState = &hsm_stateList[STATE_START];//set the current state as the root state. the root state shall be the first state.
	}

}
/*! \fn void hsm_start(void) 
*  \brief This function is used to start the HSM. 
*   Here ROOT state enters to the Default child state
*  \param void
*  \return void
*/
void hsm_start(void)
{
	
	//printf(" state before = %d  ",hsm_currentState->stateID);
	hsm_onEvent(EV_DEFAULT);

}
/*! \fn void hsm_end(void) 
*  \brief This function is used to stop the HSM. 
*  \param void
*  \return void
*/
void hsm_stop(void)
{
	hsm_currentState = STATEID_NULL;
}
/*! \fn void hsm_onEvent(EventID eventId) 
*  \brief This function is used to fire events to HSM
*  From here the Event Processing function is called 
*  \param eventId The ID of the Current Event
*  \return void
*/
void hsm_onEvent(EventID eventId)
{
   hsm_ProcessEvent(eventId);
   
}
/*! \fn void hsm_ProcessEvent(EventID eventId) 
*  \brief This function is used to process events fired to HSM
*  First it is found  who will be consuming the event. 
*  If the current state is not consuming the event the parent state is checked for it.
*  If nobody in the state hierarchy consumes the event the function does not perform any action. 
*  if the event consumer state is found state transition is executed.
*  \param eventId The ID of the Current Event
*  \return void
*/
void hsm_ProcessEvent(EventID eventId)
{
	/*
	*First find who will consume the event. If the current state is not consuming the event find the parent state
	* who will be consuming it.If nobody in the state hierarchy consumes it do not perform any action. 
	*if the state is found execute the exit and entry action sequence.

	*/
	unsigned int result = HSM_RESULT_NOK;
	state * currentStateBackUp = hsm_currentState;
	state *currentState = hsm_currentState;
	unsigned int transitionID = 0;
	while(
		!result &&
		currentState->stateID != STATEID_NULL
		)
	{
		result = hsm_isEventConsumed(currentState,eventId,&transitionID) ;//checking if the event is consumed by the state
		if(HSM_RESULT_OK == result)
		{
#ifdef SYSTEM_SIMULATION
			printf(" Event consumed %d\n",eventId);
#endif
		}
		if(!result && eventId != EV_DEFAULT)
		{
			currentState = currentState->parentState;//setting the current state to parent state
		}
		else if(!result && eventId == EV_DEFAULT)
		{
			break;
		}
		else
		{
			hsm_nextState = &hsm_stateList[currentState->smTransition->transition[transitionID].toState];//setting the next state
			//printf(" next state  = %d\n  ",hsm_nextState->stateID);
		}
	}
	if(result)
	{

		hsm_doTransition(transitionID,currentState);// if the event is consumed by the current state do the transition.
		
	}
	else
	{
		hsm_currentState = currentStateBackUp;
	}

}
/*! \fn void hsm_isEventConsumed(state *currentState, EventID eventId,unsigned int *transitionIndex) 
*  \brief This functionchecks if the evnet is consumed by the state indicated by the currentState param.
*   If the event is consumed by a transition the return value is set to HSM_RESULT_OK and the 
*  *transitionIndex is set to the ID of the Transition consuming the event
*
*  \param[in] *currentState pointer to the current state
*  \param[in]  eventId ID of the current Event to be checked for
*  \param[out] *transitionIndex pointer to transitionIndex ID of the transition to be set by the function
*  where the event is consumed. (Here it is assumed that an event can be consumed by  multiple transitions based on transition condition)
*  \return result can be HSM_RESULT_OK or HSM_RESULT_NOK. If the event is consumed by a transition the return value is set to HSM_RESULT_OK and the 
*  *transitionIndex is set to the ID of the Transition consuming the event
*/
unsigned int hsm_isEventConsumed(state *currentState, EventID eventId,unsigned int *transitionIndex)
{
	unsigned int result = HSM_RESULT_NOK;
	unsigned int transitionID = 0;
	unsigned int transitionCount = currentState->smTransition->transitionCount;
	for(transitionID = 0;transitionID < transitionCount;transitionID++)
	{
		if(eventId == currentState->smTransition->transition[transitionID].triggerID)
		{
			if(currentState->smTransition->transition[transitionID].condition != 0)//execute the transition condition to know if the conditions are correct.
			{
				if(currentState->smTransition->transition[transitionID].condition()== HSM_RESULT_OK)
				{
					*transitionIndex = transitionID;//return the current transition Identifier to event processor
					result = HSM_RESULT_OK;
					break;
				}
			}
			else
			{
				*transitionIndex = transitionID;//return the current transition Identifier to event processor
				result = HSM_RESULT_OK;
				break;
			}

		}
	}
	return result;

}
/*! \fn void hsm_doTransition(unsigned int transitionID) 
*  \brief This function actually performs the stateTransition. For the state transition execution,
*   the exit functions corresponding to the current and its parent states(which is not the common parent for source and destination) 
*   are to be executed. and Entry function to be executed in the hierarchy order
*  \param transitionID The Id of the transition that need to be perfoemd by the current State
*  \return void
*/
void hsm_doTransition(unsigned int transitionID,state *currentState)
{

	if ( hsm_nextState->stateID!= STATEID_NULL)
	{
		//call the exit hierarchically
		executeExit();
		//execute the state transition
		if(NULL != currentState->smTransition)
		{
			if(NULL != currentState->smTransition->transition[transitionID].action)
			{
			   currentState->smTransition->transition[transitionID].action();//assuming only one action is there during transition
			}
		}
		//call the entry hierarchically
		executeEntry();
		
		//execute state transition action
		hsm_currentState = hsm_nextState;//do the state transition to next state
		hsm_nextState = STATEID_NULL;//change the next State  to NULL 
		//Call the DO action of the state
		if(NULL != hsm_currentState )
		{
			if(NULL != hsm_currentState->doAction)
			{
				hsm_currentState->doAction();
			}
		}
		hsm_ProcessEvent(EV_DEFAULT);
	}
	
}
/*! \fn void executeEntry(void) 
*  \brief This function executes the Entry funtions of the states in the hierarchical order during state transition
*  The assumption is that only one entry function is present in each state. If there need to be multiple entry actions
*  it can be performed by the multiple functions called from the single function
*  \param void
*  \return void
*/
void executeEntry(void)
{
	int entry = 0;
	int stateID = 0;
	while(hsm_EntryRoute.size> 0)
	{
		stateID = Stack_Top(&hsm_EntryRoute);
		if(stateID != -1)
		{
			if(hsm_stateList[stateID].entryAction)
			{
				hsm_stateList[stateID].entryAction();//executing the entry action
			}
		}
		
	}
	if(NULL != hsm_nextState->entryAction)
	{
		hsm_nextState->entryAction();
	}
}
/*! \fn void executeExit(void) 
*  \brief This function executes the Exit funtions of the states in the hierarchical order during state transition
*  The assumption is that only one exit function is present in each state. If there need to be multiple exit actions
*  it can be performed by the multiple functions called from the single function
*  \param void
*  \return void
*/
void executeExit()
{
	state currentState = *hsm_currentState;
	state nextState = *hsm_nextState;
	while(
		//currentState.parentID != nextState.parentID
		checkIsParent(currentState,nextState) == HSM_RESULT_NOK
		)
	{
		if(NULL != currentState.exitAction)
		{
			currentState.exitAction();
		}
		currentState = *currentState.parentState;
		//nextState = *nextState.parentState;
	}
	prepareEntryTable(currentState);
}
/*! \fn unsigned int checkIsParent(state currentParent,state nextState)
*  \callergraph
*  \brief This function check if the current destination state(next state) can be entered
*  through the parent state provided as the first argument
*  \param currentParent the state to be checked if present as parent for the destination state
*  \param current destination state
*  \return void
*/
unsigned int checkIsParent(state currentParent,state nextState)
{
	unsigned result = HSM_RESULT_NOK;
	while(nextState.parentID != currentParent.stateID && currentParent.stateID != STATEID_NULL && nextState.stateID != STATEID_NULL)
	{
		nextState = *nextState.parentState;
	}
	if(nextState.parentID == currentParent.stateID)
	{
		result = HSM_RESULT_OK;
	}
	else
	{
		result = HSM_RESULT_NOK;
	}
	return result;
}
/*! \fn void prepareEntryTable(state commonParent)
*  \brief This function prepares out the route through which the destination can be reached during the state transition
*   This is important for executing the entry function in the opposite order while entering the state
*  \param commonParent this is the common parent state between the source state and destination state. The exit function need to be 
*  Executed till the common parent is reached and entry functions to be executed from the common parent to  the states in the path to the destination
*  \return void
*/
void prepareEntryTable(state commonParent)
{
	state nextState = *hsm_nextState;
	Stack_Init(&hsm_EntryRoute);
	while(nextState.parentID != commonParent.stateID)
	{
		nextState = *nextState.parentState;
		Stack_Push(&hsm_EntryRoute, nextState.stateID);
	}
}
/*! \fn unsigned int hsm_getCurrentState(void)
*  \brief This function is used by the using application to get the current state of the statemachine
*  \param void
*  \return current state of the statemachine
*/
StateID hsm_getCurrentState(void)
{
	#ifdef SYSTEM_SIMULATION 
  printf("current State from getCurrentState %d\n",hsm_currentState->stateID);
  #endif
	return hsm_currentState->stateID;
}
