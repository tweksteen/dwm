#!/bin/bash

sep(){
  echo -e "\x01\u276c\x01"
}

intf(){
  eth0=$(ip -o -4 a | awk '/eth0|wlan0/{s=s (s?" ":"") $4} END {printf "%s", s}')
  echo -e "$eth0"
}

mem(){
  mem="$(awk '/^-/ {print $3}' <(free -m))"
  echo -e "$mem""M"
}

temperature(){
  t="$(cat /sys/class/thermal/thermal_zone0/temp)"
  
}

cpu(){
  read lavg rest < /proc/loadavg
  lavg=$(echo $lavg | tr -d .) 
  echo $lavg > /dev/stderr
  cpu=$(( lavg / 4 ))
  echo -e "$cpu%"
}

cin(){
  echo -e "$(netstat -lutw | tail -n +3 | wc -l)"
}

bat(){
  ac="$(awk 'NR==1 {print +$4}' <(acpi -V))"
  onl="$(grep "on-line" <(acpi -V))"

  if [ -z "$onl" ] && [ "$ac" -gt "15" ]; then
    echo -e "\x04$ac%\x01"
  elif [ -z "$onl" ] && [ "$ac" -le "15" ]; then
    echo -e "\x03\u2047 $ac%\x01"
  else
    echo -e "\x01\u03a6\x01"
  fi
}

dte(){
  dte="$(date "+%H:%M %d-%m-%Y")"
  echo -e "$dte"
}

xsetroot -name "$(cpu) $(sep) $(mem) $(sep) $(intf) $(sep) $(bat) $(sep) $(dte) "
