#include "SampleHSM.h"
/************************************/
/*!
   \fn void SampleHSM_HSM_Create(void)
*  \brief Creating the HSM
*  \return void
*/
/************************************/
void SampleHSM_HSM_Create(void)
{
 hsm_create(m_stateList_SampleHSM,9);
}
/************************************/
/*!
   \fn void SampleHSM_HSM_Start(void)
*  \brief Starting the HSM
*  \return void
*/
/************************************/
void SampleHSM_HSM_Start(void)
{
 hsm_start();
}
/************************************/
/*!
   \fn void SampleHSM_HSM_Stop(void)
*  \brief Stoping the HSM
*  \return void
*/
/************************************/
void SampleHSM_HSM_Stop(void)
{
 hsm_stop();
}
/************************************/
/*!
   \fn void SampleHSM_HSM_onEvent(EventID eventId)
*  \brief To fire event to the HSM
*  \return void
*/
/************************************/
void SampleHSM_HSM_onEvent(EventID eventId)
{
 hsm_onEvent(eventId);
}
/************************************/
/*!
   \fn StateID SampleHSM_hsm_getCurrentState(void)
*  \brief To get the current state of HSM
*  \return StateID
*/
/************************************/
StateID SampleHSM_hsm_getCurrentState(void)
{
  return hsm_getCurrentState();
}
/************************************/
/*!
   \fn void State1_Entry(int id)
*  \brief //entry function for STATE_1
*  \return void
*/
/************************************/
void State1_Entry(int id)
{
 (void)id;
}
/************************************/
/*!
   \fn void State1_Entry(int id)
*  \brief //exit function for STATE_1
*  \return void
*/
/************************************/
void State1_Exit(int id)
{
 (void)id;
}
/************************************/
/*!
   \fn void State1_1_entry(int id)
*  \brief //entry function for STATE1_1
*  \return void
*/
/************************************/
void State1_1_entry(int id)
{
 (void)id;
}
/************************************/
/*!
   \fn void State1_1_entry(int id)
*  \brief //exit function for STATE1_1
*  \return void
*/
/************************************/
void State1_1_Exit(int id)
{
 (void)id;
}
/************************************/
/*!
   \fn int contoState211(int id)
*  \brief //condition for transition from STATE1_1 to STATE2_1_1
*  \return int
*/
/************************************/
int contoState211(int id)
{
 (void)id;
 return HSM_RESULT_OK;}
/************************************/
/*!
   \fn void State1_2_entry(int id)
*  \brief //entry function for STATE1_2
*  \return void
*/
/************************************/
void State1_2_entry(int id)
{
 (void)id;
}
/************************************/
/*!
   \fn void State1_2_entry(int id)
*  \brief //exit function for STATE1_2
*  \return void
*/
/************************************/
void State1_2_exit(int id)
{
 (void)id;
}
/************************************/
/*!
   \fn int conToState11(int id)
*  \brief //condition for transition from STATE1_2 to STATE1_1
*  \return int
*/
/************************************/
int conToState11(int id)
{
 (void)id;
 return HSM_RESULT_OK;}
/************************************/
/*!
   \fn void State2_entry(int id)
*  \brief //entry function for STATE_2
*  \return void
*/
/************************************/
void State2_entry(int id)
{
 (void)id;
}
/************************************/
/*!
   \fn void State2_entry(int id)
*  \brief //exit function for STATE_2
*  \return void
*/
/************************************/
void State2_exit(int id)
{
 (void)id;
}
/************************************/
/*!
   \fn void State2_1Entry(int id)
*  \brief //entry function for STATE2_1
*  \return void
*/
/************************************/
void State2_1Entry(int id)
{
 (void)id;
}
/************************************/
/*!
   \fn void State2_1Entry(int id)
*  \brief //exit function for STATE2_1
*  \return void
*/
/************************************/
void State2_1Exit(int id)
{
 (void)id;
}
/************************************/
/*!
   \fn void State2_1_1_Entry(int id)
*  \brief //entry function for STATE2_1_1
*  \return void
*/
/************************************/
void State2_1_1_Entry(int id)
{
 (void)id;
}
/************************************/
/*!
   \fn void State2_1_1_Entry(int id)
*  \brief //exit function for STATE2_1_1
*  \return void
*/
/************************************/
void State2_1_1_Exit(int id)
{
 (void)id;
}
/************************************/
/*!
   \fn int contoState3(int id)
*  \brief //condition for transition from STATE2_1_1 to STATE_3
*  \return int
*/
/************************************/
int contoState3(int id)
{
 (void)id;
 return HSM_RESULT_OK;}
/************************************/
/*!
   \fn int acttoState3(int id)
*  \brief //action during transition from STATE2_1_1 to STATE_3
*  \return int
*/
/************************************/
void acttoState3(int id)
{
 (void)id;
}
/************************************/
/*!
   \fn void State3_Entry(int id)
*  \brief //entry function for STATE_3
*  \return void
*/
/************************************/
void State3_Entry(int id)
{
 (void)id;
}
/************************************/
/*!
   \fn void State3_Entry(int id)
*  \brief //exit function for STATE_3
*  \return void
*/
/************************************/
void State3_Exit(int id)
{
 (void)id;
}
/************************************/
/*!
   \fn void State4Entry(int id)
*  \brief //entry function for State4
*  \return void
*/
/************************************/
void State4Entry(int id)
{
 (void)id;
}
/************************************/
/*!
   \fn void State4Entry(int id)
*  \brief //exit function for State4
*  \return void
*/
/************************************/
void State4Exit(int id)
{
 (void)id;
}
