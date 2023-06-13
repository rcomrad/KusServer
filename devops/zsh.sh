# sudo nano .zshrc

sudo apt install -y git curl zsh
chsh -s $(which zsh) 
sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# sudo usermod -s /usr/bin/zsh $(whoami)
# mkdir ~/.cache/zsh

# sudo ln -s /root/.zshrc $HOME/.zshrc
# sudo ln -s /root/.oh-my-zsh $HOME/.oh-my-zsh      
# la -a
# ls -a

#sudo apt-get install powerline fonts-powerline zsh-theme-powerlevel9k zsh-syntax-highlighting -y


#ZSH_THEME="robbyrussell"
#HISTSIZE=1300
#SAVEHIST=1000
#HISTFILE=~/.cache/zsh/history
#setopt INC_APPEND_HISTORY
#setopt SHARE_HISTORY
