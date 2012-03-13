#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

# Use aliases defined in the .bash_aliases file
if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

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

if [ -f "${HOME}/.gpg-agent-info" ]; then
	. "${HOME}/.gpg-agent-info"
	export GPG_AGENT_INFO
	export SSH_AUTH_SOCK
	export SSH_AGENT_PID
fi
# this avoid the passwd being asked on the console while in X
echo UPDATESTARTUPTTY | gpg-connect-agent 2>/dev/null > /dev/null
GPG_TTY=$(tty)
export GPG_TTY

### end

#Enable tab completion with sudo
complete -cf sudo

export EDITOR='vim'

export PATH=$PATH:/home/do/CodeSourcery/Sourcery_G++_Lite/bin:/usr/hitech/picc/9.83/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/do/workspace/brn/./click-brn/ns/:/home/do/workspace/brn/./ns2/lib
export PATH=/home/do/workspace/brn/./ns2/bin/:/home/do/workspace/brn/./click-brn/userlevel/:/home/do/workspace/brn/./click-brn/tools/click-align/:/home/do/workspace/brn/./helper/simulation/bin/:/home/do/workspace/brn/./helper/evaluation/bin:$PATH
export PATH=$PATH:/opt/java/jre/bin/:$HOME/.local/bin/
export JAVA_HOME=/opt/java

