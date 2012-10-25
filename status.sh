#!/bin/bash

sep(){
  echo -e "\u276c"
}

intf(){
  p1p1=$(ip -o -4 a | awk '/p1p1|wlan0|wlan1|ppp0/{s=s (s?" ":"") $4} END {printf "%s", s}')
  echo -e "$p1p1$wlan0"
}

mem(){
  mem="$(awk '/^-/ {print $3}' <(free -m))"
  echo -e "$mem""M"
}

cpu(){
  read cpu a b c previdle rest < /proc/stat
  prevtotal=$((a+b+c+previdle))
  sleep 0.5
  read cpu a b c idle rest < /proc/stat
  total=$((a+b+c+idle))
  cpu="$((100*( (total-prevtotal) - (idle-previdle) ) / (total-prevtotal) ))"
  echo -e "$cpu%"
}

cin(){
  echo -e "$(netstat -lutw | tail -n +3 | wc -l)"
}

bat(){
  ac="$(awk 'NR==1 {print +$4}' <(acpi -V))"
  onl="$(grep "on-line" <(acpi -V))"

  if [ -z "$onl" ] && [ "$ac" -gt "15" ]; then
    echo -e "$ac%"
  elif [ -z "$onl" ] && [ "$ac" -le "15" ]; then
    echo -e "\u2047 $ac%"
  else
    echo -e "\u03a6"
  fi
}

dte(){
  dte="$(date "+%H:%M %d-%m-%Y")"
  echo -e "$dte"
}

xsetroot -name "$(cpu) $(sep) $(mem) $(sep) $(intf) $(sep) $(bat) $(sep) $(dte)"
