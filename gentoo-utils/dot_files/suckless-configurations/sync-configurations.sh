#!/bin/sh
# `rsync` my suckless configs and remove the `.git/` directories then `git add` them for deltas.

rsync -aHAXhvPS /mnt/nfs/block0/backup/important/dot_files/custom-files/gentoo/dwm-custom-configs/* /home/will/projects/github/utilities/gentoo-utils/dot_files/suckless-configurations --exclude=*.7z

cd /home/will/projects/github/utilities/gentoo-utils/dot_files/suckless-configurations

echo -e "\nRemoving */.git/ submodules from $(pwd)\n"
rm */.git/ -rfv

echo -e "\nAdding all new files to git...\n"
git add -v *
