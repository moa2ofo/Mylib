// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_ComputeAdjustedValue_u32.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

SECTION 1  Mock callbacks

    static uint32_t
    InternalHelper_u32_Callback(uint32_t x_u32, uint16_t y_u16, int call_count)
{
  (void)call_count;
  return x_u32 + y_u16;
}

SECTION 2  setUp() and tearDown()

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

void
    test_MyLib_ComputeAdjustedValue_u32_base_0_delta_NULL(void)
{
  uint32_t result_u32;
  uint32_t expected_intermediate_u32 = 0U * 1U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + (5U);

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(0U,
                                                 ((void *)0)
                                                     );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_result_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_UINT32);
}