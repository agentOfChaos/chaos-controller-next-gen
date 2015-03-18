# chaos-controller-next-gen

====

Newer, smarter and sexier version of my hackish tool.  
The major difference is that now you can inject a _list_ of numbers, instead of just one.  
  
The other difference is that this program will run alongside the target ( it works just like a debugger ), while the older version is "fire and forget"  

Running
-------
# ccnxt -p [target pid] [list of space separated numbers]...

Stopping
-------
Ctrl-C will prompt it to quit gracefully; pressing Ctrl-C again will stop it abruptly.

Help
-------
$ ccnxt --help