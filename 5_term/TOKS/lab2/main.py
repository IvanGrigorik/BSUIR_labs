import serial

port1 = '/dev/tnt0'
port2 = '/dev/tnt1'


def change_baudrate(port: serial.Serial, new_baudrate: int):
    port.baudrate = new_baudrate
    print(f'baud rate change successfully to {port.baudrate}')


def encode_package(message: str) -> str:
    # Byte staffing
    start_byte = 'a'
    encode_message = ''
    encode_message += start_byte
    for char in message:
        if char == start_byte:
            encode_message += '*'
        encode_message += char

    return encode_message


def decode_package(message: str) -> str:
    # Byte staffing
    staffing_byte = message[0]
    decoded_message = ''
    for char in message[1:]:
        # If symbol is equal as start byte - just remove last string character
        if char == staffing_byte:
            decoded_message = decoded_message[:-1]
        decoded_message += char

    return decoded_message


def reader_routine(port: serial.Serial):
    print('Ready to read')
    while True:
        message = ''
        while port.inWaiting() > 0:
            message += port.read().decode('UTF-8')

        match message:
            case 'exit':
                port.close()
                exit(1)

            case '':
                continue

            case _:
                print(message)
                print(decode_package(message))


def writer_routine(port: serial.Serial):
    print('Ready to write')

    while True:
        message = input('> ')
        port.write(encode_package(message).encode('UTF-8'))


def main():
    choice = int(input('Do you want read or write (0/1)?'))
    match choice:
        case 0:
            port = serial.Serial(port1, 9600)
            reader_routine(port)
        case 1:
            port = serial.Serial(port2, 9600)
            writer_routine(port)


if __name__ == '__main__':
    main()
