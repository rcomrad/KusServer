#!/bin/bash
set -exu

user=rcomrad
password=123

printf "0 postgres postgres $password public\n1 journal_db $user $password journal\n" > database.pass

sudo cp ./pg_hba.conf /etc/postgresql/16/main/pg_hba.conf
sudo -u postgres psql -c "ALTER USER postgres password '$password';"

# TODO: add journal_user and database from start
sudo -u postgres psql -c "CREATE USER $user;"
sudo -u postgres psql -c "ALTER USER $user password '$password';"
sudo -u postgres psql -c "CREATE DATABASE journal_db;"