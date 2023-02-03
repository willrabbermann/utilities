# enable tab completion
autoload -U compinit promptinit
compinit
promptinit; prompt gentoo

# use completion caching
zstyle ':completion::complete:*' use-cache 1
# completion styling
zstyle ':completion:*:descriptions' format '%U%B%d%b%u'
zstyle ':completion:*:warnings' format '%BSorry, no matches for: %d%b'
# auto-correct commands
setopt correctall

git_prompt()
{
	ref=$(git symbolic-ref HEAD --short 2>/dev/null)
	if [ $? = 0 ]
	then
		[ $ref = 'main' ] && echo "( $ref) " && return
		echo "( $ref) "	
	fi
}

setopt prompt_subst
PROMPT='%F{004}%n%f%F{006}@%f%F{005}%m%f %F{006}%~ $(git_prompt)λ%f '	

# keybinds
bindkey '^[[H' beginning-of-line
bindkey '^[OH' beginning-of-line
bindkey '^H' beginning-of-line
bindkey '^[OF' end-of-line
bindkey '^[[F' end-of-line
bindkey '^E' end-of-line
bindkey '^[[1;5C' forward-word
bindkey '^[[1;5D' backward-word
bindkey '^Z' undo
bindkey '^[[3~' delete-char
bindkey '^R' history-incremental-search-backward

export HISTSIZE=2000
export HISTFILE="$HOME/.zsh_history" 
# enable history
export SAVEHIST=$HISTSIZE

setopt hist_ignore_all_dups
setopt hist_ignore_space

# autocd if only a directory is entered
setopt autocd

setopt extendedglob

alias ls='ls --color'
alias dir='dir --color'
alias vdir='vdir --color'
alias grep='grep --color'

alias ll='ls -laF'
alias la='ls -A'
alias l='ls -CF'

su_cmd="sudo"
alias locate="nocorrect $su_cmd locate"
alias grep="nocorrect grep"
alias man="nocorrect man"
alias info="nocorrect info"

eval `ssh-agent` > /dev/null

case "$PATH" in
    *_"distcc"_*) 
		export PATH="/usr/lib/distcc/bin:${PATH}"
		;;
	*)
esac


. /etc/env.d/00custom
