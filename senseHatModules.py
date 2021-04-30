def helloMsg(message):
    from sense_emu import SenseHat
    sense = SenseHat()

    sense.show_message(message)

def getTemperature():
    from sense_emu import SenseHat
    sense = SenseHat()

    sense.clear()
    temperature = sense.get_temperature()

    return temperature

