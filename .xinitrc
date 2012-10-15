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

# exec gnome-session
# exec startkde
if [ "$HOSTNAME" == "trinity" ]
then
    xsetroot -cursor_name left_ptr
    setxkbmap -layout de-latin1-nodeadkeys.map.gz
    /usr/bin/xscreensaver -no-splash &
    xrdb -merge ~/.Xresources
    #nitrogen --restore
    [ -f ~/.xprofile ] && . ~/.xprofile
    exec ck-launch-session dbus-launch xmonad
    #exec ck-launch-session dbus-launch --exit-with-session startxfce4
elif [ "$HOSTNAME" == "morpheus" ]
then
    exec startxfce4
fi

# ...or the Window Manager of your choice
