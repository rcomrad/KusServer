#!/bin/bash
set -exu

sudo -u postgres psql -c "select * from user;"
sudo -u postgres psql -c "select * from information_schema.schemata;"