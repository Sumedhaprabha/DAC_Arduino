
import busio
import adafruit_mcp4725
import time 
from pyfirmata2 import Arduino

board = Arduino('COM9')

# Create the I2C bus interface
print("Done1")
i2c = busio.I2C(board.SCL, board.SDA)

# Create the MCP4725 DAC object
print("Done2")
dac = adafruit_mcp4725.MCP4725(i2c, address=0x60)

# Function to set DAC voltage
def set_dac_voltage(voltage):
    # Voltage should be between 0 and 5V
    if 0 <= voltage <= 5:
        # Convert voltage to 12-bit value (0-4095)
        value = int((voltage / 5.0) * 4095)
        dac.value = value
        print(f"Setting DAC voltage to {voltage}V, value: {value}")
    else:
        print("Voltage out of range. It should be between 0 and 5V.")

# Test the DAC by sweeping the voltage from 0 to 5V
try:
    for voltage in range(0, 6):
        set_dac_voltage(voltage)
        time.sleep(1)  # wait for 1 second
finally:
    print("Finished")
