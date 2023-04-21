#!/bin/sh
# rsync my suckless configs and remove the .git/ submodule directories then `git add` them for deltas.

rsync --del -aHAXhvPS /mnt/nfs/block0/backup/important/dot_files/custom-files/gentoo/dwm-custom-configs/* /home/will/projects/github/utilities/gentoo-utils/dot_files/suckless-configurations --exclude=.git/ --exclude=*.7z --exclude="sync-configurations.sh"

cd /home/will/projects/github/utilities/gentoo-utils/dot_files/suckless-configurations

echo -e "\nAdding all new files to git...\n"
git add -v *
