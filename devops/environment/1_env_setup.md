1) in virtual box general settings:
    Advanced
        biderectional
        biderectional

2) in virtual box network settings:
    port forwarding
        4444 -> 22 (PORT SHOULD BE CONSISTENT WITH credentials.bat)

3) on linux run command
    # download modules for ssh connections
    sudo apt install openssh-server
    
    # allow to connect via ssh to root
    sed -i 's/^#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

    # restart ssh service after sshd_config change
    sudo systemctl restart ssh

    [optionally]
        # set your own password for root user
        sudo passwd root

4) Generate ssh-key. As a result you should have id_rsa and id_rsa.pub in yout .ssh folder.
    For windows its C:\Users\[user]\.ssh
   To set up yout windows user name change local_user variable in credentials.bat file.
