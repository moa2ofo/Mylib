// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_ProcessRecord.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

static MyLib_record_t test_record;
static uint32_t initial_counter;

void setUp(void)
{
  test_record.id_u16 = 0U;
  test_record.value_u32 = 0U;

  initial_counter = g_counter_u32;
}

void tearDown(void)
{}
void test_MyLib_ProcessRecord_NullPointer_ReturnsWithoutSideEffects(void)
{
  MyLib_ProcessRecord(
                     ((void *)0)
                         , 5U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((initial_counter)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(45), UNITY_DISPLAY_STYLE_UINT32);
}
void test_MyLib_ProcessRecord_Multiplier0_NoAccumulation(void)
{
  test_record.id_u16 = 100U;
  test_record.value_u32 = 1000U;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(66, 0U,
 ((void *)0)
 , 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(67);

  MyLib_ProcessRecord(&test_record, 0U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((initial_counter)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(73), UNITY_DISPLAY_STYLE_UINT32);
}
void test_MyLib_ProcessRecord_Multiplier1_SingleAccumulation(void)
{
  test_record.id_u16 = 42U;
  test_record.value_u32 = 500U;
  uint32_t expected_counter = initial_counter + 500U;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(95, 500U,
 ((void *)0)
 , 42U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(96);

  MyLib_ProcessRecord(&test_record, 1U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_counter)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(102), UNITY_DISPLAY_STYLE_UINT32);
}
void test_MyLib_ProcessRecord_Multiplier5_LoopAccumulation(void)
{
  test_record.id_u16 = 200U;
  test_record.value_u32 = 100U;

  uint32_t expected_accumulation = 100U * 5U;
  uint32_t expected_counter = initial_counter + expected_accumulation;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(126, expected_accumulation,
 ((void *)0)
 , 99U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(127);

  MyLib_ProcessRecord(&test_record, 5U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_counter)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(133), UNITY_DISPLAY_STYLE_UINT32);
}
void test_MyLib_ProcessRecord_MultiplierMax_BoundaryCase(void)
{
  test_record.id_u16 = 1U;
  test_record.value_u32 = 10U;

  uint32_t expected_accumulation = 10U * 255U;
  uint32_t expected_counter = initial_counter + expected_accumulation;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(157, expected_accumulation,
 ((void *)0)
 , 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(158);

  MyLib_ProcessRecord(&test_record, 255U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_counter)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(164), UNITY_DISPLAY_STYLE_UINT32);
}
void test_MyLib_ProcessRecord_WrapAroundAccumulation(void)
{
  g_counter_u32 =
                 (4294967295U)
                            - 100U;
  initial_counter = g_counter_u32;

  test_record.id_u16 = 10U;
  test_record.value_u32 = 200U;

  uint32_t expected_accumulation = 200U * 5U;
  uint32_t expected_counter = (
                              (4294967295U)
                                         - 100U) + 1000U;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(191, expected_accumulation,
 ((void *)0)
 , 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(192);

  MyLib_ProcessRecord(&test_record, 5U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_counter)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(198), UNITY_DISPLAY_STYLE_UINT32);
}
void test_MyLib_ProcessRecord_SequentialCalls_StateConsistency(void)
{
  test_record.id_u16 = 1U;
  test_record.value_u32 = 100U;

  uint32_t first_accumulation = 100U * 2U;
  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(218, first_accumulation,
 ((void *)0)
 , 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(219);

  MyLib_ProcessRecord(&test_record, 2U);
  uint32_t counter_after_first = g_counter_u32;

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((initial_counter + 200U)), (UNITY_INT)(UNITY_UINT32)((counter_after_first)), (
 ((void *)0)
 ), (UNITY_UINT)(225), UNITY_DISPLAY_STYLE_UINT32);

  test_record.value_u32 = 50U;
  uint32_t second_accumulation = 50U * 3U;
  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(230, second_accumulation,
 ((void *)0)
 , 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(231);

  MyLib_ProcessRecord(&test_record, 3U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((counter_after_first + 150U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(236), UNITY_DISPLAY_STYLE_UINT32);
}
void test_MyLib_ProcessRecord_MaxRecordValue(void)
{
  test_record.id_u16 = 65535U;
  test_record.value_u32 =
                         (4294967295U)

  uint32_t expected_accumulation =
                                  (4294967295U)

  uint32_t expected_counter = initial_counter + expected_accumulation;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(259, expected_accumulation,
 ((void *)0)
 , 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(260);

  MyLib_ProcessRecord(&test_record, 1U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_counter)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(266), UNITY_DISPLAY_STYLE_UINT32);
}
void test_MyLib_ProcessRecord_MockFunctionCalledWithCorrectParams(void)
{
  test_record.id_u16 = 100U;
  test_record.value_u32 = 300U;

  uint32_t expected_accumulation = 300U * 3U;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(288, expected_accumulation,
 ((void *)0)
 , 55U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(289);

  MyLib_ProcessRecord(&test_record, 3U);

  do { if ((
 1
 ))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((295))); } } while (0);
}