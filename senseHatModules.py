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

def getPressure():
    from sense_emu import SenseHat
    sense = SenseHat()
    
    sense.clear()
    pressure = sense.get_pressure()
    
    return pressure

def getHumidity():
    from sense_emu import SenseHat
    sense = SenseHat()
    
    sense.clear()
    humidity = sense.get_humidity()
    
    return humidity

