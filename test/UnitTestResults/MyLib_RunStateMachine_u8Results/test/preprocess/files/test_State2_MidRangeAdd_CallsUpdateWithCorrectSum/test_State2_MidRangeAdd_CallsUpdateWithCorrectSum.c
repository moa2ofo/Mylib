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

void test_State2_MidRangeAdd_CallsUpdateWithCorrectSum(void)
{
  MyLib_record_t input_rec = {30U, 400U};
  uint32_t mid_range_add = 0x80000000U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_CMockExpect(16,
 ((void *)0)
 , &input_rec);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(17);
  result = MyLib_RunStateMachine_u8(&input_rec, mid_range_add,
                                                              ((void *)0)
                                                                  );

  MyLib_ProcessRecord_CMockExpect(20,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(21);
  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(22, 0U,
 ((void *)0)
 , 500U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_base_u32(23);
  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , mid_range_add,
                                                        ((void *)0)
                                                            );

  uint32_t expected_sum = mid_range_add + 500U;
  MyLib_UpdateCounter_u8_CMockExpectAndReturn(27, expected_sum, 0U);

  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , mid_range_add,
                                                        ((void *)0)
                                                            );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_UINT8);
}