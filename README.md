# zmq_playground

### Discovered
* zsh and it's [git aliases](https://github.com/robbyrussell/oh-my-zsh/wiki/Cheatsheet)


### How to build zmq program with cpp bidnings
[Install cpp bindings](https://github.com/zeromq/cppzmq)

[Fix linking](https://stackoverflow.com/questions/12470117/compile-simple-hello-world-zeromq-c-example-compile-flags)

```
g++ -std=c++0x client.cpp -o client -L/usr/local/lib -lzmq
```
### Todo
1. Make c++ auto-complete work for Sublime
2. Need lock for adding to queue?