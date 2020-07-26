#!/usr/bin/env python3

# AVR / Arduino dynamic memory log analyis script.
#
# Copyright 2014 Matthijs Kooijman <matthijs@stdin.nl>
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
# This script is intended to read raw packets (currently only 802.15.4
# packets prefixed by a length byte) from a serial port and output them
# in pcap format.

import os
import sys
import time
import errno
import struct
import datetime

class Formatter:
    def __init__(self, out):
        self.out = out
    def close(self):
        self.out.close()

class PcapFormatter(Formatter):
    def write_header(self):
        self.out.write(struct.pack("=IHHiIII",
            0xa1b2c3d4,   # magic number
            2,            # major version number
            4,            # minor version number
            0,            # GMT to local correction
            0,            # accuracy of timestamps
            65535,        # max length of captured packets, in octets
            147          # data link type (DLT) - IEEE 802.15.4
        ))
        self.out.flush()

    def write_packet(self, data):
        now = datetime.datetime.now()
        timestamp = int(time.mktime(now.timetuple()))
        self.out.write(struct.pack("=IIII",
            timestamp,        # timestamp seconds
            now.microsecond,  # timestamp microseconds
            len(data),        # number of octets of packet saved in file
            len(data),        # actual length of packet
        ))
        self.out.write(data)
        self.out.flush()
        
def main():
    #do_sniff_once()
    get_data()

def do_sniff_once(arry,counter):
    data = bytes(arry)
    out = PcapFormatter(open("test.pcap", 'ab'))
    if counter==1:
        out.write_header()
        out.write_packet(data)
    else:
        out.write_packet(data)
    out.close()

def get_data():
    try:
        fp = open('sampleData.txt', 'r')
        counter = 1;
        path = 'test.pcap'  
        if os.path.exists(path):
            print("remove")
            os.remove(path)

        for line in fp:
            arry = line.split()
            data = []
            for item in arry:
                if (item =="<" or item ==">"):
                    continue
                elif (item == "|"):
                    break
                else:
                    hexValue= "0x"+ item
                    data.append(int(hexValue, 16))
            do_sniff_once(data,counter)
            counter+=1
    finally:
        fp.close()

if __name__ == '__main__':
    main()
