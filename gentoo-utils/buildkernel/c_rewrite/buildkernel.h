const char *HELP_PAGE =
"buildkernel [ -h -b -a -i -im -m -me -r -u -d ] [-l -d -kver] [-l -d -kver] [-l -d -kver]\n\n\
Primary arguments:\n\n\
-h      --help                  Display this help page.\n\
-b      --build                 Make symlinked kernel and exit.\n\
-a      --auto                  Make kernel, initramfs, and move buildfiles.\n\
-i      --initramfs             Make initramfs and exit.\n\
-im     --initmove              Make initramfs and move buildfiles.\n\
-m      --move                  Move preexisting buildfiles in /boot.\n\
-me     --menuconfig            Open menuconfig on symlinked kernel.\n\
-r      --regen                 Regenerate grub.cfg.\n\
-u      --upgrade               Copy current config to different kernel.\n\
-d      --debug                 Enable debug messages.\n\n\
Secondary arguments:\n\n\
-l      --localhost             Make only on the localhost.\n\
                                This mode is off by default; enabled when\n\
                                distccd is off or when no other host is\n\
                                detected online.\n\n\
-k=#	--kver=[kver]           Specify a kernel version instead of the symlinked one.\n\
                                Must be a valid directory name in \"/usr/src/linux-[kver]\".\n\
                                With no kernel version supplied, default is symlinked.\n\n\
Made for Gentoo OpenRC. The symlinked kernel refers to the kernel linked from\n\
\"/usr/src/linux\". Use \"eselect kernel list|set\" to change the symlink.\n";

const char *ARGS_HELP[] = { "-h", "-help", "--help", "help", NULL };
const char *ARGS_BUILD[] = { "-b", "-build", "--build", NULL };
const char *ARGS_AUTO[] = { "-a", "-auto", "--auto", NULL };
const char *ARGS_INITRD[] = { "-i", "-initramfs", "--initramfs", NULL };
const char *ARGS_INITRDMOVE[] = { "-im", "-initmove" ,"--initmove", NULL };
const char *ARGS_MOVE[] = { "-m", "-move", "--move", NULL };
const char *ARGS_MENUCONF[] = { "-me", "-memu", "--menu", "-menuconfig", "--menuconfig", NULL };
const char *ARGS_REGEN[] = { "-r", "-regen", "--regen", NULL };
const char *ARGS_UPGRADE[] = { "-u", "-upgrade", "--upgrade", NULL };
const char *ARGS_LOCAL[] = { "-l", "-local", "--local", "--localhost", NULL };
const char *ARGS_KVER[] = { "-k=", "-kver=", "--kver=", NULL };
const char *ARGS_DEBUG[] = { "-d", "-debug", "--debug", NULL };
