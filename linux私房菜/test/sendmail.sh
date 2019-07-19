#!/bin/bash
#program 
#	send a mail
# sendmail <mailaddress> <magess>
[ "$#" -lt 2 ] && echo "error: sendmail <mailadress> <magess>" && exit 0 
echo "send to:  $1"
shift
echo "magess:\n  $*"
echo "send from: ${USER} "
