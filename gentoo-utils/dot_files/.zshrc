autoload -U compinit promptinit
compinit
promptinit; prompt gentoo

zstyle ':completion::complete:*' use-cache 1
zstyle ':completion:*' rehash true
zstyle ':completion:*' insert-tab false

[[ $COLORTERM = *(24bit|truecolor)* ]] || zmodload zsh/nearcolor

autoload -Uz add-zsh-hook

reset_broken_terminal()
{
	printf '%b' '\e[0m\e(B\e)0\017\e[?5l\e7\e[0;0r\e8'
}

add-zsh-hook -Uz precmd reset_broken_terminal

git_prompt()
{
	ref=$(git symbolic-ref HEAD --short 2>/dev/null)
	[ $? = 0 ] && echo "( $ref) "
}

setopt prompt_subst
PROMPT='%F{004}%n%f%F{006}@%f%F{005}%m%f %F{006}%~ $(git_prompt)λ%f '

bindkey '^[[H' beginning-of-line
bindkey '^[OH' beginning-of-line
bindkey '^[[1~'	beginning-of-line
bindkey '^H' beginning-of-line
bindkey '^[OF' end-of-line
bindkey '^[[F' end-of-line
bindkey '^[[4~' end-of-line
bindkey '^E' end-of-line
bindkey '^[[1;5C' forward-word
bindkey '^[[1;5D' backward-word
bindkey '^Z' undo
bindkey '^[[3~' delete-char
bindkey '^R' history-incremental-search-backward

export HISTSIZE=2000
export HISTFILE="$HOME/.zsh_history" 
export SAVEHIST=$HISTSIZE
setopt hist_ignore_all_dups
setopt hist_ignore_space

setopt autocd
setopt extendedglob

alias ls='ls --color=auto'
alias dir='dir --color=auto'
alias vdir='vdir --color=auto'
alias grep='grep --color=auto'

alias ll='ls -laAFh --group-directories-first'
alias la='ls -aAF  --group-directories-first'
alias l='ls -CFA  --group-directories-first'

function dotcomplete()
{
	if [[ $BUFFER =~ ^'\.'$ ]]; then
		BUFFER='./'
		CURSOR=2
		zle list-choices
	elif [[ $BUFFER = '' ]];  then
		print && ls -CFaA --group-directories-first
		zle reset-prompt
	else
		zle expand-or-complete		
	fi
}

bindkey '^I' dotcomplete
zle -N dotcomplete

eval `ssh-agent` > /dev/null

if [[ -d /usr/lib/distcc/ ]] then
	if grep -q  "distcc" <<< "$PATH"; then
	else export PATH="/usr/lib/distcc/bin:${PATH}"
	fi
fi

. /etc/env.d/00custom
. /usr/share/zsh/site-functions/zsh-syntax-highlighting.zsh
typeset -A ZSH_HIGHLIGHT_STYLES
ZSH_HIGHLIGHT_MAXLENGTH=512

