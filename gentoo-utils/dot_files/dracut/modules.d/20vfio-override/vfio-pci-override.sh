#!/bin/sh

DEVICES=(
		"0000:01:00.0 " # 3060 (VGA)
		"0000:01:00.1 " # 3060 (audio)
)

for dev in ${DEVICES[@]}; do
	echo "vfio-pci" > /sys/bus/pci/devices/$dev/driver_override
done

modprobe -i vfio-pci


