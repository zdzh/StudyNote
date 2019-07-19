#!/bin/bash
#program
#  creat one file named by user's input and date command

read -p "please input file name: " fileuser
filename=${fileuser:-"backup"}
datestr=$(date +%y%m%d)
filename=${filename}-${datestr}
touch "${filename}"
