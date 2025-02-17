# Application for gathering statistics about network traffic

## NAME
**isa-top** — show transfer speeds for currently communicating connections

## SYNOPSIS
```sh
isa-top -i <interface> [-s <b|p>] [-t <seconds>] [-h] [-l]
```

## DESCRIPTION

isa-top shows transfer speeds in human-readable format for individual communicating IP addresses.
The program uses the libpcap library to capture packets from a network interface, which requires root privileges.
The connections are stored in a map, including information about the number of bytes transferred in the last interval.
Connections are displayed using the ncurses library and updated at a given refresh interval.
The program will not display more than 10 active connections at a time.

## OPTIONS
`-i <interface>`
Specify the network interface on which packets will be captured. This option is mandatory.
Examples of interfaces: eth0, wlan0.
If you are unsure about available interfaces, use the -h option to list them.

`-s <b|p>`
Specify the parameter based on which the connections will be sorted.
When not specified, connections are sorted by the number of bytes transferred in the last interval.

    - b — Sort by the number of bytes transferred in the last interval.
    - p — Sort by the number of packets transferred in the last interval.

`-t <seconds>`
Specify the refresh interval in seconds. When not specified, the default value is 1 second.

`-h`
Show the usage message of the program.

`-l`
List all available network interfaces

## EXAMPLES
Run `isa-top` on the `eth0` interface and sort connections by packets transferred:
```sh
isa-top -i eth0 -s p
```

Run `isa-top` and list all available network interfaces:
```sh
isa-top -l
```
Run `isa-top` on the loopback interface and set the refresh interval to 2 seconds:
```sh
isa-top -i lo -t 2
```
