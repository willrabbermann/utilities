#!/bin/sh
check() {
	return 0
}

depends() {
	return 0
}

install() {
	drivers+=" vfio-pci "
	inst_hook pre-udev 00 "$moddir/vfio-pci-override.sh"
}
