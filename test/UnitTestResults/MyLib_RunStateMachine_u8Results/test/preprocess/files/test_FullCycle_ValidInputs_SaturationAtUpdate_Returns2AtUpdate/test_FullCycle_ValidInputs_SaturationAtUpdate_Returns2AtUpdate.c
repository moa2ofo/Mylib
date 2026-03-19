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

void test_FullCycle_ValidInputs_SaturationAtUpdate_Returns2AtUpdate(void)
{
  MyLib_record_t input_rec = {20U, 500U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_CMockExpect(15,
 ((void *)0)
 , &input_rec);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(16);
  result = MyLib_RunStateMachine_u8(&input_rec, 100U,
                                                     ((void *)0)
                                                         );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(18), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_ProcessRecord_CMockExpect(20,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(21);
  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(22, 0U,
 ((void *)0)
 , 600U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_base_u32(23);
  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 100U,
                                               ((void *)0)
                                                   );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_UpdateCounter_u8_CMockExpectAndReturn(27, 700U, 2U);
  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 100U,
                                               ((void *)0)
                                                   );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_UINT8);
}