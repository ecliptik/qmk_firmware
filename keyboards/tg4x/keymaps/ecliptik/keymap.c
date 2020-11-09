/* Copyright 2018 u/mythosmann
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#define BASE 0 // default layer
#define SYMB 1 // symbols
#define NUMB 2 // numbers/motion

enum custom_keycodes {             // Make sure have the awesome keycode ready
  SCR_SHOT,
  REC_VID,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {               // This will do most of the grunt work with the keycodes.
    case SCR_SHOT:
      if (record->event.pressed) {
         SEND_STRING(SS_LGUI(SS_LSFT("4")));
      }
      break;
     case REC_VID:
      if (record->event.pressed) {
         SEND_STRING(SS_LGUI(SS_LSFT("5")));
      }
      break;
  }
  return true;
}

// Combos
enum combos {
  SD,
  WE,
  DF,
  XC,
  CV,
  OP,
  UI,
  HJ,
  KL,
  IO,
  JK,
  NM,
  LQUOT,
  CDOT,
  MCOM
  };

const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM we_combo[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cv_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM op_combo[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM ui_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM hj_combo[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM io_combo[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM nm_combo[] = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM lquot_combo[] = {KC_L, KC_SCOLON, COMBO_END};
const uint16_t PROGMEM commdot_combo[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM mcomm_combo[] = {KC_M, KC_COMM, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [SD] = COMBO(sd_combo, KC_BSPC),
  [WE] = COMBO(we_combo, KC_ESC),
  [DF] = COMBO(df_combo, KC_TAB),
  [XC] = COMBO(xc_combo, KC_MINS),
  [CV] = COMBO(cv_combo, KC_UNDERSCORE),
  [OP] = COMBO(op_combo, KC_QUOTE),
  [UI] = COMBO(ui_combo, KC_GRV),
  [HJ] = COMBO(hj_combo, KC_LT),
  [KL] = COMBO(kl_combo, KC_PIPE),
  [IO] = COMBO(io_combo, KC_DOUBLE_QUOTE),
  [JK] = COMBO(jk_combo, KC_COLON),
  [NM] = COMBO(nm_combo, KC_QUESTION),
  [LQUOT] = COMBO(lquot_combo, KC_GT),
  [CDOT] = COMBO(commdot_combo, KC_SLASH),
  [MCOM] = COMBO(mcomm_combo, KC_BSLASH)
};

//Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
,-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.
|  `  |   q   |   w   |   e   |   r   |   t   |   y   |   u   |   i   |   o   |   p   | KC_SLSH | Bspc  |
|-------'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-------|
|  ESC    |   a   |   s   |   d   |   f   |   g   |   h   |   j   |   k   |   l   |   ;   |    Enter    |
|---------'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----------|
|  Shift     |   z   |   x   |   c   |   v   |   b   |   n   |   m   |   ,   |   .   |           Shift  |
|---------,--'------,'-------',------'-------'-------'-------'-------',------'--,----'--,----'--,-------|
|   Ctl   |   Alt   |   Com   |   Fn                 |   Spc          | Com     | Alt  |  FN   | RCtl  |
`---------'---------'---------'----------------------'----------------'---------'-------'-------'-------'*/
  [BASE] = LAYOUT_SPLIT_ANSI( /* Base */
//,-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.
   KC_GRV, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_SLSH, KC_BSPC, \
//|-------'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-------------|
   KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_ENT, \
//|---------'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'-----,-'-------------|
   KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, \
//|---------,--'------,'-------',------'-------'-------',------'-------',------'--,----'--,----'--,-------|
   KC_LCTL, KC_LALT , KC_LGUI  ,LT(SYMB,KC_ENT)    ,LT(NUMB, KC_SPC), TT(NUMB) ,KC_RALT,KC_RGUI,KC_RCTL  \
//`---------'---------'----------'-------------------'----------------'---------'-------'--------'--------'
),
/*
,-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.
|       |   !   |   @   |   {   |   }   |   &   |   `   |   ~   |   "   |   /   |   \   |   -   |       |
|-------'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-------|
|        | #    | $     |   (   |   )   |   *   |   +   |   -   |   /   |   *   |   '   |     |         |
|---------'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----------|
|          |  %  |   ^  |   [    |  ]    |   PIPE    |   &   |   =   |   <   |   >   |       |          |
|---------,--'------,'-------',------'-------'-------'-------'-------'-------',------'--,----'--,-------|
|       |      |      |                   |                |        |      |        |       |
`---------'---------'---------'-----------------------------------------------'---------'-------'-------'*/
  [SYMB] = LAYOUT_SPLIT_ANSI( /* SYMB */
//,-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.
   KC_TRNS, KC_EXLM, KC_AT, KC_LCBR , KC_RCBR, KC_AMPR, KC_GRV, KC_TILD, KC_DOUBLE_QUOTE, KC_SLASH, KC_BSLS, KC_TRNS, \
//|-------'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-------------|
   KC_TRNS, KC_TRNS,  KC_HASH, KC_DLR, KC_LPRN, KC_RPRN, KC_ASTR, KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_QUOT, KC_TRNS, \
//|---------'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----------|
   KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_PIPE, KC_AMPR, KC_EQL, KC_LABK, KC_RABK, KC_TRNS, KC_TRNS, \
//|---------,--'------,'-------',------'-------'-------',------'-------',------'--,----'--,----'--,-------|
   KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS  \
//`---------'---------'---------'-----------------------'---------------'---------'-------'-------'-------'
),
/*
,-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.
|       |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0  |              |
|-------'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-------|
|        |  F1  |  F2  |  F3  |  F4  |  F5  |  left  |  down  |  up  |  right   |  END  |      Enter    |
|---------'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----------|
|          |  F6   |  F7   |  F8  |   F9  |  F10  |   HOME  |  PGDN  |  PGUP  |  END   |        |
|---------,--'------,'-------',------'-------'-------'-------'-------'-------',------'--,----'--,-------|
|         |         |         |                      |              |  BASE  |        |        |        |
`---------'---------'---------'----------------------------------------------'--------'------- '---------'*/
  [NUMB] = LAYOUT_SPLIT_ANSI( /* Number */
//,-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.-------.
   KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, KC_TRNS, \
//|-------'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-----'-,-------------|
   KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_END, KC_TRNS, \
//|---------'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----'--,----------|
   KC_TRNS, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_HOME, KC_PGDOWN, KC_PGUP, KC_END, KC_TRNS, KC_TRNS, \
//|---------,--'------,'-------',------'-------'-------',------'-------',------'--,----'--,----'--,-------|
   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TO(BASE), KC_TRNS, KC_TRNS, KC_TRNS \
//`---------'---------'---------'-----------------------'---------------'---------'-------'-------'-------'
)
};

void update_led(void) {
  rgblight_sethsv_at(0,0,0, 0);
  switch (biton32(layer_state)) { //same code as above
    case BASE:
      rgblight_sethsv_at(HSV_TEAL, 1);
      rgblight_sethsv_at(HSV_MAGENTA, 2);
      rgblight_sethsv_at(HSV_TEAL, 3);
      rgblight_sethsv_at(HSV_MAGENTA, 4);
      rgblight_sethsv_at(HSV_TEAL, 5);
      rgblight_sethsv_at(HSV_MAGENTA, 6);
      break;
    case SYMB:
      rgblight_sethsv_range(HSV_BLUE,1,7);
      break;
    case NUMB:
      rgblight_sethsv_range(HSV_GREEN,1,7);
      break;
    default:
      rgblight_sethsv_at(HSV_TEAL, 1);
      rgblight_sethsv_at(HSV_MAGENTA, 2);
      rgblight_sethsv_at(HSV_TEAL, 3);
      rgblight_sethsv_at(HSV_MAGENTA, 4);
      rgblight_sethsv_at(HSV_TEAL, 5);
      rgblight_sethsv_at(HSV_MAGENTA, 6);
      break;
  }
}

void led_set_user(uint8_t usb_led) {
  update_led();
}

uint32_t layer_state_set_user(uint32_t state) {
  update_led();
  return state;
}
