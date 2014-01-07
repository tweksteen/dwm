#!/bin/env ruby

def sep
  "\x01\u276c\x01"
end

def capslock
  prop = `xset -q`
  if prop =~ /Caps Lock:\s+on/
    "\u21e7"
  else
    "-"
  end
end

def intf
  ifaces = `ip -o -4 a`
  addresses = []
  for iface in ifaces.lines
    if iface =~ /eth0|wlan0|tun0/
      n, name, type, address, _ = iface.split
      addresses.push address
    end
  end
  unless addresses.empty?
    addresses.join " "
  else
    "-"
  end
end

def snd
  v = `amixer get Master`
  if v.include? "off"
    "mute"
  else
    /([0-9.-]+dB)/.match(v).captures.first
  end
end

def temperature
  t = open('/sys/class/thermal/thermal_zone0/temp').read.to_f
  dt = t / 1000
  if dt > 50
    "\x03" + dt.to_s + "\u00b0\x01"
  else
    dt.to_s + "\u00b0"
  end
end

def cpu
  lavg = open('/proc/loadavg').read.split.first.to_f
  if lavg > 2
    if lavg > 4
      "\x03" + lavg.to_s + "\x01"
    else
      "\x04" + lavg.to_s + "\x01"
    end
  else
    lavg.to_s 
  end 
end

def mem
  memt = `free -m`
  return memt.lines[2].split()[2] + "M"
end

def bat
  b = `acpi -V`
  p = (/, ([0-9]*)\%/.match b).captures.first.to_i
  online = true if b =~ /on-line/
  if not online
    if p > 15
      "\x04#{p}%\x01"
    else
      "\x03\u2047 #{p}%\x01"
    end
  else
    "\x01\u03a6\x01"
  end   
end

def date
  Time.now.strftime "%H:%M %d-%m-%Y"
end

`xsetroot -name "#{capslock} #{sep} #{snd} #{sep} #{cpu} #{sep} #{mem} #{sep} #{temperature} #{sep} #{intf} #{sep} #{bat} #{sep} #{date} "`
