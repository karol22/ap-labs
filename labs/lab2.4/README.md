Lab 2.4 - Add `syslog` support to your Logger
=============================================

To run it just type `make` and then type `./testLogger`.
Maybe you need to add the following to allow color in your syslog config file:
- Open `/etc/rsyslog.conf` and add this line at the end: `$EscapeControlCharactersOnReceive off`
- Then restart syslog and your service:
`systemctl restart rsyslog`