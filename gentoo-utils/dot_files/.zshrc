autoload -U compinit promptinit
compinit
promptinit; 

[[ Gentoo = $(head -n1 /etc/os-release | cut -d= -f2) ]] && 
	prompt gentoo 

zstyle ':completion::complete:*' use-cache 1
zstyle ':completion:*' rehash true
zstyle ':completion:*' insert-tab false
setopt correct
setopt autocd
setopt extendedglob

[[ $COLORTERM = *(24bit|truecolor)* ]] || zmodload zsh/nearcolor

case $(tty) in
	(/dev/tty[1-9]) 
		custom_colors=0 
		[[ -e /usr/local/bin/motd && -e /tmp/fresh-boot.tmp ]] && 
			rm /tmp/fresh-boot.tmp && motd;;
	(*) custom_colors=1;;
esac

autoload -Uz add-zsh-hook

find_zsh_hl_module()
{
	LOCATIONS=(
		# Gentoo
		"/usr/share/zsh/site-functions/zsh-syntax-highlighting.zsh" 
		# Fedora
		"/usr/share/zsh/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh"
	)
	for (( i=0; i < $#LOCATIONS; i++ ))
	do
		[[ -e $LOCATIONS[i] ]] && . $LOCATIONS[i] && return
	done
	printf "WARNING: \"zsh-syntax-highlighting.zsh\" not found!\n"
}

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

alias ls='ls --color=auto'
alias dir='dir --color=auto'
alias vdir='vdir --color=auto'
alias grep='grep --color=auto'
alias tree='tree -C'

alias ll='ls -lAFh --group-directories-first'
alias la='ls -CFA --group-directories-first'
alias l='ls -CF --group-directories-first'
alias dus='du -had1 | sort -h'
alias rsync-hax='rsync -aHAXhvPS --info=progress2 --no-i-r '

tab-complete()
{
	if [[ $BUFFER =~ ^'\.'$ ]]; then
		BUFFER='./'
		CURSOR=2
		zle list-choices
	elif [[ -z "${BUFFER// /}" ]]; then
		print && la
		zle reset-prompt
	else
		zle expand-or-complete		
	fi
}

select-all()
{
  MARK=0
  CURSOR=$#BUFFER
  [[ $REGION_ACTIVE = 1 ]] && REGION_ACTIVE=0 || REGION_ACTIVE=1
}

# tab
zle -N tab-complete
bindkey '^I' tab-complete
# ctrl + a
zle -N select-all
bindkey '^A' select-all
# insert / page / space  keys
bindkey '^[[2~' complete-word
bindkey '^[[5~' up-history
bindkey '^[[6~' down-history
bindkey ' ' magic-space
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
# shift|ctrl + left|right move by word
bindkey '^[[1;5C' vi-forward-word
bindkey '^[[1;5D' vi-backward-word
bindkey '^[[1;2C' vi-forward-word
bindkey '^[[1;2D' vi-backward-word
# shift+ctrl+left|right delete word
bindkey '^[[1;6C' delete-word
bindkey '^[[1;6D' backward-delete-word
# ctrl+up|down change case of word
bindkey '^[[1;5B' down-case-word
bindkey '^[[1;5A' up-case-word
# shift+up|down swap case of char
bindkey '^[[1;2A' vi-swap-case
bindkey '^[[1;2B' vi-swap-case
bindkey '^Z' undo
bindkey '^[[90;6u' redo
bindkey '^R' history-incremental-search-backward
bindkey '^[[3~' delete-char
# shift+tab clear screen
bindkey '^[[Z' clear-screen
bindkey '^[	'  clear-screen
# function keys
bindkey '^[OP' end-of-line
bindkey '^[OQ' end-of-line
bindkey '^[OR' end-of-line
bindkey '^[OS' end-of-line
bindkey '^[[15~' end-of-line
bindkey '^[[17~' end-of-line
bindkey '^[[18~' end-of-line
bindkey '^[[19~' end-of-line
bindkey '^[[20~' end-of-line
bindkey '^[[21~' end-of-line
bindkey '^[[23~' end-of-line
bindkey '^[[24~' end-of-line

HISTSIZE=2000
HISTFILE="$HOME/.zsh_history"
SAVEHIST=$HISTSIZE
setopt hist_ignore_all_dups
setopt hist_ignore_space
HISTORY_IGNORE='(git reset*|reboot|shutdown|exit|cd ..|cd ~|..|~)'

zshaddhistory() 
{
  emulate -L zsh
  [[ $1 != ${~HISTORY_IGNORE} ]] | fc -R $HISTFILE
}

kill_ssh_agent()
{
	ssh-agent -k > /dev/null
}

eval "$(ssh-agent)" > /dev/null
add-zsh-hook -Uz zshexit kill_ssh_agent

export_distcc_path()
{
	if [[ -d /usr/lib/distcc/ && -e /etc/portage/make.conf && 
		  -n $(grep distcc /etc/portage/make.conf) ]]
	then
		if grep -q  "distcc" <<< "$PATH"; then
		else export PATH="/usr/lib/distcc/bin:${PATH}"
		fi
	fi
}

export_distcc_path

# custom environment variables
[[ -e /etc/env.d/00custom ]] && . /etc/env.d/00custom

if [[ 1 = $custom_colors ]]
then
	find_zsh_hl_module
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
	ZSH_HIGHLIGHT_PATTERNS+=('visudo'  'fg=blue,bold')
	ZSH_HIGHLIGHT_PATTERNS+=('sudo '   'fg=red,bold')
	ZSH_HIGHLIGHT_PATTERNS+=('rm '     'fg=red,bold')
	ZSH_HIGHLIGHT_PATTERNS+=('rm *-* ' 'fg=red,bold')
fi
