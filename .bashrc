#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

# Use aliases defined in the .bash_aliases file
if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

#Source git bash completion scripts so that __git_ps1 is defined
#see: https://bbs.archlinux.org/viewtopic.php?id=147462
source /usr/share/git/git-prompt.sh

#Add colors to core utils
alias ls='ls --color=auto'
eval $(dircolors -b $HOME/LS_COLORS/LS_COLORS)
alias grep='grep --color=auto'
export LESS="-R"

scm_ps1() {
    local s=
    if [[ -d ".svn" ]] ; then
        s=\(svn:$(svn info | sed -n -e '/^Revision: \([0-9]*\).*$/s//\1/p' )\)
    else
        s=$(__git_ps1 "(git:%s)")
    fi
    echo -n "$s"
}

#PS1='[\u@\h \W]\$ '
#PS1='\[\e[0;32m\]\u\[\e[m\] \[\e[36m\]\w\[\e[m\] \[\e[1;31m\]$(__git_ps1 "(%s) ")\[\e[m\]\[\e[1;32m\]\$ \[\e[m\]\[\e[1;37m\]'
PS1="\[\e[2;37m\][\A] \[\e[32m\]\w\[\e[35m\] \$(scm_ps1)\[\e[31m\]\$\[\e[0m\] "
#PS1="\[\033[00;32m\]\u\[\033[00;32m\]@\[\033[00;32m\]\h:\[\033[01;34m\]\w \[\033[31m\]\$(scm_ps1)\[\033[00m\]$\[\033[00m\] "

### GPG agent config
envfile="$HOME/.gnupg/gpg-agent.env"
if [[ -e "$envfile" ]] && kill -0 $(grep GPG_AGENT_INFO "$envfile" | cut -d: -f 2) 2>/dev/null; then
    eval "$(cat "$envfile")"
else
    eval "$(gpg-agent --daemon --enable-ssh-support --write-env-file "$envfile")"
fi
export GPG_AGENT_INFO  # the env file does not contain the export statement
export SSH_AUTH_SOCK   # enable gpg-agent for ssh

### end

#Enable tab completion with sudo
complete -cf sudo

export EDITOR='vim'

export PATH=$PATH:/home/do/CodeSourcery/Sourcery_G++_Lite/bin:/usr/hitech/picc/9.83/bin
export PATH=$PATH:/opt/sun-java6/bin/:$HOME/.local/bin/
export JAVA_HOME=/opt/sun-java6

