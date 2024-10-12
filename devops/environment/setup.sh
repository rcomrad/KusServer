set -exu

# cd to this script folder
cd "$(dirname "${BASH_SOURCE[0]}")"

apt update
apt upgrade -y
apt install -y ansible-core

ansible-playbook ../ansible/setup_dev_env.yml
# ansible -i ../ansible/inventory.yml -m ping local
# ansible-playbook localhost -m ping
