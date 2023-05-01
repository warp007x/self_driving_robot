import serial
import io
import time
import re

class mySerial:
    def __init__(self, port, baud_rate):
        self.serial = serial.Serial(port, baud_rate, timeout=0)
        self.serial_io_wrapped = io.TextIOWrapper(io.BufferedRWPair(self.serial, self.serial))

    # receive message via serial
    def read(self):
        read_out = None
        if self.serial.in_waiting > 0:
            read_out = self.serial_io_wrapped.readline()
            # time.sleep(0.01)
        return read_out

    # send message via serial
    def write(self, message):
        self.serial.write(message)

    # flush the buffer
    def flush(self):
        self.serial.flush()



def main():
    ser.flush()
    # ser.write(str(commandToSend).encode() + b"\t" + b"\n")
    # time.sleep(1)

    # for i in range(600) :
    #     ser.write(str(commandToSend).encode() + b"\n")
    #     incomingMessage = ser.read()
    #     time.sleep(0.1)
    #     if incomingMessage is not None:
    #         print(incomingMessage + "\t")
    #         ser.flush()
    channels = []
    for i in range(60) :
        ser.write(str(commandToSend).encode() + b"\n")
        incomingMessage = ser.read()
        time.sleep(0.1)
        if incomingMessage is not None:
            substr=re.split(r":",incomingMessage)
            newsubstr=[]
            for ele in substr:
                ele=ele.replace("\n","")
                newsubstr.append(ele)
            channels.append(newsubstr)
            print(incomingMessage + "\t")
            ser.flush()

    for ch in channels:
        print(ch)


if __name__ == '__main__':
    commandToSend = input("Enter CHANNEL values: ")
    ser = mySerial('COM8', 115200)
    main()
