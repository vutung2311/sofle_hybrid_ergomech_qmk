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

#pragma once

// Vial Support
#define VIAL_KEYBOARD_UID { 0x05, 0xCD, 0x9F, 0x8A, 0xF4, 0xDF, 0xDE, 0xB2 }

// The four corners
#define VIAL_UNLOCK_COMBO_ROWS { 0, 6, 3, 9 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 0, 0, 0 }

#define USB_POLLING_INTERVAL_MS 1
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2000
#define SPLIT_USB_TIMEOUT_POLL 10
#define SPLIT_WATCHDOG_ENABLE
#define SPLIT_WATCHDOG_TIMEOUT 3000
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_OLED_ENABLE
#define FORCE_NKRO

/* RP2040 GPIO settles much faster than AVR — reduce from default 30µs */
#define MATRIX_IO_DELAY 10

/* Lower debounce for snappier key registration (default 5ms) */
#define DEBOUNCE 3

/* Detent-position-based encoder triggering: fire exactly one event when
 * the roller settles into its resting state (both pins HIGH via pull-ups
 * = 0b11).  This makes pulse counting robust against contact bounce and
 * variable transition counts — the LUT's +1/−1 oscillations cancel, and
 * only the net direction matters when the detent is reached. */
#define ENCODER_DEFAULT_POS 0b11

/* OLED content (layer/caps) changes infrequently — reduce split traffic */
#define OLED_UPDATE_INTERVAL 100

/* 70% brightness (178/255) to slow OLED pixel degradation */
#define OLED_BRIGHTNESS 178

/* We control oled_on/oled_off based on layer state — prevent the
 * driver from auto-turning on the display in oled_render_dirty(). */
#define OLED_MANUAL_POWER
#define OLED_TIMEOUT 0

/* Run OLED on RP2040 Core 1 (SMP) — frees Core 0 scan loop from I2C */
#define RP2040_SMP_OLED_CORE1
