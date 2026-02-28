# Project 3

## Set up

1. Run 

```bash
 -F: '/cpu MHz/ {printf "%.2f GHz\n", $2/1000}' /proc/cpuinfo | uniq
 ```