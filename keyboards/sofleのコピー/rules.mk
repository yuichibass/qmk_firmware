MCU = atmega32u4
BOOTLOADER = caterina
SPLIT_KEYBOARD = yes
DEFAULT_FOLDER = sofle/rev1
SWAP_HANDS_ENABLE = no

OLED_DRIVER_ENABLE = no

UNICODE_ENABLE = yes

SRC +=    naginata_v13.c

EXTRAFLAGS += -flto