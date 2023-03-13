#!/usr/bin/python3

import RPi.GPIO as GPIO
import sys
import serial
import time

# ESP32 GPIOs
# Valid for Unijoysticle2 A500
uni2_a500_gpios = {
    "j1": {
        "up": 26,
        "down": 18,
        "left": 19,
        "right": 23,
        "fire": 14,
        "pin5": 16,
        "pin9": 33,
    },
    "j2": {
        "up": 27,
        "down": 25,
        "left": 32,
        "right": 17,
        "fire": 13,
        "pin5": 22,
        "pin9": 21,
    },
    "leds": {
        "green": 5,
        "red": 12,
        "blue": 15,
    },
    "push_buttons": {
        "mode": 34,
        "swap": 35,
    },
}

# Valid for Unijoysticle2+
uni2_plus_gpios = {
    "j1": {
        "up": 26,
        "down": 18,
        "left": 19,
        "right": 23,
        "fire": 14,
        "pin5": 16,
        "pin9": 33,
    },
    "j2": {
        "up": 27,
        "down": 25,
        "left": 32,
        "right": 17,
        "fire": 13,
        "pin5": 22,
        "pin9": 21,
    },
    "leds": {
        "green": 5,
        "red": 12,
        # Not Blue LED
    },
    "push_buttons": {
        "mode": 34,
        # No swap button
    },
}


# RPi GPIOs
rpi_gpios = {
    "j1": {
        "up": 21,
        "down": 16,
        "left": 12,
        "right": 1,
        "fire": 20,
        "pin5": 8,  # Fire 3
        "pin9": 7,  # Fire 2
    },
    "j2": {
        "up": 11,
        "down": 24,
        "left": 23,
        "right": 18,
        "fire": 25,
        "pin5": 14,  # Fire 3
        "pin9": 15,  # Fire 2
    },
    "leds": {
        "green": 2,
        "red": 3,
    },
}


def esp32_set_gpio(ser, gpio: int, level: int) -> None:
    s = f"gpio_set {gpio} {level}\r\n"
    ser.write(bytes(s, "utf-8"))
    # Sending the command via Serial + time to for the ESP32 to process it
    # might take a few milliseconds.
    # This "wait" is kind of a "sync"
    time.sleep(0.1)


def esp32_get_gpio(ser, gpio: int) -> int:
    s = f"gpio_get {gpio}\r\n"
    ser.write(bytes(s, "utf-8"))

    # First line is Echo, ignore it
    _ = ser.readline()
    line = ser.readline()

    # Output should have this format:
    #   GPIO 26 = 0
    # Convert it to string, split it by ' ' so we'll have for entries:

    r = line.decode("utf-8")
    r.strip()
    _, number, _, lvl = r.split(" ")
    assert number == gpio
    return lvl


def setup_gpios():
    GPIO.setmode(GPIO.BCM)

    # LEDs are output
    # J1, J2 are input

    for k in rpi_gpios["leds"]:
        pin = rpi_gpios["leds"][k]
        GPIO.setup(pin, GPIO.OUT)
        GPIO.output(pin, GPIO.LOW)

    for k in rpi_gpios["j1"]:
        pin = rpi_gpios["j1"][k]
        GPIO.setup(pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)

    for k in rpi_gpios["j2"]:
        pin = rpi_gpios["j2"][k]
        GPIO.setup(pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)


def test_leds():
    green_pin = rpi_gpios["leds"]["green"]
    red_pin = rpi_gpios["leds"]["red"]

    print("Testing Green LED...")
    for _ in range(5):
        GPIO.output(green_pin, GPIO.HIGH)
        time.sleep(0.1)
        GPIO.output(green_pin, GPIO.LOW)
        time.sleep(0.1)

    print("Testing RED LED...")
    for _ in range(5):
        GPIO.output(red_pin, GPIO.HIGH)
        time.sleep(0.1)
        GPIO.output(red_pin, GPIO.LOW)
        time.sleep(0.1)


def test_pin(ser, port: str, pin: str) -> None:
    print(f"Testing {port}:{pin}")
    esp32_set_gpio(ser, uni2_a500_gpios[port][pin], 1)
    lvl = GPIO.input(rpi_gpios[port][pin])
    assert lvl == 0

    esp32_set_gpio(ser, uni2_a500_gpios[port][pin], 0)
    lvl = GPIO.input(rpi_gpios[port][pin])
    assert lvl == 1


def test_all_pins_except(ser, port: str, pin: str, level: int) -> None:
    """All must have level, except for port:pin"""
    ports = ["j1", "j2"]
    for port in ports:
        for pin in uni2_a500_gpios[port].keys():
            if pin == pin and port == port:
                continue
            lvl = GPIO.input(rpi_gpios[port][pin])
            assert lvl == level


def test_pin_alone(ser, port: str, pin: str) -> None:
    """Only port:pin must be asserted, the rest should be deasserted"""

    print(f"Testing alone {port}:{pin}")
    esp32_set_gpio(ser, uni2_a500_gpios[port][pin], 1)
    lvl = GPIO.input(rpi_gpios[port][pin])
    assert lvl == 0
    test_all_pins_except(ser, port, pin, 0)

    esp32_set_gpio(ser, uni2_a500_gpios[port][pin], 0)
    lvl = GPIO.input(rpi_gpios[port][pin])
    assert lvl == 1
    test_all_pins_except(ser, port, pin, 0)


def test_led(ser, port: str, pin: str) -> None:
    print(f"Testing {port}:{pin}")
    print("This is a visual test. LED should be blinking")

    for _ in range(5):
        esp32_set_gpio(ser, uni2_a500_gpios[port][pin], 0)
        time.sleep(0.1)
        esp32_set_gpio(ser, uni2_a500_gpios[port][pin], 1)
        time.sleep(0.1)


def main():
    ser = serial.Serial(sys.argv[1], 115200, timeout=1)
    print(ser.name)

    setup_gpios()
    test_leds()

    ports = ["j1", "j2"]
    for port in ports:
        for pin in uni2_a500_gpios[port].keys():
            test_pin(ser, port, pin)

    for port in ports:
        for pin in uni2_a500_gpios[port].keys():
            test_pin_alone(ser, port, pin)

    for pin in uni2_a500_gpios["leds"].keys():
        test_led(ser, "leds", pin)

    ser.close()
    GPIO.cleanup()


if __name__ == "__main__":
    exit(main())
