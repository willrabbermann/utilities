# toggledistcc #
```toggledistcc``` preserves your entire make.conf and does the following:

1. Set ```MAKEOPTS=``` automatically to toggle distcc opts. No other makeopt setting will be preserved.

Distcc on: ```"-j#DISTCC_TJ -l#LOCAL_TJ"``` Distcc off: ```"-j#LOCAL_TJ"```

2. Set ```FEATURES=``` and preserve previous feature entries, as well as performing 
   space limiting (one space per word, none on the beginning or ends).

Distcc on: ```"other_feature distcc"``` Distcc off: ```"other_feature"```

3. Start/stop distcc service in OpenRC.

## config.h ##
User configuations are set in ```config.h``` before compiling.

toggledistcc is compiled with a constant ```DISTCC_TJ```, which represents the max number of threads when using distcc (remote + local); It is recommended to update this to match your setup.

A system command is run to find the thread count of your local processor. Therefore it is not necessary to update ```LOCAL_TJ```.

## why? ##
I made toggledistcc so I could easily turn distcc off when I start getting ICE (internal compiler errors).
Some things compile fine with distcc opts but its useful being able to turn them off when errors arise.

## Notice ##
It is important to add/remove ```/usr/lib/distcc/bin:``` from the beginning of your ```PATH``` environment variable when you enable/disable distcc.
Running toggledistcc can not do this for you, as it is a child process and changes to PATH are not persistent when the program ends.
Restart your shell after using toggledistcc and update PATH in your .shellrc like so:
```
if [[ -d /usr/lib/distcc/ && -n $(grep distcc /etc/portage/make.conf) ]]; then
	if grep -q "distcc" <<< "$PATH"; then
	else export PATH="/usr/lib/distcc/bin:${PATH}"
	fi
fi
```
Or set PATH manually without ```/usr/lib/distcc/bin:```
