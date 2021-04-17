// !!! DO NOT ADD #pragma once !!! //
//#include <print.h>

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(kitt_effect)
RGB_MATRIX_EFFECT(SOLID_REACTIVE_SIMPLE_B)
RGB_MATRIX_EFFECT(pixelanim)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

//==============================================================================================

// KITT EFFECT

uint8_t k_led_count = 8;
uint8_t k_led_first = 14;
static uint8_t time_to_led(uint8_t time, uint8_t led_behind) {
    uint16_t led_time = k_led_count * time;
    uint16_t step = ((2 * k_led_count + (led_time / 128)) - led_behind) % (2 * k_led_count);
    uint8_t led;
    if (step < k_led_count) {
        led = step;
    } else {
        led = k_led_count - 1 - (step - k_led_count);
    }
    return led;
}

static HSV kitt_effect_math(HSV hsv, uint8_t i, uint8_t time) {

    hsv.h = 0;
    hsv.s = 255;

    if (i >= k_led_first && i < k_led_first + k_led_count) {
        uint8_t j = i - k_led_first;
        if (j == time_to_led(time, 0)) {
            hsv.v = hsv.v;
        } else if (j == time_to_led(time, 1)) {
            hsv.v = hsv.v/2;
        } else if (j == time_to_led(time, 2)) {
            hsv.v = hsv.v/4;
        } else if (j == time_to_led(time, 3)) {
            hsv.v = hsv.v/8;
        } else {
            hsv.v = 0;
        }
    } else {
        hsv.v = 0;
    }

    return hsv;
}

bool kitt_effect(effect_params_t* params) {
    return effect_runner_i(params, &kitt_effect_math);
}

//==============================================================================================

// Bottom Reactive

static HSV SOLID_REACTIVE_SIMPLE_B_math(HSV hsv, uint16_t offset) {
    hsv.v = scale8(255 - offset, hsv.v);
    return hsv;
}

bool SOLID_REACTIVE_SIMPLE_B(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  HSV hsv  = rgb_matrix_config.hsv;
  RGB rgb = hsv_to_rgb(hsv);

  effect_runner_reactive(params, &SOLID_REACTIVE_SIMPLE_B_math);
    for (uint16_t i = led_min; i < led_max; i++) {
      if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
      }
    }

  return led_max < DRIVER_LED_TOTAL;
}

//==============================================================================================

// PIXELANIM

int faceArray[8][54] = {

  { //00
    1,1,1,1,0,1,1,1,1,0,1,1,
    0,1,1,0,0,1,1,1,0,0,1,1,
    0,1,1,0,0,1,0,0,0,0,0,0,
    0,1,1,0,0, 1 ,1,1,0,1,1,

      0,    0,    0,   0,   0,   0
  },
  { //01
    1,1,1,0,1,1,1,1,0,1,1,1,
    1,1,0,0,1,1,1,0,0,1,1,0,
    1,1,0,0,1,0,0,0,0,0,0,1,
    1,1,0,0,1, 1 ,1,0,1,1,1,

      0,    0,    0,   0,   0,   0
  },
  { //02
    1,1,0,1,1,1,1,0,1,1,1,1,
    1,0,0,1,1,1,0,0,1,1,0,0,
    1,0,0,1,0,0,0,0,0,0,1,1,
    1,0,0,1,1, 1 ,0,1,1,1,1,

      0,    0,    0,   0,   0,   0
  },
  { //03
    1,0,1,1,1,1,0,1,1,1,1,0,
    0,0,1,1,1,0,0,1,1,0,0,0,
    0,0,1,0,0,0,0,0,0,1,1,0,
    0,0,1,1,1, 0 ,1,1,1,1,0,

      0,    0,    0,   0,   0,   0
  },
  { //04
    0,1,1,1,1,0,1,1,1,1,0,1,
    0,1,1,1,0,0,1,1,0,0,0,0,
    0,1,0,0,0,0,0,0,1,1,0,0,
    0,1,1,1,1, 0 ,1,1,1,0,0,

      0,    0,    0,   0,   0,   0
  },
  { //05
    1,1,1,1,0,1,1,1,1,0,1,1,
    1,1,1,0,0,1,1,0,0,0,0,1,
    1,0,0,0,0,0,0,1,1,0,0,1,
    1,1,1,1,0, 1 ,1,1,0,0,1,

      0,    0,    0,   0,   0,   0
  },
  { //06
    1,1,1,0,1,1,1,1,0,1,1,1,
    1,1,0,0,1,1,0,0,0,0,1,1,
    0,0,0,0,0,0,1,1,0,0,1,1,
    1,1,1,0,1, 1 ,1,0,0,1,1,

      0,    0,    0,   0,   0,   0
  },
  { //07
    1,1,0,1,1,1,1,0,1,1,1,1,
    1,0,0,1,1,0,0,0,0,1,1,0,
    0,0,0,0,0,1,1,0,0,1,1,0,
    1,1,0,1,1, 1 ,0,0,1,1,0,

      0,    0,    0,   0,   0,   0
  },
};

uint32_t p_timer = 0;
uint8_t c_frame = 0;

static bool pixelanim(effect_params_t* params) {
  if (p_timer > g_rgb_timer) {
    return false;
  }

//  HSV hsv  = rgb_matrix_config.hsv;
//  RGB rgb = hsv_to_rgb(hsv);
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (int j = led_min; j < led_max; j++) {
      if (faceArray[c_frame][j]) {
          rgb_matrix_set_color(j, 255, 0, 0);
      } else {
          rgb_matrix_set_color(j, 0x00, 0x00, 0x00);
      }
  }

  if (led_max == DRIVER_LED_TOTAL) {
    p_timer = g_rgb_timer + 200;
    c_frame = c_frame == 7 ? 0 : c_frame + 1;
    dprintf("c_frame = %d\n", c_frame);
  }

  return led_max < DRIVER_LED_TOTAL;
}

//==============================================================================================

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
