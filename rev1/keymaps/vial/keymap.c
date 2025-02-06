/* Copyright 2020 Josef Adamcik
 * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
 * Modification for Vial support by Drew Petersen
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

// clang-format off

#include QMK_KEYBOARD_H
#include "oled.c"

// Default keymap. This can be changed in Vial. Use oled.c to change behavior that Vial cannot change.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,------------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Bspc  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+-------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Del   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+-------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  | '     |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+-------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  | RShift|
 * `-----------------------------------------/       /     \      \------------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Space  /       \Enter \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[0] = LAYOUT(
  KC_GRV,     KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_BSPC,
  KC_ESC,     KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   KC_DEL,
  KC_TAB,     KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_QUOT,
  KC_LSFT,    KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                     KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
              KC_MUTE, KC_LGUI,KC_LALT,KC_LCTL, MO(1), KC_SPC,       KC_ENT,  MO(2), KC_RCTL, KC_RALT, KC_RGUI,
                                                                    KC_UP, KC_LEFT, KC_ENTER, KC_RIGHT, KC_DOWN
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  |      |      |  Up  |      |      |                    |      |      |      |      |      | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps |      | Left | Down | Right|      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | Shift|  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |      |      |   \  | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Space  /       \Enter \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[1] = LAYOUT(
  XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  _______, XXXXXXX, XXXXXXX,   KC_UP, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_F12,
  KC_CAPS, XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT,XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  _______,  KC_EQL, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR,                    KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX, KC_BSLS, _______,
            KC_MUTE, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______,
                                                                    KC_UP, KC_LEFT, KC_ENTER, KC_RIGHT, KC_DOWN
),
/* RAISE
 * ,----------------------------------------.                     ,------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+-------|
 * | Esc  | Ins  | Pscr | Menu |      |      |                    | PgUp | Home |  Up  | End  |      | F12   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+-------|
 * | Tab  |      |      |      |      |      |-------.    ,-------|PgDown| Left | Down | Right|  Del | Enter |
 * |------+------+------+------+------+------|  MUTE  |    |      |------+------+------+------+------+-------|
 * |Shift | Undo |  Cut | Copy | Paste|      |-------|    |-------| Del  |      |      |      |   \  | Shift |
 * `-----------------------------------------/       /     \      \------------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Space  /       \Enter \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[2] = LAYOUT(
  XXXXXXX,   KC_F1,    KC_F2,    KC_F3,    KC_F4,   KC_F5,                     KC_F6,    KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,
  _______,  KC_INS,  KC_PSCR,   KC_APP,  XXXXXXX, XXXXXXX,                   KC_PGUP,  KC_HOME,  KC_UP,   KC_END,   XXXXXXX,  KC_F12,
  _______, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,                   KC_PGDN,  KC_LEFT, KC_DOWN, KC_RGHT,   XXXXXXX, XXXXXXX,
  _______, KC_UNDO,   KC_CUT,  KC_COPY, KC_PASTE, XXXXXXX,                   XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,  KC_SLSH, _______,
           KC_MUTE,  _______,  _______,  _______, _______, _______,       _______, _______, _______, _______, _______,
                                                                    KC_UP, KC_LEFT, KC_ENTER, KC_RIGHT, KC_DOWN
)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(_______, _______) },
    [1] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(_______, _______) },
    [2] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
};
#endif
