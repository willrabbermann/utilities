#!/bin/sh
check() {
	return 0
}

depends() {
	return 0
}

install() {
	inst /usr/bin/clear
	inst_hook pre-trigger 00 "$moddir/greeting.sh"
}
