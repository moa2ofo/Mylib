// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_Orchestrate_u32.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b =
                   0
}

void tearDown(void)
{
}

void test_MyLib_Orchestrate_u32_WhenDeltaIsNotNullAndStartIsNonZero_UsesCorrectDelta(void)
{
  uint32_t start_u32 = 200U;
  uint16_t delta_value = 42U;
  uint32_t l_base_u32 = 250U;
  uint32_t expected_return = 280U;

  InternalHelper_u32_CMockExpectAndReturn(40, start_u32, delta_value, l_base_u32);

  MyLib_ProcessRecord_CMockExpect(43,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(44);

  g_counter_u32 = 30U;

  uint32_t result = MyLib_Orchestrate_u32(start_u32, &delta_value);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_return)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(52), UNITY_DISPLAY_STYLE_UINT32);
}