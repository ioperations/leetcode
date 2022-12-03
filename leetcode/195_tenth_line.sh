#!/usr/bin/env sh
ccred="\033[0;31m"
ccgreen="\033[0;32m"
ccyellow="\033[0;33m"
ccwhite="\033[0;37m"


# echo "Line1\nLine2\nLine3\nLine4\nLine5\nLine6\nLine7\nLine8\nLine9\nLine10\n"|head -n10 | tail -n1

# shellcheck disable=SC2028

echo "Line1\nLine2\nLine3\nLine4\nLine5\nLine6\nLine7\nLine8\nLine9\nLine10\n"| awk 'NR==10 {print $0}'

# shellcheck disable=SC2028
echo "Line1\nLine2\nLine3\nLine4\nLine5\nLine6\nLine7\nLine8\nLine9\n"| awk 'NR==10 {print $0}'

# echo file.txt |  head -n 10 | tail -n 1
