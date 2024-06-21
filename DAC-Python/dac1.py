from pyfirmata2 import Arduino, util
import time
import adafruit_mcp4725 
import busio

board = Arduino('COM9')

# dac = board.get_pin('a:4:o')
print("Done1")
i2c = busio.I2C(board.get_pin('a:5:i'), board.get_pin('a:4:i'))
print("Done2")
dac = adafruit_mcp4725.MCP4725(i2c, address=0x60)  
print("Done3")
board.i2c_write(0x60, [64,0b11111111,0b11110000])
print("Done")
# while True:
    
#     voltage = float(input("Enter voltage(51=exit): "))
#     if (voltage<=5.0 and voltage>=0.0):
#         print("Voltage =" + str(voltage) + "V/n")
#         #dac.write[voltage]
#         dac.raw_value(voltage)
#         time.sleep(2)
#         print("Enter next voltage /n")
#     elif (voltage==51):
#         break
#     else:
#         print("Invalid input")

        