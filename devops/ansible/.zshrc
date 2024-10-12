# If you come from bash you might have to change your $PATH.
# export PATH=$HOME/bin:$HOME/.local/bin:/usr/local/bin:$PATH

# Path to your Oh My Zsh installation.
export ZSH=$HOME/.oh-my-zsh
setopt APPEND_HISTORY

# Set name of the theme to load --- if set to "random", it will
# load a random theme each time Oh My Zsh is loaded, in which case,
# to know which specific one was loaded, run: echo $RANDOM_THEME
# See https://github.com/ohmyzsh/ohmyzsh/wiki/Themes
#ZSH_THEME="agnoster"
# ZSH_THEME="amuse"

# ZSH_THEME_VIRTUAL_ENV_PROMPT_PREFIX=" %{$fg[green]%}~ "
# ZSH_THEME_VIRTUALENV_PREFIX=$ZSH_THEME_VIRTUAL_ENV_PROMPT_PREFIX
# ZSH_THEME_VIRTUALENV_SUFFIX=$ZSH_THEME_VIRTUAL_ENV_PROMPT_SUFFIX

# USER=%{$fg_bold[blue]%}%n@%m
# PROMPT='
# {$fg_bold[blue]%}%n@%m%{$fg_bold[green]%}%~%{$reset_color%} | %{$fg_bold[red]%}%$(virtualenv_prompt_info)%{$reset_color%} $(git_prompt_info)$(virtualenv_prompt_info)
# $ '

# /home/user/.oh-my-zsh/themes/adben.zsh-theme

# RED_START="${PR_RED} "
MAGENTA='%{$fg_bold[magenta]%}'
GREEN='%{$fg_bold[green]%}'
BLUE='%{$fg_bold[blue]%}'
CYAN='%{$fg_bold[cyan]%}'
RED='%{$fg_bold[red]%}'
YELLOW='%{$fg_bold[yellow]%}'
RESET='%{$reset_color%}'

ZSH_LOGIN='%n@%m'
ZSH_PATH='[ %~ ]'
ZSH_GIT='$(git_prompt_info)$(virtualenv_prompt_info)'

# PROMPT='%{$fg_bold[green]%}%n@%m %{$fg[blue]%}%D{[%X]} %{$reset_color%} '
PROMPT="
${GREEN}${ZSH_LOGIN}${RESET} ${CYAN}${ZSH_PATH}${RESET} ${RED}${ZSH_GIT}${RESET} 
${YELLOW}--> ${RESET}"

#  %s ${GREEN}

# ZSH_PROMPT_BASE_COLOR="%{$fg_bold[blue]%}"
# ZSH_THEME_REPO_NAME_COLOR="%{$fg_bold[red]%}"


# %{$fg_bold[green]%}
# %{$fg[cyan]%}%c
# %{$fg_bold[blue]%}$(git_prompt_info)
# %{$fg_bold[blue]%}$(svn_prompt_info)
# %{$reset_color%}


# PROMPT='
# %{$fg_bold[green]%}%~%{$reset_color%}$(git_prompt_info)$(virtualenv_prompt_info) ⌚ %{$fg_bold[red]%}%*%{$reset_color%}
# $ '

# ' %{$fg[blue]%}%D{[%X]} %{$reset_color%} '

# PROMPT=$'%{$fg_bold[green]%}%n@%m %{$fg[blue]%}%D{[%X]} %{$reset_color%}%{$fg[white]%}[%~]%{$reset_color%} $(git_prompt_info)\
# %{$fg[blue]%}->%{$fg_bold[blue]%} %#%{$reset_color%} '

# RED_START="${PR_GREY}<${PR_RED}<${PR_BRIGHT_RED}<${PR_RESET} "
# RED_END="${PR_BRIGHT_RED}>${PR_RED}>${PR_GREY}>${PR_RESET} "
# GREEN_START="${PR_GREY}>${PR_GREEN}>${PR_BRIGHT_GREEN}>${PR_RESET}"
# GREEN_END="${PR_BRIGHT_GREEN}>${PR_GREEN}>${PR_GREY}>${PR_RESET} "


# # Prompt: header, context (user@host), directory
# PROMPT="${RED_START}${PR_YELLOW}\$(prompt_header)${PR_RESET}
# ${RED_START}\$(prompt_context)${PR_BRIGHT_YELLOW}%~${PR_RESET}
# ${GREEN_START} "
# # Right prompt: vcs status + time
# RPROMPT="\$(git_prompt_info)\$(svn_prompt_info)${PR_YELLOW}%D{%R.%S %a %b %d %Y} ${GREEN_END}"
# # Matching continuation prompt
# PROMPT2="${GREEN_START} %_ ${GREEN_START} "


# PROMPT="${RED_START}${PR_YELLOW}\$(prompt_header)${PR_RESET}"


# Set list of themes to pick from when loading at random
# Setting this variable when ZSH_THEME=random will cause zsh to load
# a theme from this variable instead of looking in $ZSH/themes/
# If set to an empty array, this variable will have no effect.
# ZSH_THEME_RANDOM_CANDIDATES=( "robbyrussell" "agnoster" )

# Uncomment the following line to use case-sensitive completion.
# CASE_SENSITIVE="true"

# Uncomment the following line to use hyphen-insensitive completion.
# Case-sensitive completion must be off. _ and - will be interchangeable.
# HYPHEN_INSENSITIVE="true"

# Uncomment one of the following lines to change the auto-update behavior
# zstyle ':omz:update' mode disabled  # disable automatic updates
# zstyle ':omz:update' mode auto      # update automatically without asking
# zstyle ':omz:update' mode reminder  # just remind me to update when it's time

# Uncomment the following line to change how often to auto-update (in days).
# zstyle ':omz:update' frequency 13

# Uncomment the following line if pasting URLs and other text is messed up.
# DISABLE_MAGIC_FUNCTIONS="true"

# Uncomment the following line to disable colors in ls.
# DISABLE_LS_COLORS="true"

# Uncomment the following line to disable auto-setting terminal title.
# DISABLE_AUTO_TITLE="true"

# Uncomment the following line to enable command auto-correction.
ENABLE_CORRECTION="true"

# Uncomment the following line to display red dots whilst waiting for completion.
# You can also set it to another string to have that shown instead of the default red dots.
# e.g. COMPLETION_WAITING_DOTS="%F{yellow}waiting...%f"
# Caution: this setting can cause issues with multiline prompts in zsh < 5.7.1 (see #5765)
# COMPLETION_WAITING_DOTS="true"

# Uncomment the following line if you want to disable marking untracked files
# under VCS as dirty. This makes repository status check for large repositories
# much, much faster.
# DISABLE_UNTRACKED_FILES_DIRTY="true"

# Uncomment the following line if you want to change the command execution time
# stamp shown in the history command output.
# You can set one of the optional three formats:
# "mm/dd/yyyy"|"dd.mm.yyyy"|"yyyy-mm-dd"
# or set a custom format using the strftime function format specifications,
# see 'man strftime' for details.
HIST_STAMPS="dd.mm.yyyy"

# Would you like to use another custom folder than $ZSH/custom?
# ZSH_CUSTOM=/path/to/new-custom-folder

# Which plugins would you like to load?
# Standard plugins can be found in $ZSH/plugins/
# Custom plugins may be added to $ZSH_CUSTOM/plugins/
# Example format: plugins=(rails git textmate ruby lighthouse)
# Add wisely, as too many plugins slow down shell startup.
plugins=(git)

source $ZSH/oh-my-zsh.sh

# User configuration

# export MANPATH="/usr/local/man:$MANPATH"

# You may need to manually set your language environment
# export LANG=en_US.UTF-8

# Preferred editor for local and remote sessions
# if [[ -n $SSH_CONNECTION ]]; then
#   export EDITOR='vim'
# else
#   export EDITOR='nvim'
# fi

# Compilation flags
# export ARCHFLAGS="-arch $(uname -m)"

# Set personal aliases, overriding those provided by Oh My Zsh libs,
# plugins, and themes. Aliases can be placed here, though Oh My Zsh
# users are encouraged to define aliases within a top-level file in
# the $ZSH_CUSTOM folder, with .zsh extension. Examples:
# - $ZSH_CUSTOM/aliases.zsh
# - $ZSH_CUSTOM/macos.zsh
# For a full list of active aliases, run `alias`.
#
# Example aliases
# alias zshconfig="mate ~/.zshrc"
# alias ohmyzsh="mate ~/.oh-my-zsh"
