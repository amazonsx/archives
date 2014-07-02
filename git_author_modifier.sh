#! /bin/sh
git filter-branch --env-filter '
 
an="$GIT_AUTHOR_NAME"
am="$GIT_AUTHOR_EMAIL"
cn="$GIT_COMMITTER_NAME"
cm="$GIT_COMMITTER_EMAIL"
 
if [ "$GIT_COMMITTER_EMAIL" = "root@guoshi20.(none)" ]
then
    cn="Your new usernmae"
    cm="Your new email addr"
fi
if [ "$GIT_AUTHOR_EMAIL" = "root@guoshi20.(none)" ]
then
    an="Your new username" 
    am="Your new email addr"
fi 
export GIT_AUTHOR_NAME="$an" 
export GIT_AUTHOR_EMAIL="$am"
export GIT_COMMITTER_NAME="$cn"
export GIT_COMMITTER_EMAIL="$cm" 
'
