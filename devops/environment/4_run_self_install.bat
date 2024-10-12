call _credentials.bat

ssh root@%ip% -p %port% "apt install -y git"
ssh root@%ip% -p %port% "mkdir -p ~/projects && cd ~/projects && git clone -b version_5 https://github.com/rcomrad/KusServer.git"
ssh root@%ip% -p %port% "cd ~/projects/KusServer/ && git fetch --all && git reset --hard origin/version_5" @REM TODO: remove
ssh root@%ip% -p %port% "cd ~/projects/KusServer/devops/environment && chmod +x ./setup.sh && ./setup.sh"
