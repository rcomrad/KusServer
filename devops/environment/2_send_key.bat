call credentials.bat

set "MICROSOFT_MEGALANGUAGE="
for /f "delims=" %%b in (setup.sh) do ( 
    call set "MICROSOFT_MEGALANGUAGE=%%MICROSOFT_MEGALANGUAGE%% %%b" 
)

type C:\Users\%local_user%\.ssh\id_rsa.pub | ssh root@%ip% -p %port% "%MICROSOFT_MEGALANGUAGE%"
