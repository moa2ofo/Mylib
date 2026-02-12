// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_UpdateCounter_u8.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
  g_counter_u32 = 0U;
  g_systemReady_b =
                   0

  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;

  SetCounterLimit_u32((100U));
  SetSaturationEn_b(
                   1
                       );
}

void tearDown(void)
{ }

void test_MyLib_UpdateCounter_u8_SystemNotReady_ReturnOne(void)
{
  uint8_t result;

  g_systemReady_b =
                   0

  g_counter_u32 = 0U;

  result = MyLib_UpdateCounter_u8(10U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(41), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_UINT32);
}

void test_MyLib_UpdateCounter_u8_SystemNotReady_CounterPreserved(void)
{
  uint8_t result;

  g_systemReady_b =
                   0

  g_counter_u32 = 42U;

  result = MyLib_UpdateCounter_u8(100U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(64), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((42U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(67), UNITY_DISPLAY_STYLE_UINT32);
}
void test_MyLib_UpdateCounter_u8_SystemReady_NormalAdd_ReturnZero(void)
{
  uint8_t result;

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   1
                       );
  SetCounterLimit_u32((100U));
  g_counter_u32 = 10U;

  result = MyLib_UpdateCounter_u8(5U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(90), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((15U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(93), UNITY_DISPLAY_STYLE_UINT32);
}

void test_MyLib_UpdateCounter_u8_SaturationEnabled_OverflowPrevented(void)
{
  uint8_t result;

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   1
                       );
  SetCounterLimit_u32(100U);
  g_counter_u32 = 90U;

  result = MyLib_UpdateCounter_u8(20U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(115), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(118), UNITY_DISPLAY_STYLE_UINT32);
}

void test_MyLib_UpdateCounter_u8_SaturationDisabled_OverflowAllowed(void)
{
  uint8_t result;

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   0
                        );
  SetCounterLimit_u32(100U);
  g_counter_u32 = 90U;

  result = MyLib_UpdateCounter_u8(20U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(140), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((110U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(143), UNITY_DISPLAY_STYLE_UINT32);
}

void test_MyLib_UpdateCounter_u8_ZeroAddition(void)
{
  uint8_t result;

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   1
                       );
  g_counter_u32 = 50U;

  result = MyLib_UpdateCounter_u8(0U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(164), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((50U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(167), UNITY_DISPLAY_STYLE_UINT32);
}

void test_MyLib_UpdateCounter_u8_MaxValueAddition_SaturationEnabled(void)
{
  uint8_t result;

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   1
                       );
  SetCounterLimit_u32(100U);
  g_counter_u32 = 0U;

  result = MyLib_UpdateCounter_u8(0xFFFFFFFFU);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(189), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(192), UNITY_DISPLAY_STYLE_UINT32);
}

void test_MyLib_UpdateCounter_u8_CounterAtLimit_SaturationTriggered(void)
{
  uint8_t result;

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   1
                       );
  SetCounterLimit_u32(100U);
  g_counter_u32 = 100U;

  result = MyLib_UpdateCounter_u8(1U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(214), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(217), UNITY_DISPLAY_STYLE_UINT32);
}

void test_MyLib_UpdateCounter_u8_CounterAtLimit_NoAddition(void)
{
  uint8_t result;

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   1
                       );
  SetCounterLimit_u32(100U);
  g_counter_u32 = 100U;

  result = MyLib_UpdateCounter_u8(0U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(239), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(242), UNITY_DISPLAY_STYLE_UINT32);
}
void test_MyLib_UpdateCounter_u8_CycleCountTogglePattern_Every16Calls(void)
{
  uint8_t result;

 _Bool
      saturation_state;
  int toggle_count = 0;

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   1
                       );
  SetCounterLimit_u32(100U);
  g_counter_u32 = 0U;
  saturation_state =
                    

  for(int i = 0; i < 32; i++)
{
    result = MyLib_UpdateCounter_u8(1U);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
   ((void *)0)
   ), (UNITY_UINT)(268), UNITY_DISPLAY_STYLE_UINT8);

   _Bool
        current_state = GetSaturationEn_b();
    if(current_state != saturation_state)
{
      toggle_count++;
      saturation_state = current_state;
    }
  }

  UnityAssertGreaterOrLessOrEqualNumber((UNITY_INT) ((1)), (UNITY_INT) ((toggle_count)), UNITY_GREATER_OR_EQUAL, (
 ((void *)0)
 ), (UNITY_UINT)(279), UNITY_DISPLAY_STYLE_INT);
  UnityAssertGreaterOrLessOrEqualNumber((UNITY_INT) ((2)), (UNITY_INT) ((toggle_count)), UNITY_SMALLER_OR_EQUAL, (
 ((void *)0)
 ), (UNITY_UINT)(280), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((32U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(283), UNITY_DISPLAY_STYLE_UINT32);
}
void test_MyLib_UpdateCounter_u8_CycleCountToggle_FindPattern(void)
{
  uint8_t result;

 _Bool
      saturation_state;

 _Bool
      first_toggle_found =
                           0

  int calls_to_first_toggle = 0;

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   1
                       );
  SetCounterLimit_u32(100U);
  g_counter_u32 = 0U;
  saturation_state = GetSaturationEn_b();

  for(int i = 0; i < 16; i++)
{
    result = MyLib_UpdateCounter_u8(1U);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
   ((void *)0)
   ), (UNITY_UINT)(310), UNITY_DISPLAY_STYLE_UINT8);

   _Bool
        current_state = GetSaturationEn_b();
    if(current_state != saturation_state)
{
      first_toggle_found =
                          1

      calls_to_first_toggle = i + 1;
      break;
    }
  }

  do { if ((first_toggle_found))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((321))); } } while (0);

  saturation_state = GetSaturationEn_b();

 _Bool
      second_toggle_found =
                            

  for(int i = 0; i < 16; i++)
{
    result = MyLib_UpdateCounter_u8(1U);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
   ((void *)0)
   ), (UNITY_UINT)(329), UNITY_DISPLAY_STYLE_UINT8);

   _Bool
        current_state = GetSaturationEn_b();
    if(current_state != saturation_state)
{
      second_toggle_found =
                           1

      break;
    }
  }

  do { if ((second_toggle_found))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((339))); } } while (0);
}
void test_MyLib_UpdateCounter_u8_MultipleCycleToggles(void)
{
  uint8_t result;

 _Bool
      saturation_state;
  int toggle_count = 0;

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   1
                       );
  SetCounterLimit_u32(100U);
  g_counter_u32 = 0U;

  saturation_state = GetSaturationEn_b();

  for(int i = 0; i < 48; i++)
{
    result = MyLib_UpdateCounter_u8(1U);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
   ((void *)0)
   ), (UNITY_UINT)(365), UNITY_DISPLAY_STYLE_UINT8);

   _Bool
        current_state = GetSaturationEn_b();
    if(current_state != saturation_state)
{
      toggle_count++;
      saturation_state = current_state;
    }
  }

  UnityAssertGreaterOrLessOrEqualNumber((UNITY_INT) ((2)), (UNITY_INT) ((toggle_count)), UNITY_GREATER_OR_EQUAL, (
 ((void *)0)
 ), (UNITY_UINT)(375), UNITY_DISPLAY_STYLE_INT);
  UnityAssertGreaterOrLessOrEqualNumber((UNITY_INT) ((3)), (UNITY_INT) ((toggle_count)), UNITY_SMALLER_OR_EQUAL, (
 ((void *)0)
 ), (UNITY_UINT)(376), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((48U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(379), UNITY_DISPLAY_STYLE_UINT32);
}

void test_MyLib_UpdateCounter_u8_CycleToggle_FromDisabledToEnabled(void)
{
  uint8_t result;

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   0
                        );
  SetCounterLimit_u32(100U);
  g_counter_u32 = 0U;

  for(int i = 0; i < 15; i++)
{
    result = MyLib_UpdateCounter_u8(1U);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
   ((void *)0)
   ), (UNITY_UINT)(400), UNITY_DISPLAY_STYLE_UINT8);
    UnityAssertEqualNumber((UNITY_INT)((
   0
   )), (UNITY_INT)((GetSaturationEn_b())), (
   ((void *)0)
   ), (UNITY_UINT)(401), UNITY_DISPLAY_STYLE_INT);
  }

  result = MyLib_UpdateCounter_u8(1U);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(406), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)((
 1
 )), (UNITY_INT)((GetSaturationEn_b())), (
 ((void *)0)
 ), (UNITY_UINT)(409), UNITY_DISPLAY_STYLE_INT);
}

void test_MyLib_UpdateCounter_u8_CustomLimit_BelowLimit(void)
{
  uint8_t result;

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   1
                       );
  SetCounterLimit_u32(50U);
  g_counter_u32 = 40U;

  result = MyLib_UpdateCounter_u8(5U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(431), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((45U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(434), UNITY_DISPLAY_STYLE_UINT32);
}

void test_MyLib_UpdateCounter_u8_CustomLimit_ExceedsLimit(void)
{
  uint8_t result;

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   1
                       );
  SetCounterLimit_u32(50U);
  g_counter_u32 = 48U;

  result = MyLib_UpdateCounter_u8(10U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(456), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((50U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(459), UNITY_DISPLAY_STYLE_UINT32);
}

void test_MyLib_UpdateCounter_u8_CounterAtZero_WithAddition(void)
{
  uint8_t result;

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   1
                       );
  g_counter_u32 = 0U;

  result = MyLib_UpdateCounter_u8(42U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(480), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((42U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(483), UNITY_DISPLAY_STYLE_UINT32);
}

void test_MyLib_UpdateCounter_u8_ExactLimitBoundary_NoOverflow(void)
{
  uint8_t result;

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   1
                       );
  SetCounterLimit_u32(100U);
  g_counter_u32 = 95U;

  result = MyLib_UpdateCounter_u8(5U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(505), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(508), UNITY_DISPLAY_STYLE_UINT32);
}

void test_MyLib_UpdateCounter_u8_PastLimitBoundary_OverflowBy1(void)
{
  uint8_t result;

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   1
                       );
  SetCounterLimit_u32(100U);
  g_counter_u32 = 95U;

  result = MyLib_UpdateCounter_u8(6U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(530), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(533), UNITY_DISPLAY_STYLE_UINT32);
}

void test_MyLib_UpdateCounter_u8_SaturationDisabled_ExactBoundary(void)
{
  uint8_t result;

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   0
                        );
  SetCounterLimit_u32(100U);
  g_counter_u32 = 95U;

  result = MyLib_UpdateCounter_u8(5U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(555), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(558), UNITY_DISPLAY_STYLE_UINT32);
}

void test_MyLib_UpdateCounter_u8_SystemReadyTransition(void)
{
  uint8_t result;

  g_systemReady_b =
                   0

  g_counter_u32 = 0U;

  result = MyLib_UpdateCounter_u8(10U);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(576), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(577), UNITY_DISPLAY_STYLE_UINT32);

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   1
                       );

  result = MyLib_UpdateCounter_u8(10U);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(585), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((10U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(588), UNITY_DISPLAY_STYLE_UINT32);
}

void test_MyLib_UpdateCounter_u8_LargeCounterValue_WithinLimit(void)
{
  uint8_t result;

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   1
                       );
  SetCounterLimit_u32(2000000000U);
  g_counter_u32 = 1000000000U;

  result = MyLib_UpdateCounter_u8(500000000U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(610), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1500000000U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(613), UNITY_DISPLAY_STYLE_UINT32);
}

void test_MyLib_UpdateCounter_u8_LargeCounterValue_ExceedsLimit(void)
{
  uint8_t result;

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   1
                       );
  SetCounterLimit_u32(2000000000U);
  g_counter_u32 = 1800000000U;

  result = MyLib_UpdateCounter_u8(300000000U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(635), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((2000000000U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(638), UNITY_DISPLAY_STYLE_UINT32);
}