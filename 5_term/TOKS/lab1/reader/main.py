import serial


# Reader, which read info from /dev/tnt1
def read(port: serial.Serial):
    while True:
        message = ''
        while port.inWaiting() > 0:
            message += port.read().decode('UTF-8')

        if message == 'exit':
            port.close()
            exit()

        if message != '':
            if message[0] == '#':
                new_baudrate = int(message[1:])
                port.baudrate = new_baudrate
                print(f'baud rate change successfully to {port.baudrate}')
                continue
            print(f'tnt1 message: {message}')


def main():
    ser = serial.Serial('/dev/tnt1', baudrate=9600, stopbits=serial.STOPBITS_TWO)
    print('Ready to read message')
    read(ser)


if __name__ == '__main__':
    main()
