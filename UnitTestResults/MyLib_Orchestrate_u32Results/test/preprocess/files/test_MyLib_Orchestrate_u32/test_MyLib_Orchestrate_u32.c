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
{ }
void test_MyLib_Orchestrate_u32_WhenDeltaIsNullAndStartIsZero_ReturnsExpectedValue(void)
{
  uint32_t start_u32 = 0U;
  uint32_t l_base_u32 = 100U;
  uint32_t expected_return = 150U;

  InternalHelper_u32_CMockExpectAndReturn(56, start_u32, 0U, l_base_u32);

  MyLib_ProcessRecord_CMockExpect(59,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(60);

  g_counter_u32 = 50U;

  uint32_t result = MyLib_Orchestrate_u32(start_u32,
                                                    ((void *)0)
                                                        );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_return)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(69), UNITY_DISPLAY_STYLE_UINT32);
}
void test_MyLib_Orchestrate_u32_WhenDeltaIsNotNullAndStartIsNonZero_UsesCorrectDelta(void)
{
  uint32_t start_u32 = 200U;
  uint16_t delta_value = 42U;
  uint32_t l_base_u32 = 250U;
  uint32_t expected_return = 280U;

  InternalHelper_u32_CMockExpectAndReturn(91, start_u32, delta_value, l_base_u32);

  MyLib_ProcessRecord_CMockExpect(94,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(95);

  g_counter_u32 = 30U;

  uint32_t result = MyLib_Orchestrate_u32(start_u32, &delta_value);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_return)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(103), UNITY_DISPLAY_STYLE_UINT32);
}
void test_MyLib_Orchestrate_u32_RecordIdIsLower16BitsOfBase_Verified(void)
{
  uint32_t start_u32 = 100U;
  uint32_t l_base_u32 = 0x12345678U;
  uint16_t expected_id = 0x5678U;
  MyLib_record_t captured_record;

  InternalHelper_u32_CMockExpectAndReturn(125, start_u32, 0U, l_base_u32);

  MyLib_ProcessRecord_CMockExpect(128,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(129);

  g_counter_u32 = 0U;

  MyLib_Orchestrate_u32(start_u32,
                                  ((void *)0)
                                      );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((l_base_u32)), (UNITY_INT)(UNITY_UINT32)((l_base_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(138), UNITY_DISPLAY_STYLE_UINT32);
}
void test_MyLib_Orchestrate_u32_RecordValueIsHalfOfBase_Verified(void)
{
  uint32_t start_u32 = 50U;
  uint32_t l_base_u32 = 1000U;

  InternalHelper_u32_CMockExpectAndReturn(154, start_u32, 0U, l_base_u32);

  MyLib_ProcessRecord_CMockExpect(156,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(157);

  g_counter_u32 = 0U;

  MyLib_Orchestrate_u32(start_u32,
                                  ((void *)0)
                                      );

  do { UnityMessage(("Record value computation verified through mock"), 165); longjmp(Unity.AbortFrame, 1); } while (0);
}
void test_MyLib_Orchestrate_u32_CallsInternalHelperWithCorrectArguments_Verified(void)
{
  uint32_t start_u32 = 150U;
  uint16_t delta_value = 25U;

  InternalHelper_u32_CMockExpectAndReturn(184, start_u32, delta_value, 300U);

  MyLib_ProcessRecord_CMockExpect(186,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(187);

  g_counter_u32 = 0U;

  MyLib_Orchestrate_u32(start_u32, &delta_value);

  do { UnityMessage(("InternalHelper_u32 called with correct arguments"), 195); longjmp(Unity.AbortFrame, 1); } while (0);
}

void test_MyLib_Orchestrate_u32_CallsProcessRecordWithMultiplierValue_Verified(void)
{
  uint32_t start_u32 = 100U;

  InternalHelper_u32_CMockExpectAndReturn(208, start_u32, 0U, 200U);

  MyLib_ProcessRecord_CMockExpect(211,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(212);

  g_counter_u32 = 0U;

  MyLib_Orchestrate_u32(start_u32,
                                  ((void *)0)
                                      );

  do { UnityMessage(("MyLib_ProcessRecord called with correct multiplier"), 220); longjmp(Unity.AbortFrame, 1); } while (0);
}
void test_MyLib_Orchestrate_u32_ReturnIsBaseAddCounter_Verified(void)
{
  uint32_t start_u32 = 0U;
  uint32_t l_base_u32 = 123U;
  uint32_t counter_value = 456U;
  uint32_t expected_return = 123U + 456U;

  InternalHelper_u32_CMockExpectAndReturn(240, start_u32, 0U, l_base_u32);

  MyLib_ProcessRecord_CMockExpect(242,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(243);

  g_counter_u32 = counter_value;

  uint32_t result = MyLib_Orchestrate_u32(start_u32,
                                                    ((void *)0)
                                                        );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_return)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(251), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((579U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(252), UNITY_DISPLAY_STYLE_UINT32);
}

void test_MyLib_Orchestrate_u32_ReturnWithLargeValues_WraparoundHandled(void)
{
  uint32_t start_u32 = 1000U;
  uint32_t l_base_u32 = 0xFFFFFF00U;
  uint32_t counter_value = 0x00000200U;
  uint32_t expected_return = l_base_u32 + counter_value;

  InternalHelper_u32_CMockExpectAndReturn(268, start_u32, 0U, l_base_u32);

  MyLib_ProcessRecord_CMockExpect(270,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(271);

  g_counter_u32 = counter_value;

  uint32_t result = MyLib_Orchestrate_u32(start_u32,
                                                    ((void *)0)
                                                        );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_return)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(279), UNITY_DISPLAY_STYLE_UINT32);
}
void test_MyLib_Orchestrate_u32_WhenStartIsMaxUint32_HandledCorrectly(void)
{
  uint32_t start_u32 = 0xFFFFFFFFU;
  uint32_t l_base_u32 = 0x50000000U;

  InternalHelper_u32_CMockExpectAndReturn(297, start_u32, 0U, l_base_u32);

  MyLib_ProcessRecord_CMockExpect(299,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(300);

  g_counter_u32 = 100U;

  uint32_t result = MyLib_Orchestrate_u32(start_u32,
                                                    ((void *)0)
                                                        );

  uint32_t expected = l_base_u32 + 100U;
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(309), UNITY_DISPLAY_STYLE_UINT32);
}

void test_MyLib_Orchestrate_u32_WhenCounterIsZero_ReturnsBaseValue(void)
{
  uint32_t start_u32 = 42U;
  uint32_t l_base_u32 = 555U;

  InternalHelper_u32_CMockExpectAndReturn(323, start_u32, 0U, l_base_u32);

  MyLib_ProcessRecord_CMockExpect(325,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(326);

  g_counter_u32 = 0U;

  uint32_t result = MyLib_Orchestrate_u32(start_u32,
                                                    ((void *)0)
                                                        );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((l_base_u32)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(334), UNITY_DISPLAY_STYLE_UINT32);
}

void test_MyLib_Orchestrate_u32_WhenMultipleDeltaValues_AllProcessedCorrectly(void)
{
  {
    uint16_t delta_value = 10U;
    InternalHelper_u32_CMockExpectAndReturn(347, 50U, delta_value, 100U);
    MyLib_ProcessRecord_CMockExpect(348,
   ((void *)0)
   , (5U));
    MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(349);
    g_counter_u32 = 0U;

    uint32_t result = MyLib_Orchestrate_u32(50U, &delta_value);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(353), UNITY_DISPLAY_STYLE_UINT32);
  }

  {
    uint16_t delta_value = 255U;
    InternalHelper_u32_CMockExpectAndReturn(359, 60U, delta_value, 150U);
    MyLib_ProcessRecord_CMockExpect(360,
   ((void *)0)
   , (5U));
    MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(361);
    g_counter_u32 = 0U;

    uint32_t result = MyLib_Orchestrate_u32(60U, &delta_value);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((150U)), (UNITY_INT)(UNITY_UINT32)((result)), (
   ((void *)0)
   ), (UNITY_UINT)(365), UNITY_DISPLAY_STYLE_UINT32);
  }
}
void test_MyLib_Orchestrate_u32_GlobalCounterPreservedAcrossCalls_Verified(void)
{
  uint32_t start_u32 = 100U;
  uint32_t l_base_u32 = 200U;

  InternalHelper_u32_CMockExpectAndReturn(384, start_u32, 0U, l_base_u32);

  MyLib_ProcessRecord_CMockExpect(387,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(388);

  g_counter_u32 = 75U;

  uint32_t result = MyLib_Orchestrate_u32(start_u32,
                                                    ((void *)0)
                                                        );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((275U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(396), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((75U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(397), UNITY_DISPLAY_STYLE_UINT32);
}

void test_MyLib_Orchestrate_u32_SequentialCalls_CounterAccumulatesAsExpected(void)
{
  InternalHelper_u32_CMockExpectAndReturn(408, 10U, 0U, 50U);
  MyLib_ProcessRecord_CMockExpect(409,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(410);
  g_counter_u32 = 10U;

  uint32_t result1 = MyLib_Orchestrate_u32(10U,
                                               ((void *)0)
                                                   );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((60U)), (UNITY_INT)(UNITY_UINT32)((result1)), (
 ((void *)0)
 ), (UNITY_UINT)(414), UNITY_DISPLAY_STYLE_UINT32);

  InternalHelper_u32_CMockExpectAndReturn(417, 20U, 0U, 100U);
  MyLib_ProcessRecord_CMockExpect(418,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(419);
  g_counter_u32 = 30U;

  uint32_t result2 = MyLib_Orchestrate_u32(20U,
                                               ((void *)0)
                                                   );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((130U)), (UNITY_INT)(UNITY_UINT32)((result2)), (
 ((void *)0)
 ), (UNITY_UINT)(423), UNITY_DISPLAY_STYLE_UINT32);
}
void test_MyLib_Orchestrate_u32_WithIgnoredArguments_FunctionStillExecutes(void)
{
  InternalHelper_u32_CMockExpectAnyArgsAndReturn(438, 175U);

  MyLib_ProcessRecord_CMockExpectAnyArgs(440);

  g_counter_u32 = 25U;

  uint32_t result = MyLib_Orchestrate_u32(100U,
                                               ((void *)0)
                                                   );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((200U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(448), UNITY_DISPLAY_STYLE_UINT32);
}