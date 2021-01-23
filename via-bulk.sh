#!/bin/sh
set -e
set -x

for tapping_term in `seq -f %03g 1 500`
do
  keymap=via-default-$tapping_term
  keymap_path=./keyboards/claw44/keymaps/$keymap
  echo $keymap

  cp -pr ./keyboards/claw44/keymaps/via-default-template $keymap_path
  sed -i -e "s/XXX/$tapping_term/" $keymap_path/config.h
  make claw44:$keymap

  echo "#define IGNORE_MOD_TAP_INTERRUPT" >> $keymap_path/config.h
  cp -pr $keymap_path imti-$keymap_path
  make claw44:imti-$keymap

  rm -rf $keymap_path
  rm -rf imti-$keymap_path
done
