# Lab 2.1 - ClockWall

First, enter the following commands:
 ```go build clock2.go```
  ```go build clockWall.go```

Then you can execute the programs as in the example:
```
# Clock Servers initialization
$ TZ=US/Eastern    ./clock2 -port 8010 &
$ TZ=Asia/Tokyo    ./clock2 -port 8020 &
$ TZ=Europe/London ./clock2 -port 8030 &

# Starting clockWall client
$ clockWall NewYork=localhost:8010 Tokyo=localhost:8020 London=localhost:8030
US/Eastern    : 12:00:00
Asia/Tokyo    : 17:00:00
Europe/London : 02:00:00
.
.
.

```
