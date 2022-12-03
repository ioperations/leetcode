#!/usr/bin/env sh
ccred="\033[0;31m"
ccgreen="\033[0;32m"
ccyellow="\033[0;33m"
ccwhite="\033[0;37m"

# the day is sunny the the
# the sunny is is


echo  "the day is sunny the the \nthe sunny is is" | tr " " "\n" |  grep -v "^$"   |sort -n -r |  uniq -c | awk '{print $2 " " $1}'


echo ""

echo  "a  a   b" | tr " " "\n" |  grep -v "^$"   |sort -n -r |  uniq -c | sort -n  -r | awk '{print $2 " " $1}'

 #cat words.txt  | tr " " "\n" |  grep -v "^$"   |sort -n -r | uniq -c | awk '{print $2 " " $1}'


# the 4
# is 3
# sunny 2
# day 1
