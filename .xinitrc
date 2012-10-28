#!/bin/sh
#
# ~/.xinitrc
#
# Executed by startx (run your window manager from here)
HOSTNAME=$(hostname)

if [ -d /etc/X11/xinit/xinitrc.d ]; then
  for f in /etc/X11/xinit/xinitrc.d/*; do
    [ -x "$f" ] && . "$f"
  done
  unset f
fi

case $1 in
xmonad)
    xsetroot -cursor_name left_ptr
    setxkbmap -layout de-latin1-nodeadkeys.map.gz
    #/usr/bin/xscreensaver -no-splash &
    xrdb -merge ~/.Xresources
    #nitrogen --restore
    [ -f ~/.xprofile ] && . ~/.xprofile
    exec dbus-launch xmonad
    #exec ck-launch-session dbus-launch --exit-with-session startxfce4
    ;;
xfce4)
    exec startxfce4
    ;;
esac
