#!/bin/sh
#
# ~/.xinitrc
#
# Executed by startx (run your window manager from here)

if [ -d /etc/X11/xinit/xinitrc.d ]; then
  for f in /etc/X11/xinit/xinitrc.d/*; do
    [ -x "$f" ] && . "$f"
  done
  unset f
fi

# exec gnome-session
# exec startkde
# exec ck-launch-session dbus-launch startxfce4
xsetroot -cursor_name left_ptr
setxkbmap -layout de
/usr/bin/xscreensaver -no-splash &
xrdb -merge ~/.Xresources
exec ck-launch-session dbus-launch xmonad
# ...or the Window Manager of your choice
