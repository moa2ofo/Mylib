// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/InternalHelper_u32.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"

void setUp(void)
{
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b =
                   0
}

void tearDown(void)
{ }
void test_InternalHelper_u32__x_is_zero_y_is_zero(void)
{
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = 0U;
  uint32_t expected_u32 = 0U;

  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_UINT32);
}
void test_InternalHelper_u32__x_nonzero_y_is_zero(void)
{
  uint32_t x_u32 = 100U;
  uint16_t y_u16 = 0U;
  uint32_t expected_u32 = 100U;

  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(86), UNITY_DISPLAY_STYLE_UINT32);
}
void test_InternalHelper_u32__x_is_zero_y_is_one(void)
{
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = 1U;
  uint32_t expected_u32 = 0U;

  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(111), UNITY_DISPLAY_STYLE_UINT32);
}
void test_InternalHelper_u32__x_nonzero_y_is_one(void)
{
  uint32_t x_u32 = 50U;
  uint16_t y_u16 = 1U;
  uint32_t expected_u32 = 50U;

  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(135), UNITY_DISPLAY_STYLE_UINT32);
}
void test_InternalHelper_u32__x_is_zero_y_is_two(void)
{
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = 2U;
  uint32_t expected_u32 = 2U;

  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(166), UNITY_DISPLAY_STYLE_UINT32);
}
void test_InternalHelper_u32__x_is_zero_y_is_five(void)
{
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = 5U;
  uint32_t expected_u32 = 20U;

  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(196), UNITY_DISPLAY_STYLE_UINT32);
}
void test_InternalHelper_u32__x_nonzero_y_is_five(void)
{
  uint32_t x_u32 = 100U;
  uint16_t y_u16 = 5U;
  uint32_t expected_u32 = 120U;

  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(221), UNITY_DISPLAY_STYLE_UINT32);
}
void test_InternalHelper_u32__x_is_250_y_is_ten(void)
{
  uint32_t x_u32 = 250U;
  uint16_t y_u16 = 10U;
  uint32_t expected_u32 = 340U;

  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(246), UNITY_DISPLAY_STYLE_UINT32);
}
void test_InternalHelper_u32__x_max_u32_y_is_one(void)
{
  uint32_t x_u32 =
                  (4294967295U)

  uint16_t y_u16 = 1U;
  uint32_t expected_u32 =
                         (4294967295U)

  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(273), UNITY_DISPLAY_STYLE_UINT32);
}
void test_InternalHelper_u32__x_is_zero_y_max_u16(void)
{
  uint32_t x_u32 = 0U;
  uint16_t y_u16 =
                  (65535)

  uint32_t expected_u32;

  expected_u32 = (uint32_t)
                          (65535)
                                     * (uint32_t)(
                                                  (65535)
                                                             - 1U);

  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(303), UNITY_DISPLAY_STYLE_UINT32);
}
void test_InternalHelper_u32__x_at_documented_max_y_moderate(void)
{
  uint32_t x_u32 = 60535U;
  uint16_t y_u16 = 100U;
  uint32_t expected_u32 = 70435U;

  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(331), UNITY_DISPLAY_STYLE_UINT32);
}
void test_InternalHelper_u32__does_not_modify_global_counter(void)
{
  g_counter_u32 = 0U;
  uint32_t x_u32 = 100U;
  uint16_t y_u16 = 5U;
  uint32_t counter_before = g_counter_u32;

  InternalHelper_u32(x_u32, y_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((counter_before)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(360), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(361), UNITY_DISPLAY_STYLE_UINT32);
}
void test_InternalHelper_u32__does_not_modify_global_record(void)
{
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  MyLib_record_t record_before = g_record;
  uint32_t x_u32 = 100U;
  uint16_t y_u16 = 5U;

  InternalHelper_u32(x_u32, y_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((record_before.id_u16)), (UNITY_INT)(UNITY_UINT16)((g_record.id_u16)), (
 ((void *)0)
 ), (UNITY_UINT)(385), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((record_before.value_u32)), (UNITY_INT)(UNITY_UINT32)((g_record.value_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(386), UNITY_DISPLAY_STYLE_UINT32);
}
void test_InternalHelper_u32__does_not_modify_system_ready_flag(void)
{
  g_systemReady_b =
                   

 _Bool
      ready_before = g_systemReady_b;
  uint32_t x_u32 = 100U;
  uint16_t y_u16 = 5U;

  InternalHelper_u32(x_u32, y_u16);

  UnityAssertEqualNumber((UNITY_INT)((ready_before)), (UNITY_INT)((g_systemReady_b)), (
 ((void *)0)
 ), (UNITY_UINT)(410), UNITY_DISPLAY_STYLE_INT);
  do { if (!(g_systemReady_b))
{ } else { UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((411))); } } while (0);
}
void test_InternalHelper_u32__loop_executes_exactly_y_times(void)
{
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = 3U;

  uint32_t expected_u32 = 6U;

  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(445), UNITY_DISPLAY_STYLE_UINT32);
}
void test_InternalHelper_u32__loop_counter_increments_correctly(void)
{
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = 4U;
  uint32_t expected_u32 = 12U;

  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(474), UNITY_DISPLAY_STYLE_UINT32);
}
void test_InternalHelper_u32__uint16_to_uint32_cast_correctness(void)
{
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = 200U;
  uint32_t expected_u32 = 39800U;

  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(505), UNITY_DISPLAY_STYLE_UINT32);
}
void test_InternalHelper_u32__accumulation_prevents_intermediate_overflow(void)
{
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = 500U;
  uint32_t expected_u32 = 249500U;

  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(531), UNITY_DISPLAY_STYLE_UINT32);
}
void test_InternalHelper_u32__alternating_values_consistency(void)
{
  uint32_t result1 = InternalHelper_u32(10U, 2U);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((12U)), (UNITY_INT)(UNITY_UINT32)((result1)), (
 ((void *)0)
 ), (UNITY_UINT)(553), UNITY_DISPLAY_STYLE_UINT32);

  uint32_t result2 = InternalHelper_u32(20U, 3U);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((26U)), (UNITY_INT)(UNITY_UINT32)((result2)), (
 ((void *)0)
 ), (UNITY_UINT)(557), UNITY_DISPLAY_STYLE_UINT32);

  uint32_t result3 = InternalHelper_u32(30U, 1U);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((30U)), (UNITY_INT)(UNITY_UINT32)((result3)), (
 ((void *)0)
 ), (UNITY_UINT)(561), UNITY_DISPLAY_STYLE_UINT32);
}
void test_InternalHelper_u32__repeated_same_input_returns_same_output(void)
{
  uint32_t x_u32 = 42U;
  uint16_t y_u16 = 7U;
  uint32_t expected_u32 = 84U;

  uint32_t result1 = InternalHelper_u32(x_u32, y_u16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_u32)), (UNITY_INT)(UNITY_UINT32)((result1)), (
 ((void *)0)
 ), (UNITY_UINT)(584), UNITY_DISPLAY_STYLE_UINT32);

  uint32_t result2 = InternalHelper_u32(x_u32, y_u16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_u32)), (UNITY_INT)(UNITY_UINT32)((result2)), (
 ((void *)0)
 ), (UNITY_UINT)(588), UNITY_DISPLAY_STYLE_UINT32);

  uint32_t result3 = InternalHelper_u32(x_u32, y_u16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_u32)), (UNITY_INT)(UNITY_UINT32)((result3)), (
 ((void *)0)
 ), (UNITY_UINT)(592), UNITY_DISPLAY_STYLE_UINT32);
}