import serial


# Reader, which read info from /dev/tnt1

def main():
    ser = serial.Serial('/dev/tnt1', baudrate=9600, stopbits=serial.STOPBITS_TWO)
    print('Ready to read message')

    while True:
        message = ''
        while ser.inWaiting() > 0:
            message += ser.read().decode('UTF-8')

        if message == 'exit':
            ser.close()
            exit()

        if message != '':
            if message[0] == '#':
                new_baudrate = int(message[1:])
                ser.baudrate = new_baudrate
                print(f'baud rate change successfully to {ser.baudrate}')
                continue
            print(f'tnt1 message: {message}')


if __name__ == '__main__':
    main()
