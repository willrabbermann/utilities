# toggledhcp
Toggle between DHCP and static addressing in netifrc. Modifies /etc/conf.d/net to enable/disable DHCP and static configurations.
Made for Gentoo OpenRC
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



## Example output (redacted info)
```
----------------------------------------
/etc/conf.d/net
----------------------------------------
config_eth0="dhcp"
#config_eth0="192.168.1.99/24"
routes_eth0="default via 192.168.1.1"
dns_servers_eth0="192.168.1.1 6.6.6.6"
----------------------------------------
**Disabling dhcp for interface eth0**
new /etc/conf.d/net
----------------------------------------
#config_eth0="dhcp"
config_eth0="192.168.1.99/24"
routes_eth0="default via 192.168.1.1"
dns_servers_eth0="192.168.1.1 6.6.6.6"
----------------------------------------
Restarting network interfaces...
----------------------------------------
 * WARNING: you are stopping a boot service
 * Caching service dependencies ...                                                                                                   [ ok ]
 * Bringing down interface eth0
 *   Stopping dhcpcd on eth0 ...
sending signal TERM to pid 4934
waiting for pid 4934 to exit                                                                                                          [ ok ]
 * Bringing up interface eth0
 *   192.168.1.99/24 ...                                                                                                               [ ok ]
 *   Adding routes
 *     default via 192.168.1.1 ...                                                                                                    [ ok ]
```
