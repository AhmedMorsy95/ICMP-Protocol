# ICMP_Protocol

Implementation of ICMP protocol in C, Echo reply.

## Getting Started

These instruction will help you get the project running on your machine.

### Setting tap Interface

Tun/tap interfaces are a feature offered by Linux (and probably by other UNIX-like operating systems) that can do userspace networking,
that is, allow userspace programs to see raw network traffic (at the ethernet or IP level) and do whatever they like with it.

open the terminal and run these commands in sudo mode.

```
openvpn --mktun --dev tap1
ip link set tap1 up
ip addr add 10.0.0.1/24 dev tap1
ip link set tap1 up
```

### Runing the project

open src folder and run this command.

```
make && ./main
```

The project will start reading some IPv4 and IPv4 packets.

### testing the protocol using ping command

open another terminal and run this command.


```
ping 10.0.0.2
```

You can ping any address in the subnet 10.0.0.x except for x=1 (specified for the tap device).

