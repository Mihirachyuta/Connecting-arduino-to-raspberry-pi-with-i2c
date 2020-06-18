import smbus
import time

# for RPI version 1, use “bus = smbus.SMBus(0)”
bus = smbus.SMBus(1)

# This is the address we setup in the Arduino Program
address = 0x04
a=100
vib=0
t=0
h=0

def readNumber():
    number = bus.read_byte(address)
    # number = bus.read_byte_data(address, 1)
    return number
while True:    
    try:
        rep =bus.read_i2c_block_data(address,0)
        string = ""
        for i in range(0,12):
            string += chr(rep[i])
        try:
            string=string.split()
            if(t!=int(string[0])):
                t=int(string[0])
            if(h!=float(string[2])):
                h=float(string[2])
            if((int(string[1])-a)<0):
                continue
            else:
                vib=(int(string[1])-a)/2
            print("t=",string[0],"*c","vib=",vib,"/s","h=",string[2],"%",)
            a=int(string[1])
        except:
            print("split error")
    except:
        print("i2c error")
    
    time.sleep(1)
