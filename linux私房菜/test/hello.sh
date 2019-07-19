#!/bin/bash
echo "HELLO"
case ${1} in
	"hello")
		echo "my name is ${USER}"
	   	;;
	"ls")
		echo "ls"
		ls
		;;
	"what can you do")
		echo "I can do 'ls' for you"
		;;
	"")
		echo " I'm here"
		;;
	*)
		echo "sorry, I can't understand what you say"
		;;
esac
