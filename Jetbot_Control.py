import serial
from time import sleep

arduino = serial.Serial('/dev/ttyACM0', 115200, timeout=1)

while True:
    command = input()
    print(command)
    if command == 'q':
        arduino.write(b'0')
    if command == 'w':
        arduino.write(b'1')
    if command == 's':
        arduino.write(b'2')
    if command == 'd':
        arduino.write(b'3')
    if command == 'a':
        arduino.write(b'4')
