// toggledistcc configuration file
// Set DISTCC_TJ (what is configured as -j# in MAKEOPTS) with your remote + local jobs.
const size_t DISTCC_TJ = 24;
// If LOCAL_TJ is 0, a system command will find your local thread count and use it.
// Set LOCAL_TJ if you need a specific value.
size_t LOCAL_TJ = 0;
