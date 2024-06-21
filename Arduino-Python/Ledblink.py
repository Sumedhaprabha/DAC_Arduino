import pyfirmata2
import time 

board = pyfirmata2.Arduino('COM9')
ledpin = board.get_pin('d:13:o')

while True:
    ledpin.write(1)
    time.sleep(1)
    ledpin.write(0)
    time.sleep(1)