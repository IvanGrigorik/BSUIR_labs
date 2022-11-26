#!/usr/bin/env python3

import random
import time

RED = "\x1b[31m"
GREEN = "\x1b[32m"
YELLOW = "\x1b[33m"
WHITE = "\x1b[37m"


class Transmitter:
    # Private members
    __try_counter = 0
    __propagation_time = 1
    __transmission_time = 2 * __propagation_time

    # Public class methods
    @staticmethod
    def send_message(message: str):
        print(f"Sent message: \"{message}\"")
        Receiver.get_transmitter_message(message)

    @staticmethod
    def send_jam():
        print(f"{RED}Jam signal{WHITE}")

    @classmethod
    def wait_transmission_time(cls):
        time.sleep(cls.__transmission_time)

    @classmethod
    def increment_try_counter(cls):
        cls.__try_counter += 1
        print(f"{YELLOW}Try counter: {cls.__try_counter}{WHITE}")

    @classmethod
    def random_delay(cls):
        time_to_wait = random.randint(0, 2 ** cls.__try_counter)
        print(f"{YELLOW}Generated random delay from {0, 2 ** cls.__try_counter}: {time_to_wait}")
        print(f"Wait {time_to_wait}s...{WHITE}")
        time.sleep(time_to_wait)

    @classmethod
    def is_try_max(cls) -> bool:
        return cls.__try_counter > 10

    @classmethod
    def clear_try_counter(cls):
        cls.__try_counter = 0


class Receiver:
    # Private members
    __is_collision = False
    __message = ""

    @classmethod
    def get_transmitter_message(cls, message: str):
        cls.__message = message

    @classmethod
    def is_collision(cls) -> bool:
        cls.__is_collision = random.choice([True, False])
        return cls.__is_collision

    @classmethod
    def get_message(cls) -> str:
        return cls.__message


def main():
    while True:
        message = input("\nEnter message (exit to leave)\n>> ")
        if message == "exit":
            break
        Transmitter.clear_try_counter()

        Transmitter.send_message(message)

        while Receiver.is_collision():
            Transmitter.send_jam()
            Transmitter.wait_transmission_time()

            Transmitter.increment_try_counter()
            if Transmitter.is_try_max():
                print(f"{RED}Too many tries{WHITE}")
                break

            Transmitter.random_delay()

        message = Receiver.get_message()
        print(f"{GREEN}Message: {message}{WHITE}")


if __name__ == '__main__':
    main()
