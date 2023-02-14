cd ..
git branch -D autocommit
git checkout -b autocommit
git stash
git switch autocommit
git stash apply
git add .
git commit -m 'autocommit'
git push -f --set-upstream origin autocommit
git switch -
git stash pop
