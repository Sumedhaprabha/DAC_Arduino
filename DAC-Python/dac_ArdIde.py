import serial
import time

# Replace 'COM9' with the port your Arduino is connected to
try:
    ser = serial.Serial('COM9', 9600)
except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
    exit()

# Function to set DAC voltage
def set_dac_voltage(voltage):
    # Voltage should be between 0 and 5V
    if 0 <= voltage <= 5:
        value = int((voltage / 5.0) * 4095)
        ser.write(f"{value}\n".encode())
        print(f"Setting DAC voltage to {voltage}V, value: {value}")
    else:
        print("Voltage out of range. It should be between 0 and 5V.")

# Test the DAC by sweeping the voltage from 0 to 5V
try:
    for voltage in range(0, 6):
        set_dac_voltage(voltage)
        time.sleep(3)  # wait for 1 second
finally:
    ser.close()
    print("Finished")

