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

void test_MyLib_Orchestrate_u32_WhenMultipleDeltaValues_AllProcessedCorrectly(void)
{
  {
    uint16_t delta_value = 10U;
    InternalHelper_u32_CMockExpectAndReturn(36, 50U, delta_value, 100U);
    MyLib_ProcessRecord_CMockExpect(37,
   ((void *)0)
   , (5U));
    MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(38);
    g_counter_u32 = 0U;

    uint32_t result = MyLib_Orchestrate_u32(50U, &delta_value);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_UINT32);
  }

  {
    uint16_t delta_value = 255U;
    InternalHelper_u32_CMockExpectAndReturn(48, 60U, delta_value, 150U);
    MyLib_ProcessRecord_CMockExpect(49,
   ((void *)0)
   , (5U));
    MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(50);
    g_counter_u32 = 0U;

    uint32_t result = MyLib_Orchestrate_u32(60U, &delta_value);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((150U)), (UNITY_INT)(UNITY_UINT32)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(54), UNITY_DISPLAY_STYLE_UINT32);
  }
}