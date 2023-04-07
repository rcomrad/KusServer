cd ..

set /p commitMessage="Commit message: "
echo %commitMessage%

git checkout master
git add .
git commit -m "%commitMessage%"
git push 
pause