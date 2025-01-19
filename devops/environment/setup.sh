mkdir -p ~/.ssh                                                     &&
cat > ~/.ssh/authorized_keys                                        &&

set -o xtrace                                                       &&

apt update -y                                                       && 
apt upgrade -y                                                      &&

apt install -y git                                                  &&
mkdir -p ~/projects                                                 && 
cd ~/projects                                                       && 
git clone -b version_5 https://github.com/rcomrad/KusServer.git     &&

apt install -y ansible-core                                         &&
cd ./KusServer/devops/ansible/                                      &&
ansible-playbook ./setup_dev_env.yml
