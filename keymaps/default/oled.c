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


//Sets up what the OLED screens display.

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("Qwrt"), false);
            break;
        default:
            oled_write_P(PSTR("Mod\n"), false);
            break;
    }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case 1:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

/* Brief boot splash: show the display for OLED_BOOT_SPLASH_MS after power-on
 * so the user can confirm the keyboard booted, then revert to normal
 * burn-in-prevention mode (off on default layer). */
#ifndef OLED_BOOT_SPLASH_MS
#    define OLED_BOOT_SPLASH_MS 3000   /* 3 seconds */
#endif

/* Anti-burn-in: toggle between normal and inverted display every
 * OLED_INVERT_INTERVAL ms so all pixels age equally (~50/50 duty). */
#ifndef OLED_INVERT_INTERVAL
#    define OLED_INVERT_INTERVAL 1000   /* 1 second */
#endif

static bool     oled_inverted_state  = false;
static uint32_t oled_invert_timer    = 0;
static uint32_t oled_boot_timer      = 0;
static bool     oled_boot_timer_init = false;
static bool     oled_splash_ended    = false;

/* The driver's rotation state — we temporarily override it during splash so
 * the landscape logo renders correctly on the master (normally ROTATION_270). */
extern oled_rotation_t oled_rotation;
extern uint8_t         oled_rotation_width;

static void set_oled_rotation(oled_rotation_t rot) {
    oled_rotation = rot;
    if (rot == OLED_ROTATION_0 || rot == OLED_ROTATION_180) {
        oled_rotation_width = OLED_DISPLAY_WIDTH;
    } else {
        oled_rotation_width = OLED_DISPLAY_HEIGHT;
    }
}

bool oled_task_user(void) {
    /* Lazy-init the boot timer on first call (timer_read32() is 0 at
     * static-init time on some platforms). */
    if (!oled_boot_timer_init) {
        oled_boot_timer      = timer_read32();
        oled_boot_timer_init = true;
        /* Force master into landscape for the splash logo. */
        if (is_keyboard_master()) {
            set_oled_rotation(OLED_ROTATION_0);
        }
    }

    bool     in_splash = timer_elapsed32(oled_boot_timer) < OLED_BOOT_SPLASH_MS;
    uint8_t  layer     = get_highest_layer(layer_state);

    /* Transition: splash just ended on master — restore the narrow rotation
     * and clear the buffer so the old landscape content doesn't linger. */
    if (!in_splash && !oled_splash_ended && is_keyboard_master()) {
        oled_splash_ended = true;
        set_oled_rotation(OLED_ROTATION_270);
        oled_clear();
    }

    if (is_keyboard_master()) {
        /* Master decides OLED power based on layer state.
         * OLED_MANUAL_POWER prevents the driver from auto-turning on
         * the display; SPLIT_OLED_ENABLE syncs this to the slave. */
        if (layer == 0 && !in_splash) {
            oled_off();
            return false;
        }
        oled_on();
    } else {
        /* Slave: SPLIT_OLED_ENABLE syncs the master's oled_on/oled_off
         * state via the split transport.  Do NOT call oled_on()/oled_off()
         * here — that would race with the synced state and keep the
         * slave display on after the master turned it off. */
        if (!is_oled_on()) {
            return false;
        }
    }

    if (in_splash) {
        /* During boot splash, show logo on both halves. */
        render_logo();
    } else if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }

    /* Periodically flip the display polarity to equalise pixel wear. */
    if (timer_elapsed32(oled_invert_timer) >= OLED_INVERT_INTERVAL) {
        oled_invert_timer   = timer_read32();
        oled_inverted_state = !oled_inverted_state;
        oled_invert(oled_inverted_state);
    }

    return false;
}

#endif
