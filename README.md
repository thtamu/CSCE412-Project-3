# Load Balancer

## Brief Overview


This is a C++ implementation of the Load Balancer. It helps manage requests coming in by assigning it to free servers, while also managing the queue and adjusting the number of servers to best handle the workload.

It operates by having new requests be automatically generated in the background and whenever the Load Balancer sees them, it checks for server availability. Available servers take the requests, but some requests enter the queue. The LoadBalancer dynamically creates and destroys servers based on its needs. The requests are randomly generated, and so is the frequency at which they come in.

## GitHub

[View the code on GitHub](https://github.com/thtamu/CSCE412-Project-3/)