OLED_ENABLE = yes
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
RGB_MATRIX_ENABLE = no     # Disable keyboard RGB matrix, as it is enabled by default on rev3
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
WPM_ENABLE = yes
MOUSEKEY_ENABLE = yes

BOOTLOADER = caterina

# Per-key debounce: registers presses immediately, but only releases a key after
# it has been stable for DEBOUNCE ms. This stops release chatter from producing
# double presses without adding input latency.
DEBOUNCE_TYPE = asym_eager_defer_pk
