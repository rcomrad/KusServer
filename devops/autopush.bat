cd ..
git branch -D autocommit
git branch autocommit
git stash
git switch autocommit
git stash apply
git add .
git commit -m 'autocommit'
git push -f --set-upstream origin autocommit
git switch -
git stash pop
