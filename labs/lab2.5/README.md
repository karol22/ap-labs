Lab 2.5 - Depth-limiting Web Crawler
====================================

Add depth-limiting to the concurrent web crawler from [crawl2.go](https://github.com/CodersSquad/hello-gophers/blob/master/src/crawl2.go).
That is, if the user sets `-depth=3`, then only URLs reachable by at most 3 links will be fetched.

#How to run it:

First, enter the following command:
 ```go run crawl3.go -depth=<DEPTH> <URL>```
 It is mandatory to add the `depth` flag. For example, if you type `go run crawl3.go -depth=0 www.example.com` it would return the url itself.