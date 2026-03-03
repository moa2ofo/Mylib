// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib_UpdateCounter_u8.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void test_system_not_ready_returns_error_code_1_and_no_counter_update(void)
{
  uint32_t initial_counter = 42U;
  g_counter_u32 = initial_counter;
  g_systemReady_b =
                   

  uint8_t result = MyLib_UpdateCounter_u8(10U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(17), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((initial_counter)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(18), UNITY_DISPLAY_STYLE_UINT32);
}

void test_system_ready_saturation_disabled_zero_increment_returns_0_counter_unchanged(void)
{
  uint32_t initial_counter = 50U;
  g_counter_u32 = initial_counter;
  g_systemReady_b =
                   1

  set_SaturationEn_b(
                    0
                         );

  uint8_t result = MyLib_UpdateCounter_u8(0U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((initial_counter)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_UINT32);
}

void test_system_ready_saturation_disabled_small_increment_returns_0_counter_updated(void)
{
  g_counter_u32 = 10U;
  g_systemReady_b =
                   1

  set_SaturationEn_b(
                    0
                         );
  set_CounterLimit_u32(100U);

  uint8_t result = MyLib_UpdateCounter_u8(5U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(47), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((15U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(48), UNITY_DISPLAY_STYLE_UINT32);
}

void test_system_ready_saturation_disabled_increment_causing_wraparound_returns_0_counter_wraps(void)
{
  g_counter_u32 =
                 (4294967295U)
                            - 5U;
  g_systemReady_b =
                   1

  set_SaturationEn_b(
                    0
                         );

  uint8_t result = MyLib_UpdateCounter_u8(10U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(61), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((4U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(62), UNITY_DISPLAY_STYLE_UINT32);
}

void test_system_ready_saturation_enabled_increment_below_limit_returns_0_counter_updated(void)
{
  g_counter_u32 = 20U;
  g_systemReady_b =
                   1

  set_SaturationEn_b(
                    1
                        );
  set_CounterLimit_u32(100U);

  uint8_t result = MyLib_UpdateCounter_u8(30U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(76), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((50U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(77), UNITY_DISPLAY_STYLE_UINT32);
}

void test_system_ready_saturation_enabled_increment_exactly_at_limit_returns_0_counter_equals_limit(void)
{
  g_counter_u32 = 50U;
  g_systemReady_b =
                   1

  set_SaturationEn_b(
                    1
                        );
  set_CounterLimit_u32(100U);

  uint8_t result = MyLib_UpdateCounter_u8(50U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(91), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(92), UNITY_DISPLAY_STYLE_UINT32);
}

void test_system_ready_saturation_enabled_increment_exceeding_limit_by_one_returns_2_counter_clamped(void)
{
  g_counter_u32 = 50U;
  g_systemReady_b =
                   1

  set_SaturationEn_b(
                    1
                        );
  set_CounterLimit_u32(100U);

  uint8_t result = MyLib_UpdateCounter_u8(51U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(106), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(107), UNITY_DISPLAY_STYLE_UINT32);
}

void test_system_ready_saturation_enabled_large_increment_far_exceeding_limit_returns_2_counter_clamped(void)
{
  g_counter_u32 = 10U;
  g_systemReady_b =
                   1

  set_SaturationEn_b(
                    1
                        );
  set_CounterLimit_u32(100U);

  uint8_t result = MyLib_UpdateCounter_u8(1000U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(121), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(122), UNITY_DISPLAY_STYLE_UINT32);
}

void test_system_ready_saturation_enabled_increment_causing_wraparound_before_saturation_returns_2_counter_clamped(void)
{
  g_counter_u32 =
                 (4294967295U)
                            - 10U;
  g_systemReady_b =
                   1

  set_SaturationEn_b(
                    1
                        );
  set_CounterLimit_u32(100U);

  uint8_t result = MyLib_UpdateCounter_u8(20U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(136), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(137), UNITY_DISPLAY_STYLE_UINT32);
}

void test_cycle_counter_toggle_saturation_toggles_after_16_calls(void)
{
  g_systemReady_b =
                   1

  g_counter_u32 = 0U;
  set_SaturationEn_b(
                    0
                         );
  set_CounterLimit_u32(1000U);

 _Bool
      initial_saturation = get_SaturationEn_b();

  for(uint8_t i = 0U; i < 15U; i++)
{
    MyLib_UpdateCounter_u8(1U);
  }

  UnityAssertEqualNumber((UNITY_INT)((initial_saturation)), (UNITY_INT)((get_SaturationEn_b())), (
 ((void *)0)
 ), (UNITY_UINT)(155), UNITY_DISPLAY_STYLE_INT);

  MyLib_UpdateCounter_u8(1U);

  UnityAssertEqualNumber((UNITY_INT)((!initial_saturation)), (UNITY_INT)((get_SaturationEn_b())), (
 ((void *)0)
 ), (UNITY_UINT)(159), UNITY_DISPLAY_STYLE_INT);
}

void test_cycle_counter_toggle_saturation_does_not_toggle_on_call_15(void)
{
  g_systemReady_b =
                   1

  g_counter_u32 = 0U;
  set_SaturationEn_b(
                    1
                        );
  set_CounterLimit_u32(1000U);

 _Bool
      initial_saturation = get_SaturationEn_b();

  for(uint8_t i = 0U; i < 15U; i++)
{
    MyLib_UpdateCounter_u8(1U);
  }

  UnityAssertEqualNumber((UNITY_INT)((initial_saturation)), (UNITY_INT)((get_SaturationEn_b())), (
 ((void *)0)
 ), (UNITY_UINT)(177), UNITY_DISPLAY_STYLE_INT);
}

void test_cycle_counter_toggle_saturation_does_not_toggle_on_call_17(void)
{
  g_systemReady_b =
                   1

  g_counter_u32 = 0U;
  set_SaturationEn_b(
                    0
                         );
  set_CounterLimit_u32(1000U);

  for(uint8_t i = 0U; i < 16U; i++)
{
    MyLib_UpdateCounter_u8(1U);
  }

 _Bool
      saturation_after_16 = get_SaturationEn_b();

  MyLib_UpdateCounter_u8(1U);

  UnityAssertEqualNumber((UNITY_INT)((saturation_after_16)), (UNITY_INT)((get_SaturationEn_b())), (
 ((void *)0)
 ), (UNITY_UINT)(197), UNITY_DISPLAY_STYLE_INT);
}

void test_cycle_counter_toggle_persistence_saturation_toggles_again_at_call_32(void)
{
  g_systemReady_b =
                   1

  g_counter_u32 = 0U;
  set_SaturationEn_b(
                    0
                         );
  set_CounterLimit_u32(1000U);

 _Bool
      initial_saturation = get_SaturationEn_b();

  for(uint8_t i = 0U; i < 16U; i++)
{
    MyLib_UpdateCounter_u8(1U);
  }

 _Bool
      saturation_after_16 = get_SaturationEn_b();
  UnityAssertEqualNumber((UNITY_INT)((!initial_saturation)), (UNITY_INT)((saturation_after_16)), (
 ((void *)0)
 ), (UNITY_UINT)(216), UNITY_DISPLAY_STYLE_INT);

  for(uint8_t i = 0U; i < 16U; i++)
{
    MyLib_UpdateCounter_u8(1U);
  }

  UnityAssertEqualNumber((UNITY_INT)((initial_saturation)), (UNITY_INT)((get_SaturationEn_b())), (
 ((void *)0)
 ), (UNITY_UINT)(222), UNITY_DISPLAY_STYLE_INT);
}

void test_system_not_ready_after_multiple_ready_calls_returns_1_counter_unchanged(void)
{
  g_systemReady_b =
                   1

  g_counter_u32 = 10U;
  set_SaturationEn_b(
                    0
                         );
  set_CounterLimit_u32(100U);

  MyLib_UpdateCounter_u8(5U);
  MyLib_UpdateCounter_u8(5U);

  uint32_t counter_before_not_ready = g_counter_u32;

  g_systemReady_b =
                   

  uint8_t result = MyLib_UpdateCounter_u8(10U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(243), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((counter_before_not_ready)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(244), UNITY_DISPLAY_STYLE_UINT32);
}

void test_saturation_boundary_counter_at_limit_minus_one_increment_by_one_returns_0_counter_equals_limit(void)
{
  g_systemReady_b =
                   1

  set_CounterLimit_u32(100U);
  g_counter_u32 = 99U;
  set_SaturationEn_b(
                    1
                        );

  uint8_t result = MyLib_UpdateCounter_u8(1U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(258), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(259), UNITY_DISPLAY_STYLE_UINT32);
}

void test_saturation_boundary_counter_at_limit_increment_by_one_returns_2_counter_remains_at_limit(void)
{
  g_systemReady_b =
                   1

  set_CounterLimit_u32(100U);
  g_counter_u32 = 100U;
  set_SaturationEn_b(
                    1
                        );

  uint8_t result = MyLib_UpdateCounter_u8(1U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(273), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(274), UNITY_DISPLAY_STYLE_UINT32);
}

void test_saturation_boundary_counter_at_zero_increment_to_exactly_limit_returns_0_counter_equals_limit(void)
{
  g_systemReady_b =
                   1

  set_CounterLimit_u32(100U);
  g_counter_u32 = 0U;
  set_SaturationEn_b(
                    1
                        );

  uint8_t result = MyLib_UpdateCounter_u8(100U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(288), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(289), UNITY_DISPLAY_STYLE_UINT32);
}

void test_saturation_boundary_counter_at_zero_increment_to_limit_plus_one_returns_2_counter_clamped(void)
{
  g_systemReady_b =
                   1

  set_CounterLimit_u32(100U);
  g_counter_u32 = 0U;
  set_SaturationEn_b(
                    1
                        );

  uint8_t result = MyLib_UpdateCounter_u8(101U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(303), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(304), UNITY_DISPLAY_STYLE_UINT32);
}

void test_maximum_uint32_increment_counter_at_zero_add_max_saturation_disabled_returns_0_counter_wraps_to_max(void)
{
  g_systemReady_b =
                   1

  g_counter_u32 = 0U;
  set_SaturationEn_b(
                    0
                         );

  uint8_t result = MyLib_UpdateCounter_u8(
                                         (4294967295U)
                                                   );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(317), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((
 (4294967295U)
 )), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(318), UNITY_DISPLAY_STYLE_UINT32);
}

void test_maximum_uint32_increment_counter_at_one_add_max_saturation_disabled_returns_0_counter_wraps_to_zero(void)
{
  g_systemReady_b =
                   1

  g_counter_u32 = 1U;
  set_SaturationEn_b(
                    0
                         );

  uint8_t result = MyLib_UpdateCounter_u8(
                                         (4294967295U)
                                                   );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(331), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(332), UNITY_DISPLAY_STYLE_UINT32);
}

void test_saturation_disabled_counter_at_max_increment_by_one_returns_0_counter_wraps_to_zero(void)
{
  g_systemReady_b =
                   1

  g_counter_u32 =
                 (4294967295U)

  set_SaturationEn_b(
                    0
                         );

  uint8_t result = MyLib_UpdateCounter_u8(1U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(345), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(346), UNITY_DISPLAY_STYLE_UINT32);
}

void test_limit_set_to_max_saturation_enabled_any_increment_returns_0_new_value_cannot_exceed_limit(void)
{
  g_systemReady_b =
                   1

  set_CounterLimit_u32(
                      (4294967295U)
                                );
  g_counter_u32 = 100U;
  set_SaturationEn_b(
                    1
                        );

  uint8_t result = MyLib_UpdateCounter_u8(1000U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(360), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(361), UNITY_DISPLAY_STYLE_UINT32);
}

void test_limit_set_to_zero_saturation_enabled_any_nonzero_increment_returns_2_counter_clamped_to_zero(void)
{
  g_systemReady_b =
                   1

  set_CounterLimit_u32(0U);
  g_counter_u32 = 0U;
  set_SaturationEn_b(
                    1
                        );

  uint8_t result = MyLib_UpdateCounter_u8(1U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(375), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(376), UNITY_DISPLAY_STYLE_UINT32);
}

void test_cycle_counter_increments_across_system_not_ready_calls(void)
{
  g_systemReady_b =
                   1

  g_counter_u32 = 0U;
  set_SaturationEn_b(
                    0
                         );
  set_CounterLimit_u32(1000U);

  for(uint8_t i = 0U; i < 8U; i++)
{
    MyLib_UpdateCounter_u8(1U);
  }

  g_systemReady_b =
                   

  for(uint8_t i = 0U; i < 8U; i++)
{
    uint8_t result = MyLib_UpdateCounter_u8(1U);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
   ((void *)0)
   ), (UNITY_UINT)(396), UNITY_DISPLAY_STYLE_UINT8);
  }

  g_systemReady_b =
                   

 _Bool
      saturation_before = get_SaturationEn_b();

  MyLib_UpdateCounter_u8(1U);

  UnityAssertEqualNumber((UNITY_INT)((!saturation_before)), (UNITY_INT)((get_SaturationEn_b())), (
 ((void *)0)
 ), (UNITY_UINT)(404), UNITY_DISPLAY_STYLE_INT);
}

void setUp(void)
{
  g_counter_u32 = 0U;
  g_systemReady_b =
                   0

  set_CounterLimit_u32(0U);
  set_SaturationEn_b(
                    0
                         );
}

void tearDown(void)
{
}

void test_system_not_ready_after_multiple_ready_calls_returns_1_counter_unchanged(void)
{
  g_systemReady_b =
                   1

  g_counter_u32 = 10U;
  set_SaturationEn_b(
                    0
                         );
  set_CounterLimit_u32(100U);

  MyLib_UpdateCounter_u8(5U);
  MyLib_UpdateCounter_u8(5U);

  uint32_t counter_before_not_ready = g_counter_u32;

  g_systemReady_b =
                   

  uint8_t result = MyLib_UpdateCounter_u8(10U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(432), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((counter_before_not_ready)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(433), UNITY_DISPLAY_STYLE_UINT32);
}