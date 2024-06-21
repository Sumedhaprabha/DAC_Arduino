import serial.tools.list_ports

ports = serial.tools.list_ports.comports() #to get list of ports
serialInst = serial.Serial() #making instance of serial and to set communication as serial
portList = []

#To convert into readable format
for one in ports:
    portList.append(str(one))
    print(str(one))


com = input("Select Com Port for Arduino #:")
use = ""
#To check is valid com port is entered
for i in range(len(portList)):
    if portList[i].startswith("COM" + str(com)):
        use = "COM"+str(com)
        print(use)
    
#Setup
serialInst.baudrate = 9600
serialInst.port = use
serialInst.open()

while True:
    command = input("Enter Command (ON/OFF): ")
    serial.write(command.encode('utf-8'))

    if command == 'exit':
        exit()
