# toggledhcp
## config.h
Set the interface name(s) you want to toggle between DHCP and static addressing.
## limitations
For now only static IPs starting with ```192.168``` will be toggled.
Should be easy to add different addresses if I find it necessary.
## Errors
If toggledhcp cannot find the configurations for the interfaces, 
it will print an error and safely exit without modifying ```/etc/conf.d/net```.
```ERROR: Could not find `config_wlan0="dhcp"`
ERROR: Could not find `config_wlan0="192.168.```



