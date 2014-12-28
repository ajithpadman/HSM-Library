#ifndef SAMPLEHSM
#define SAMPLEHSM
#include "hsm.h"
enum EventIDList_SampleHSM
{
  EV2 = EV_BASE_MAX,
  EV_1,
  EV5,
  EV3,
  EV4,
  MAX_EVENTS
};
enum statelist_SampleHSM
{
  ROOT_STATE = STATE_START,
  STATE_1,
  STATE1_1,
  STATE1_2,
  STATE_2,
  STATE2_1,
  STATE2_1_1,
  STATE_3,
  State4,
  MAX_STATEID
};
/************************************
State Machine Functions
************************************/
void SampleHSM_HSM_Create(void);/*Create the HSM*/
void SampleHSM_HSM_Start(void);/*Starting the HSM*/
void SampleHSM_HSM_Stop(void);/*Stoping the HSM*/
void SampleHSM_HSM_onEvent(EventID eventId);/*To fire event to the HSM*/
StateID SampleHSM_hsm_getCurrentState(void);/*To get the current state of HSM*/
/************************************
State Definitions
************************************/
/************************************
ROOT_STATE
************************************/
//Transition Table for ROOT_STATE
static Transition transition_SampleHSMROOT_STATE[1] =
{
   {(EventID) EV_DEFAULT,noCondition,noAction,ROOT_STATE,STATE_1}
};
/************************************
STATE_1
************************************/
//entry function for STATE_1
void State1_Entry(int id);
//exit function for STATE_1
void State1_Exit(int id);
//Transition Table for STATE_1
static Transition transition_SampleHSMSTATE_1[1] =
{
   {(EventID) EV_DEFAULT,noCondition,noAction,STATE_1,STATE1_2}
};
/************************************
STATE1_1
************************************/
//entry function for STATE1_1
void State1_1_entry(int id);
//exit function for STATE1_1
void State1_1_Exit(int id);
//condition for transition from STATE1_1 to STATE2_1_1
int contoState211(int id);
//Transition Table for STATE1_1
static Transition transition_SampleHSMSTATE1_1[1] =
{
   {(EventID) EV2,contoState211,noAction,STATE1_1,STATE2_1_1}
};
/************************************
STATE1_2
************************************/
//entry function for STATE1_2
void State1_2_entry(int id);
//exit function for STATE1_2
void State1_2_exit(int id);
//condition for transition from STATE1_2 to STATE1_1
int conToState11(int id);
//Transition Table for STATE1_2
static Transition transition_SampleHSMSTATE1_2[2] =
{
  {(EventID) EV_1,conToState11,noAction,STATE1_2,STATE1_1},
   {(EventID) EV5,noCondition,noAction,STATE1_2,STATE_2}
};
/************************************
STATE_2
************************************/
//entry function for STATE_2
void State2_entry(int id);
//exit function for STATE_2
void State2_exit(int id);
//Transition Table for STATE_2
static Transition transition_SampleHSMSTATE_2[1] =
{
   {(EventID) EV_DEFAULT,noCondition,noAction,STATE_2,STATE2_1_1}
};
/************************************
STATE2_1
************************************/
//entry function for STATE2_1
void State2_1Entry(int id);
//exit function for STATE2_1
void State2_1Exit(int id);
/************************************
STATE2_1_1
************************************/
//entry function for STATE2_1_1
void State2_1_1_Entry(int id);
//exit function for STATE2_1_1
void State2_1_1_Exit(int id);
//condition for transition from STATE2_1_1 to STATE_3
int contoState3(int id);
//action during transition from STATE2_1_1 to STATE_3
void acttoState3(int id);
//Transition Table for STATE2_1_1
static Transition transition_SampleHSMSTATE2_1_1[1] =
{
   {(EventID) EV3,contoState3,acttoState3,STATE2_1_1,STATE_3}
};
/************************************
STATE_3
************************************/
//entry function for STATE_3
void State3_Entry(int id);
//exit function for STATE_3
void State3_Exit(int id);
//Transition Table for STATE_3
static Transition transition_SampleHSMSTATE_3[1] =
{
   {(EventID) EV4,noCondition,noAction,STATE_3,State4}
};
/************************************
State4
************************************/
//entry function for State4
void State4Entry(int id);
//exit function for State4
void State4Exit(int id);
/************************************
Transition Table
************************************/
static TransitionTable transitionTable_SampleHSM[MAX_STATEID]=
{
//For STATEID_NULL
  {NULL_TRANSITION },
//For ROOT_STATE
  {transition_SampleHSMROOT_STATE,1},
//For STATE_1
  {transition_SampleHSMSTATE_1,1},
//For STATE1_1
  {transition_SampleHSMSTATE1_1,1},
//For STATE1_2
  {transition_SampleHSMSTATE1_2,2},
//For STATE_2
  {transition_SampleHSMSTATE_2,1},
//For STATE2_1
  {NULL_TRANSITION },
//For STATE2_1_1
  {transition_SampleHSMSTATE2_1_1,1},
//For STATE_3
  {transition_SampleHSMSTATE_3,1},
//For State4
  {NULL_TRANSITION }
};
/************************************
State Table
************************************/
static state m_stateList_SampleHSM[MAX_STATEID]=
{
{0,0,0,0,0,0},//STATEID_NULL
{ROOT_STATE,STATEID_NULL,&transitionTable_SampleHSM[ROOT_STATE],0,0,0},//ROOT_STATE
{STATE_1,ROOT_STATE,&transitionTable_SampleHSM[STATE_1],State1_Entry,State1_Exit,0},//STATE_1
{STATE1_1,STATE_1,&transitionTable_SampleHSM[STATE1_1],State1_1_entry,State1_1_Exit,0},//STATE1_1
{STATE1_2,STATE_1,&transitionTable_SampleHSM[STATE1_2],State1_2_entry,State1_2_exit,0},//STATE1_2
{STATE_2,ROOT_STATE,&transitionTable_SampleHSM[STATE_2],State2_entry,State2_exit,0},//STATE_2
{STATE2_1,STATE_2,&transitionTable_SampleHSM[STATE2_1],State2_1Entry,State2_1Exit,0},//STATE2_1
{STATE2_1_1,STATE2_1,&transitionTable_SampleHSM[STATE2_1_1],State2_1_1_Entry,State2_1_1_Exit,0},//STATE2_1_1
{STATE_3,ROOT_STATE,&transitionTable_SampleHSM[STATE_3],State3_Entry,State3_Exit,0},//STATE_3
{State4,ROOT_STATE,&transitionTable_SampleHSM[State4],State4Entry,State4Exit,0}//State4
};
#endif


