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

void test_ProcessRecord_called_with_MYLIB_MULT_VALUE_U8(void)
{
  uint32_t start_u32 = 100U;
  const uint16_t *delta_pc_u16 =
                                ((void *)0)

  uint32_t l_base_u32 = 200U;
  uint32_t actual_return;

  g_counter_u32 = 50U;

  InternalHelper_u32_CMockExpectAndReturn(27, start_u32, 0U, l_base_u32);

  UnityFail( (("MyLib_ProcessRecord requires _ExpectAnyArgs (not AndReturn)")), (UNITY_UINT)(29));;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((l_base_u32 + g_counter_u32)), (UNITY_INT)(UNITY_UINT32)((actual_return)), (
 ((void *)0)
 ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_UINT32);
}