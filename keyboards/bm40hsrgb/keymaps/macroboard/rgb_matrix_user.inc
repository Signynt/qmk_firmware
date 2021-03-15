
RGB_MATRIX_EFFECT(TEST_ANIM)
RGB_MATRIX_EFFECT(MUSIC_ANIM)
RGB_MATRIX_EFFECT(BRIGHT_ANIM)
RGB_MATRIX_EFFECT(NUM_ANIM)
RGB_MATRIX_EFFECT(FRACTAL)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

//==============================================================================================

//TEST_ANIM

static bool TEST_ANIM(effect_params_t* params) {

  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  float wLEDs[54] = {
    1,1,1,1,0,1,1,1,1,0,1,1,
    0,1,1,0,0,1,1,1,0,0,1,1,
    0,1,1,0,0,1,0,0,0,0,0,0,
    0,1,1,0,0, 1 ,1,1,0,1,1,

      0,    0,    0,   0,   0,   0
  };

  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
  }
  for (uint16_t i = led_min; i < led_max; i++) {
    if (wLEDs[i] == 1 ){
      rgb_matrix_set_color(i, 0xff, 0xff, 0xff);
    }
  }
  return led_max < DRIVER_LED_TOTAL;
}

//==============================================================================================

// MUSIC_ANIM

int musicArray[6][54] = {

  { //00
    0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,0,0,0,0,1,1,0,0,0,0,
    1,1,1,0,0,1,1,1,1,0,0,1,
    1,1,1,1,1, 1 ,1,1,1,1,1,

      0,    0,    0,   0,   0,   0
  },
  { //01
    0,0,0,0,0,0,0,0,0,0,0,0,
    1,0,0,0,0,1,1,0,0,0,0,1,
    1,1,0,0,1,1,1,1,0,0,1,1,
    1,1,1,1,1, 1 ,1,1,1,1,1,

      0,    0,    0,   0,   0,   0
  },
  { //02
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,1,1,0,0,0,0,1,1,
    1,0,0,1,1,1,1,0,0,1,1,1,
    1,1,1,1,1, 1 ,1,1,1,1,1,

      0,    0,    0,   0,   0,   0
  },
  { //03
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,1,1,0,0,0,0,1,1,0,
    0,0,1,1,1,1,0,0,1,1,1,1,
    1,1,1,1,1, 1 ,1,1,1,1,1,

      0,    0,    0,   0,   0,   0
  },
  { //04
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,1,1,0,0,0,0,1,1,0,0,
    0,1,1,1,1,0,0,1,1,1,1,0,
    1,1,1,1,1, 1 ,1,1,1,1,1,

      0,    0,    0,   0,   0,   0
  },
  { //05
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,1,1,0,0,0,0,1,1,0,0,0,
    1,1,1,1,0,0,1,1,1,1,0,0,
    1,1,1,1,1, 1 ,1,1,1,1,1,

      0,    0,    0,   0,   0,   0
  },
};

uint32_t p2_timer = 0;
uint8_t c2_frame = 0;

static bool MUSIC_ANIM(effect_params_t* params) {
  if (p2_timer > g_rgb_timer) {
    return false;
  }

//  HSV hsv  = rgb_matrix_config.hsv;
//  RGB rgb = hsv_to_rgb(hsv);
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (int k = led_min; k < led_max; k++) {
      if (musicArray[c2_frame][k]) {
          rgb_matrix_set_color(k, 70, 70, 100);
      } else {
          rgb_matrix_set_color(k, 0x00, 0x00, 0x00);
      }
  }

  if (led_max == DRIVER_LED_TOTAL) {
    p2_timer = g_rgb_timer + 200;
    c2_frame = c2_frame == 5 ? 0 : c2_frame + 1;
    dprintf("c2_frame = %d\n", c2_frame);
  }

  return led_max < DRIVER_LED_TOTAL;
}

//==============================================================================================

//BRIGHT EFFECT

static bool BRIGHT_ANIM(effect_params_t* params) {

  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  float wLEDs[54] = {
    0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
    0, 0, 0, 0, 0,  0  , 0, 1, 0, 0, 0,

      0,    0,    0,   0,   0,   0
  };

  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
  }
  for (uint16_t i = led_min; i < led_max; i++) {
    if (wLEDs[i] == 1 ){
      rgb_matrix_set_color(i, 0xff, 0xff, 0xff);
    }
  }
  return led_max < DRIVER_LED_TOTAL;
}

//==============================================================================================

//FRACTAL effect

uint32_t f_timer = 0;

uint8_t halfArray[6][4];
uint8_t fullArray[12][4];

uint8_t halfbottom[3];
uint8_t fullbottom[6];
uint8_t displArray[54];

bool testArray1[11][4] = {
  {1,1,1,1},
  {0,1,0,1,},
  {1,1,1,1,},
  {0,0,0,0,},
  {1,1,1,1,},
  {1,0,1,0,},
  {1,1,1,0,},
  {0,0,0,0,},
  {1,1,1,1,},
  {1,0,0,1,},
  {1,0,0,1,},
}
};

static bool FRACTAL(effect_params_t* params) {
  uint16_t f_speed = (400 / rgb_matrix_config.speed) * 127;

  if (f_timer > g_rgb_timer) {
    return false;
  }

  if (params->init) {
    srand(g_rgb_timer);
  }

  HSV hsv  = rgb_matrix_config.hsv;
  RGB rgb = hsv_to_rgb(hsv);
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (int j = led_min; j < led_max; j++) {
      int i = j > 41 ? j + 1 : j;
      if (displArray[i]) {
          rgb_matrix_set_color(j, rgb.r, rgb.g, rgb.b);
      } else {
          rgb_matrix_set_color(j, 0x00, 0x00, 0x00);
      }
  }

  if (led_max == DRIVER_LED_TOTAL) {
    f_timer = g_rgb_timer + f_speed;

    // move columns
    for (uint8_t col = 5; col > 0; col--) {
        for (uint8_t row = 0; row < 4; row++) {
            halfArray[col][row] = halfArray[col-1][row];
        }
    }
    //bottom
    for (uint8_t col = 2; col > 0; col--) {
        halfbottom[col] = halfbottom[col-1];
    }



    // random fill first column
  for (uint8_t col = 0; col < 2; col++) {
    for (uint8_t row = 0; row < 4; row++) {
      halfArray[0][row] = testArray1[col+1][row];
    }
    for (uint8_t row = 1; row < 4; row++) {
      halfArray[0][row] = testArray1[col-1][row];
    }
    for (uint8_t row = 2; row < 4; row++) {
      halfArray[0][row] = testArray1[col][row];
    }
    for (uint8_t row = 3; row < 4; row++) {
      halfArray[0][row] = testArray1[col][row];
    }
  }
    // bottom
//    halfbottom[0] = 1;




    // transfer to big array
    for (uint8_t col = 0; col < 6; col++) {
        for (uint8_t row = 0; row < 4; row++){
            fullArray[5 - col][row] = halfArray[col][row];
            fullArray[6 + col][row] = halfArray[col][row];
        }
    }
    //bottom
    for (uint8_t col = 0; col < 3; col++){
      fullbottom[2 - col] = halfbottom[col];
      fullbottom[3 + col] = halfbottom[col];
    }



    // transfer to matrix array
    uint8_t k = 0;
    for (uint8_t row = 0; row < 4; row++) {
        for (uint8_t col = 0; col < 12; col++) {
              displArray[k] = fullArray[col][row];
              k++;
        }
    }
    //bottom
    uint8_t l = 48;
    for (uint8_t col = 0; col < 6; col++) {
        displArray[l] = fullbottom[col];
        l++;
    }
  }

  return led_max < DRIVER_LED_TOTAL;
}

//==============================================================================================

bool NUM_ANIM(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, 0, 0, 0);
    }
    return led_max < DRIVER_LED_TOTAL;
}

//==============================================================================================

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
