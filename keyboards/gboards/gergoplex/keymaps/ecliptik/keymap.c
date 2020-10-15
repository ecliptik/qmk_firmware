/* Good on you for modifying your layout! if you don't have
 * time to read the QMK docs, a list of keycodes can be found at
 *
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * There's also a template for adding new layers at the bottom of this file!
 */

#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define NUMB 2 // numbers/motion
#define NAV  3 // nav/motion

// Tap Dance

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

// Define a type for as many tap dance states as you need
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP
};

enum {
    NAV_LAYR, // Our custom tap dance key; add any other tap dance keys to this enum
};

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
uint8_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);

// Super alt tab
bool is_alt_tab_active = false;    // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;        // we will be using them soon.

enum custom_keycodes {             // Make sure have the awesome keycode ready
  ALT_TAB = SAFE_RANGE,
  SCR_SHOT,
  REC_VID,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {               // This will do most of the grunt work with the keycodes.
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LGUI);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;

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

void matrix_scan_user(void) {     // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LGUI);
      is_alt_tab_active = false;
    }
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,-----------------------------.       ,--------------------------------.
 * |    Q |  W  |  E  |  R  |  T  |      |  Y  |  U  |  I  |  O  |    P   |
 * |-----+-----+-----+-----+------|      |--------------------------------|
 * |CTRL/A|  S  |  D  |  F  |  G  |      |  H  |  J  |  K  |  L  | CTRL/; |
 * |-----+-----+-----+-----+------|      |--------------------------------|
 * |SHFT/Z|  X  |  C  |  V  |  B  |      |  N  |  M  |  ,  |  .  | SHFT/? |
 * `------+-----+-----+------+----'      `--------------------------------'
 *  .-------------------------.           .-----------------.
 *  |ESC/META|ENT/ALT|SPC(SYM)|           |SPC(NUM)|LSFT|TAB|
 *  '-------------------------'           '-----------------'
 */
[BASE] = LAYOUT_gergoplex(
    KC_Q,               KC_W, KC_E, KC_R, KC_T,    KC_Y, KC_U, KC_I,    KC_O,   KC_P,
    MT(MOD_LCTL, KC_A), KC_S, KC_D, KC_F, KC_G,    KC_H, KC_J, KC_K,    KC_L,   MT(MOD_LCTL, KC_SCLN),
    MT(MOD_LSFT, KC_Z), KC_X, KC_C, KC_V, KC_B,    KC_N, KC_M, KC_COMM, KC_DOT, MT(MOD_RSFT, KC_SLSH),

    MT(MOD_LGUI, KC_ESC), MT(MOD_LALT, KC_ENT), LT(SYMB, KC_SPC), // Left
    LT(NUMB, KC_SPC), KC_RSFT, TD(NAV_LAYR) // Right
    ),

/* Keymap 1: Symbols layer
 * ,-----------------------------.       ,-----------------------------.
 * |  !   |  @  |  {  |  }  |  &  |      |  `  |  ~  |  "  |     |  \  |
 * |-----+-----+-----+-----+------|      |-----------------------------|
 * |  #   |  $  |  (  |  )  |  *  |      |  +  |  -  |  /  |  *  |  '  |
 * |-----+-----+-----+-----+------|      |-----------------------------|
 * |  %   |  ^  |  [  |  ]  |  |  |      |  &  |  =  |  ,  |  .  |  -  |
 * `------+-----+-----+------+----'      `-----------------------------'
 *      .-----------------.                   .------------------.
 *      |    |  ;  |      |                   |  =  |  ;  |  DEL |
 *      '-----------------'                   '------------------'
 */
[SYMB] = LAYOUT_gergoplex(
    KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_AMPR,    KC_GRV,  KC_TILD, KC_DOUBLE_QUOTE,  KC_TRNS, KC_BSLS,
    KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_ASTR,    KC_PLUS, KC_MINS, KC_SLSH,          KC_ASTR, KC_QUOT,
    KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_PIPE,    KC_AMPR, KC_EQL,  KC_COMM,          KC_DOT,  KC_MINS,
      KC_TRNS, KC_SCLN, KC_TRNS,                      KC_EQL, KC_SCLN, KC_DEL
    ),

/* Keymap 2: Number/Function layer
 * ,-----------------------------.       ,-------------------------------.
 * |  1   |  2  |  3  |  4  |  5  |      |  6  |  7  |  8  |  9  |   0   |
 * |-----+-----+-----+-----+------|      |-------------------------------|
 * |  F1  | F2  | F3  | F4  |  F5 |      | LFT | DWN | UP  | RGT | VOLUP |
 * |-----+-----+-----+-----+------|      |-------------------------------|
 * |  F6  | F7  | F8  | F9  | F10 |      |   | PGDN | PGUP | MUTE| VOLDN |
 * `------+-----+-----+------+----'      `-------------------------------'
 *      .-----------------.                   .-----------------.
 *      | F11 | F12|      |                   |     | PLY | SKP |
 *      '-----------------'                   '-----------------'
 */
[NUMB] = LAYOUT_gergoplex(
    KC_1,  KC_2,  KC_3,  KC_4,  KC_5,      KC_6,    KC_7,      KC_8,    KC_9,    KC_0,
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,     KC_LEFT, KC_DOWN,   KC_UP,   KC_RGHT, KC_END,
    KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,    KC_HOME, KC_PGDOWN, KC_PGUP, KC_MUTE, KC_VOLD,
      KC_F11, KC_F12, KC_TRNS,               KC_TRNS, KC_MPLY, KC_MNXT
    ),

// Navigation layer to use for tap-dance
[NAV] = LAYOUT_gergoplex(
    KC_TRNS, KC_MS_UP,      KC_MS_UP,   KC_MS_BTN2,  KC_TRNS,      KC_TRNS, KC_PGDOWN, KC_PGUP, KC_TRNS, KC_TRNS,
    KC_MS_LEFT, KC_MS_LEFT, KC_MS_BTN1, KC_MS_RIGHT, KC_MS_RIGHT,  KC_LEFT, KC_DOWN,   KC_UP,   KC_RGHT, KC_TRNS,
    SCR_SHOT, KC_MS_DOWN,    KC_MS_DOWN, KC_MS_BTN2,  REC_VID,      KC_TRNS, KC_PGDOWN, KC_PGUP, KC_TRNS, KC_TRNS,
        ALT_TAB, KC_TRNS, KC_TRNS,                          KC_TRNS, KC_TRNS, TD(NAV_LAYR)
    )
};

;

// Tapdance

// Determine the current tap dance state
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) return DOUBLE_TAP;
    else return 8;
}

// Initialize tap structure associated with example tap dance key
static tap ql_tap_state = {
    .is_press_action = true,
    .state = 0
};

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case SINGLE_TAP:
            tap_code(KC_TRNS);
            break;
        case SINGLE_HOLD:
            tap_code(KC_TRNS);
            break;
        case DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(NAV)) {
                // If already set, then switch it off
                layer_move(BASE);
            } else {
                // If not already set, then switch the layer on
              layer_on(NAV);
          }
            break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == SINGLE_HOLD) {
        layer_move(BASE);
    }
    ql_tap_state.state = 0;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [NAV_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 200)
};
