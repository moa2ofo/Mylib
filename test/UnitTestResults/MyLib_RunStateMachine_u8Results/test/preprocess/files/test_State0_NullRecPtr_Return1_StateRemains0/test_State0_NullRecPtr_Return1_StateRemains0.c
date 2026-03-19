// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_RunStateMachine_u8.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_State0_NullRecPtr_Return1_StateRemains0(void)
{
  uint8_t result;

  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 0,
                                            ((void *)0)
                                                );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_UINT8);

  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 0,
                                            ((void *)0)
                                                );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_UINT8);
}