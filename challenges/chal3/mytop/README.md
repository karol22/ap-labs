MyTop
=====
-To run `make` and then `./mytop`
-Maybe you need to add the following to allow color in your syslog config file (otherwise, ignore):
- Open `/etc/rsyslog.conf` and add this line at the end: `$EscapeControlCharactersOnReceive off`
- Then restart syslog and your service:
