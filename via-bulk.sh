#!/bin/sh
set -e
set -x

for tapping_term in `seq 1 500`
do
  keymap=via-default-$tapping_term
  keymap_path=./keyboards/claw44/keymaps/$keymap
  echo $keymap

  cp -pr ./keyboards/claw44/keymaps/via-default-template $keymap_path
  sed -i -e "s/XXX/$tapping_term/" $keymap_path/config.h
  make claw44:$keymap

  echo "#define IGNORE_MOD_TAP_INTERRUPT" >> $keymap_path/config.h
  imti_keymap=via-default-imti-$tapping_term
  imti_keymap_path=./keyboards/claw44/keymaps/$imti_keymap
  cp -pr $keymap_path $imti_keymap_path
  make claw44:$imti_keymap

  rm -rf $keymap_path
  rm -rf $imti_keymap_path
done

for tapping_term in `seq 1 500`
do
  keymap=via-oled-$tapping_term
  keymap_path=./keyboards/claw44/keymaps/$keymap
  echo $keymap

  cp -pr ./keyboards/claw44/keymaps/via-oled-template $keymap_path
  sed -i -e "s/XXX/$tapping_term/" $keymap_path/config.h
  make claw44:$keymap

  echo "#define IGNORE_MOD_TAP_INTERRUPT" >> $keymap_path/config.h
  imti_keymap=via-oled-imti-$tapping_term
  imti_keymap_path=./keyboards/claw44/keymaps/$imti_keymap
  cp -pr $keymap_path $imti_keymap_path
  make claw44:$imti_keymap

  rm -rf $keymap_path
  rm -rf $imti_keymap_path
done
