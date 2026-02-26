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
{
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
   ), (UNITY_UINT)(41), UNITY_DISPLAY_STYLE_UINT8);

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
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((52))); } } while (0);

  saturation_state = GetSaturationEn_b();

 _Bool
      second_toggle_found =
                            

  for(int i = 0; i < 16; i++)
{
    result = MyLib_UpdateCounter_u8(1U);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
   ((void *)0)
   ), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_UINT8);

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
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((70))); } } while (0);
}