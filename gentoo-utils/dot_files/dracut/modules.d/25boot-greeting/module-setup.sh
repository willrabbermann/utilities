#!/bin/sh
check() {
	return 0
}

depends() {
	return 0
}

install() {
	inst /usr/bin/clear
	inst_hook pre-udev 00 "$moddir/clear.sh"
	inst_hook pre-trigger 00 "$moddir/greeting.sh"
}
