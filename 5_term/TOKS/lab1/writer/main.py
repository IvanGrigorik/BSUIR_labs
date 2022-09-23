import serial

def write(port: serial.Serial):
    while True:
        message = input('>> ')

        # If we want to change speed of ports
        if message == 'ch':
            port_number = int(input('Enter which port speed you want to change (0/1): '))
            new_baudrate = 0
            while new_baudrate not in serial.Serial.BAUDRATES and new_baudrate >= 115200:
                new_baudrate = int(input('Enter new port speed: '))

            match port_number:
                case 0:
                    port.baudrate = new_baudrate
                    print(f'baud rate change successfully to {port.baudrate}')
                case 1:
                    port.write(f'#{str(new_baudrate)}'.encode())
            continue
        # Normal program output
        port.write(message.encode())

        # end of program
        if message == 'exit':
            port.close()
            exit()

# Writer, which write information to /dev/tnt0
def main():
    ser = serial.Serial('/dev/tnt0', baudrate=9600, stopbits=serial.STOPBITS_TWO)
    print('Port ready write message')

    baudrate_table = [50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800, 2400,
                      4800, 9600, 19200, 28800, 38400, 57600, 76800, 115200]




if __name__ == '__main__':
    main()
