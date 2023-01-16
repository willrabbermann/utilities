# buildkernel
Linux kernel builder, upgrader, mover. Preform Gentoo Linux system administration tasks.

Change ```hosts``` and ```hostsTJ``` to your machine's hostnames/thread counts.

```./install``` installs to ```/usr/local/sbin/```

```
buildkernel   [-m -r -b -a -l -i -im -u -me -c -cl -rmk -h] [kernel_version,localhost]
--move         -- move build files.
--regen        -- regenerate /boot/grub/grub.cfg and exit.
--build        -- build /usr/src/linux and exit.
--auto         -- build /usr/src/linux & initramfs then continue to automatic moving.
--localhost    -- make in localhost only mode (e.g. "buildkernel --auto --localhost").
--i   [kver]   -- build initramfs and exit. [kver] is optional.
--im  [kver]   -- build initramfs and continue to moving. [kver] is optional.
--upgrade      -- copy the .config of the current kernel to a new kernel directory.
--menu         -- open menuconfig in /usr/src/linux.
--current      -- print current kernel(s) in eselect and exit.
--clean        -- clean cache directory: /var/cache/*
--rmkernels    -- remove old kernels and modules using a wildcard.
--help         -- print this help page and exit.
```
