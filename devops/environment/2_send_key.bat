call _credentials.bat

type id_rsa.pub | ssh %user%@%ip% -p %port% "rm -rf ~/* && mkdir -p ~/.ssh && cat > ~/.ssh/authorized_keys"
