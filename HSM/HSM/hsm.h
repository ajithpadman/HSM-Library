/*!
* \file HSM.h
* This file implements the Hierarchical StateMachine
* \author    Ajith Padman Magneti Marelli GmbH
* \version   1.0
* \date      29.09.2014
*  
*/
#ifndef HSM
#define HSM
#ifdef _WIN32
#include <stdio.h>
#endif
#include "stack.h"
/**
*Macro definitions
***/
/*!
  \def RESULT_NOK
  General Function Result
*/
#ifndef HSM_RESULT_NOK
#define HSM_RESULT_NOK 0
#endif
/*!
  \def RESULT_NOK
  General Function Result
*/
#ifndef HSM_RESULT_OK
#define HSM_RESULT_OK 1
#endif
/*!
  \def STATEID_NULL
  Initial State of the system once the HSM is created
*/
#define STATEID_NULL 0
/*!
  \def STATE_START
  Macro indicating user stateID start
*/
#define STATE_START STATEID_NULL+1 
/*!
  \def noAction
  no Action in the transition
*/
#define noAction 0
/*!
  \def noCondition
  no condition in the transition
*/
#define noCondition 0
/*!
  \def NULL_TRANSTION
  no Transition
*/
#define NULL_TRANSITION 0,0


/*
*Definition of the DataTypes
*
*/
/*!
  \typedef StateID
  Unique identifier of the statemachine
*/
typedef  unsigned int StateID;
/*! \enum EventID
 * ID of the minimum required Events.
 */
 typedef enum  
{
	EV_NULL,
	EV_DEFAULT,
	EV_BASE_MAX // Always keep this as the last value in the base class
}EventID;
 /*! \struct Transition
 * state Transition elements
 */
typedef struct Transition
{
	EventID triggerID;//Event creating  the transition
	int (*condition)(int SMinstanceID);//condition for the transition
	void (*action)(int SMinstanceID);//Transition action
	StateID fromState;//Source StateID
	StateID toState;//Destination StateID

}Transition;
 /*! \struct TransitionTable
 * state Transition table for each state
 */
typedef struct TransitionTable
{
	Transition* transition;
	unsigned int transitionCount;
}TransitionTable;
/*! \struct State
 * Elements of a state
 */
typedef struct State
{
	StateID stateID;//ID of the current State
	StateID parentID;//ID of the Parent
	TransitionTable *smTransition;//pointer to the list of transitions from the state
	void (*entryAction)(int SMinstanceID);
	void (*exitAction)(int SMinstanceID);
	struct State *parentState;
}state;
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

/***
*HSM Functions 
*
***/

void hsm_create(state *stateList,unsigned int noOfStates);
void hsm_start(void);
void hsm_stop(void);
void hsm_onEvent(EventID eventId);
StateID hsm_getCurrentState(void);


#endif