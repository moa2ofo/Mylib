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

void test_MyLib_Orchestrate_u32_WhenDeltaIsNullAndStartIsZero_ReturnsExpectedValue(void)
{
  uint32_t start_u32 = 0U;
  uint32_t l_base_u32 = 100U;
  uint32_t expected_return = 150U;

  InternalHelper_u32_CMockExpectAndReturn(39, start_u32, 0U, l_base_u32);

  MyLib_ProcessRecord_CMockExpect(42,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(43);

  g_counter_u32 = 50U;

  uint32_t result = MyLib_Orchestrate_u32(start_u32,
                                                    ((void *)0)
                                                        );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_return)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(52), UNITY_DISPLAY_STYLE_UINT32);
}