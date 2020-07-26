## Modbus RTU packets parser
This program can be used to parse hex format modbus RTU stream into PCAP format.
And the resulted pcap file can be analysed by wireshark.

## Achieve serial Port sniffing  
Combining with [interceptty](https://github.com/geoffmeyers/interceptty) we can get packets in pcap format wiche can be used by wireshark to analyse.

```code
sudo interceptty backdevice frontdevice | interceptty-nicedump
```

Feeding the output from above program into parser program will result the pcap file.
