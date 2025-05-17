# sudo nano .zshrc

sudo apt install -y git curl zsh
chsh -s $(which zsh) 
sudo -H -u $1 ZSH=/home/$1/.zsh CHSH=yes RUNZSH=no sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
sudo usermod -s /usr/bin/zsh $1
mkdir -p /home/$1/.cache/zsh

# sudo ln -s /root/.zshrc $HOME/.zshrc
# sudo ln -s /root/.oh-my-zsh $HOME/.oh-my-zsh      

#sudo apt-get install powerline fonts-powerline zsh-theme-powerlevel9k zsh-syntax-highlighting -y

#ZSH_THEME="robbyrussell"
#HISTSIZE=1300
#SAVEHIST=1000
#HISTFILE=~/.cache/zsh/history
#setopt INC_APPEND_HISTORY
#setopt SHARE_HISTORY
