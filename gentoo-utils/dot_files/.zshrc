autoload -U compinit promptinit
compinit
promptinit; prompt gentoo

zstyle ':completion::complete:*' use-cache 1
zstyle ':completion:*' rehash true
zstyle ':completion:*' insert-tab false
setopt correct

[[ $COLORTERM = *(24bit|truecolor)* ]] || zmodload zsh/nearcolor

case $(tty) in
	(/dev/tty[1-9]) custom_colors=0;;
	(*) custom_colors=1;;
esac

autoload -Uz add-zsh-hook

reset_broken_terminal()
{
	printf '%b' '\e[0m\e(B\e)0\017\e[?5l\e7\e[0;0r\e8'
}

add-zsh-hook -Uz precmd reset_broken_terminal

git_prompt()
{
	ref=$(git symbolic-ref HEAD --short 2>/dev/null) && echo "( $ref) "
}

setopt prompt_subst
PROMPT='%F{004}%n%f%F{006}@%f%F{005}%m%f %F{006}%~ $(git_prompt)λ%f '

# insert / page / space  keys
bindkey '^[[2~' complete-word
bindkey '^[[5~' up-history
bindkey '^[[6~' down-history
bindkey ' '		magic-space
# home / end keys
bindkey '^[[H' beginning-of-line
bindkey '^[[104;5u' beginning-of-line
bindkey '^[OH' beginning-of-line
bindkey '^[[1~' beginning-of-line
bindkey '^H' beginning-of-line
bindkey '^[OF' end-of-line
bindkey '^[[F' end-of-line
bindkey '^[[4~' end-of-line
bindkey '^E' end-of-line
# Shift|Ctrl + Left|Right move by word
bindkey '^[[1;5C' forward-word
bindkey '^[[1;5D' backward-word
bindkey '^[[1;2C' forward-word
bindkey '^[[1;2D' backward-word
# Shift+Ctrl+Left|Right delete word
bindkey '^[[1;6C' delete-word
bindkey '^[[1;6D' backward-delete-word
# Ctrl+Up|Down change case of word
bindkey '^[[1;5B' down-case-word
bindkey '^[[1;5A' up-case-word
# Shift+Up|Down swap case of char
bindkey '^[[1;2A' vi-swap-case
bindkey '^[[1;2B' vi-swap-case
bindkey '^Z' undo
bindkey '^[[90;6u' redo
bindkey '^R' history-incremental-search-backward
bindkey '^[[3~' delete-char
# Shift+tab clear screen
bindkey '^[[Z' clear-screen

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
alias tree='tree -C'

alias ll='ls -lAFh --group-directories-first'
alias la='ls -CFA --group-directories-first'
alias l='ls -CF --group-directories-first'

tab_complete()
{
	if [[ $BUFFER =~ ^'\.'$ ]]; then
		BUFFER='./'
		CURSOR=2
		zle list-choices
	elif [[ -z "${BUFFER// /}" ]]; then
		#zle -R "" $(la)
		print && la
		zle reset-prompt
	else
		zle expand-or-complete		
	fi
}

bindkey '^I' tab_complete
zle -N tab_complete

kill_ssh_agent()
{
	ssh-agent -k > /dev/null
}

eval "$(ssh-agent)" > /dev/null
add-zsh-hook -Uz zshexit kill_ssh_agent

if [[ -d /usr/lib/distcc/ && -n $(grep distcc /etc/portage/make.conf) ]]; then
	if grep -q  "distcc" <<< "$PATH"; then
	else export PATH="/usr/lib/distcc/bin:${PATH}"
	fi
fi

. /etc/env.d/00custom

if [ $custom_colors = 1 ]; then
	. /usr/share/zsh/site-functions/zsh-syntax-highlighting.zsh
	typeset -A ZSH_HIGHLIGHT_STYLES
	ZSH_HIGHLIGHT_MAXLENGTH=512
	ZSH_HIGHLIGHT_HIGHLIGHTERS=(main brackets pattern regexp root line)
	ZSH_HIGHLIGHT_STYLES[cursor-matchingbracket]='underline'
	ZSH_HIGHLIGHT_STYLES[bracket-level-1]='fg=red,bold'
	ZSH_HIGHLIGHT_STYLES[bracket-level-2]='fg=green,bold'
	ZSH_HIGHLIGHT_STYLES[bracket-level-3]='fg=blue,bold'
	ZSH_HIGHLIGHT_STYLES[bracket-level-4]='fg=magenta,bold'
	ZSH_HIGHLIGHT_STYLES[path]='none'
	ZSH_HIGHLIGHT_STYLES[unknown-token]='fg=none'
	ZSH_HIGHLIGHT_STYLES[reserved-word]='fg=green'
	ZSH_HIGHLIGHT_STYLES[suffix-alias]='fg=green'
	ZSH_HIGHLIGHT_STYLES[global-alias]='fg=green'
	ZSH_HIGHLIGHT_STYLES[builtin]='fg=green'
	ZSH_HIGHLIGHT_STYLES[function]='fg=blue'
	ZSH_HIGHLIGHT_STYLES[command]='fg=blue'
	ZSH_HIGHLIGHT_STYLES[precommand]='fg=blue'
	ZSH_HIGHLIGHT_STYLES[alias]='fg=blue'
	ZSH_HIGHLIGHT_STYLES[globbing]='fg=magenta'
	ZSH_HIGHLIGHT_STYLES[single-quoted-argument]='fg=magenta'
	ZSH_HIGHLIGHT_STYLES[double-quoted-argument]='fg=magenta'
	ZSH_HIGHLIGHT_STYLES[dollar-quoted-argument]='fg=magenta'
	ZSH_HIGHLIGHT_STYLES[history-expansion]='fg=blue'
	ZSH_HIGHLIGHT_STYLES[command-substitution]='fg=magenta'
	ZSH_HIGHLIGHT_PATTERNS+=('sudo' 'fg=red,bold')
	ZSH_HIGHLIGHT_PATTERNS+=('rm -r' 'fg=red,bold')
	ZSH_HIGHLIGHT_PATTERNS+=('rm -rf' 'fg=red,bold')
	ZSH_HIGHLIGHT_PATTERNS+=('rm -fr' 'fg=red,bold')
fi
