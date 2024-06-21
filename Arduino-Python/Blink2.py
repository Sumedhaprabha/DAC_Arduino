from pyfirmata2 import Arduino, util
import time 

board = Arduino('COM9')
looptimes = input("How many times would you like the LED to blink?")
print("Blinking " + looptimes + " times")

for x in range(int(looptimes)):
    board.digital[13].write(1)
    time.sleep(1)
    board.digital[13].write(0)
    time.sleep(1)

# from pyfirmata2 import Arduino,util
# import serial
# import time

# # Initialize the board
# try:
#     board = Arduino('COM9')
# except Exception as e:
#     print(f"Error initializing the board: {e}")
#     exit()

# # Get the number of times to blink the LED
# looptimes = input("How many times would you like the LED to blink? ")

# try:
#     looptimes = int(looptimes)
# except ValueError:
#     print("Please enter a valid number.")
#     exit()

# print(f"Blinking {looptimes} times")

# # Blink the LED on pin 13
# for x in range(looptimes):
#     try:
#         board.digital[13].write(1)  # Turn the LED on
#         time.sleep(1)               # Wait for 1 second
#         board.digital[13].write(0)  # Turn the LED off
#         time.sleep(1)               # Wait for 1 second
#     except Exception as e:
#         print(f"Error during blinking: {e}")
#         break

# # Close the board connection
# board.exit()
# print("Blinking completed")
