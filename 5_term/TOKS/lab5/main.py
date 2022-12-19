#!/usr/bin/env python3
import random
import sys
import time

import serial

# definition global constants
RED = "\x1b[31m"
GREEN = "\x1b[32m"
YELLOW = "\x1b[33m"
WHITE = "\x1b[37m"
PORT_PATH = "/dev/tnt"
PAYLOAD_LEN = 8


def main():
    if len(sys.argv) != 2 or int(sys.argv[1]) > 3:
        print(f"{RED}Error. Need to pass station number (0-3){WHITE}")
        exit(-1)

    match sys.argv[1]:
        case "0":
            writer_file = PORT_PATH + "0"
            reader_file = PORT_PATH + "5"
        case "1":
            writer_file = PORT_PATH + "2"
            reader_file = PORT_PATH + "1"
        case "2":
            writer_file = PORT_PATH + "4"
            reader_file = PORT_PATH + '3'

    have_token = True if sys.argv[1] == '0' else False
    station_address = ' '.join(format(ord(x), '01b') for x in sys.argv[1])[4:]

    receiver_data = ''
    transmitter_data = ''
    message_queue = list()

    print(f"Writer port: {writer_file}")
    print(f"Reader port: {reader_file}")
    port_writer = serial.Serial(writer_file)
    port_reader = serial.Serial(reader_file)

    for x in range (10):
        # Generate own message with 10% chance
        # message structure:
        #   SFS: PPP_T_RRR
        #   FCS: DA_SA_INFO8BIT
        #   EFS: A_C
        if random.randint(1, 10) == 7:
            sfs = generate_data(3) + '1' + generate_data(3)
            fcs = generate_source_address(station_address) + station_address + \
                  generate_data(PAYLOAD_LEN)
            efs = "00"
            station_message = sfs + fcs + efs
            print(f"{YELLOW}Generated message: {WHITE}{station_message}")
            message_queue.append(station_message)

        priority = message_queue[0][0:3] if len(message_queue) != 0 else "000"

        # Check for token
        if len(receiver_data) > 0:
            if receiver_data[3] == '0':
                have_token = True
        if len(receiver_data) > 0:
            max_priority = format(max(int(priority, 2),
                                      int(receiver_data[4:7], 2)), "b").zfill(3)

        # Send messages
        if have_token:
            message = ''
            if len(message_queue) > 0:


                if len(receiver_data) == 0:
                    message = message_queue[0][0:4] + "000" + message_queue[0][
                                                              7:21]

                    message_queue.remove(message_queue[0])
                    print(f"{YELLOW}Send message from queue: {WHITE}{message}")
                    port_writer.write(message.encode("windows-1251"))

                elif int(priority) > int(receiver_data[0:3]):
                    message = message_queue[0][0:4] + max_priority + \
                              message_queue[0][7:21]

                    message_queue.remove(message_queue[0])
                    print(f"{YELLOW}Send message from queue: {WHITE}{message}")
                    port_writer.write(message.encode("windows-1251"))

                # Send message

            else:
                print(f"{RED}Must send token{WHITE}")
                if receiver_data == "":
                    message = "000" + "0" + priority
                else:
                    message = receiver_data[0:3] + "0" + receiver_data[4:7]
                port_writer.write(message.encode("windows-1251"))
                have_token = False

        elif receiver_data != '':
            print(max_priority)
            message = receiver_data[0:4] + max_priority + receiver_data[
                                                          7:21]
            print(f"{YELLOW}Send own message: {WHITE}{message}")
            port_writer.write(message.encode("windows-1251"))

        # Read message
        receiver_data = ''
        while port_reader.inWaiting():
            receiver_data = receiver_data + port_reader.read().decode(
                "windows-1251")

        if receiver_data != '':
            if receiver_data[3] == '0':
                print(f"{GREEN}Got token!{WHITE}")
            else:
                if receiver_data[7:9] == station_address:
                    print(f"{GREEN}Got message for me: {WHITE}{receiver_data}")
                    receiver_data = receiver_data[0:19]
                elif receiver_data[9:11] == station_address and \
                        receiver_data[20:21] == "11":
                    print(f"{GREEN}Got old message: {WHITE}{receiver_data}")
                    receiver_data = ''
                else:
                    print(f"Got message: {receiver_data}")
        time.sleep(1)


def generate_data(data_len: int) -> str:
    data = ''
    for x in range(data_len):
        data += str(random.randint(0, 1))
    return data


def generate_source_address(own_address: str) -> str:
    generated_address = own_address
    while generated_address == own_address or generated_address == "11":
        generated_address = generate_data(2)
    return generated_address


if __name__ == '__main__':
    main()
