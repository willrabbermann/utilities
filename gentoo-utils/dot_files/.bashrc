# .bashrc

# Single ssh-agent per bash session
kill_ssh_agent() {
	ssh-agent -k > /dev/null
}
eval "$(ssh-agent)" > /dev/null
trap kill_ssh_agent EXIT

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

tput smkx
tabs -n

. /etc/env.d/00custom
