# SenseHat Functions
def sendMsg(message):
    from sense_hat import SenseHat
    sense = SenseHat()

    sense.show_message(message)
    
    return 1;

def getTemperature():
    from sense_hat import SenseHat
    sense = SenseHat()

    sense.clear()
    temperature = sense.get_temperature()

    return temperature

def getPressure():
    from sense_hat import SenseHat
    sense = SenseHat()
    
    sense.clear()
    pressure = sense.get_pressure()
    
    return pressure

def getHumidity():
    from sense_hat import SenseHat
    sense = SenseHat()
    
    sense.clear()
    humidity = sense.get_humidity()
    
    return humidity
# SenseHat Emulator Functions
def emu_sendMsg(message):
    from sense_emu import SenseHat
    sense = SenseHat()

    sense.show_message(message)
    
    return 1;

def emu_getTemperature():
    from sense_emu import SenseHat
    sense = SenseHat()

    sense.clear()
    temperature = sense.get_temperature()

    return temperature

def emu_getPressure():
    from sense_emu import SenseHat
    sense = SenseHat()
    
    sense.clear()
    pressure = sense.get_pressure()
    
    return pressure

def emu_getHumidity():
    from sense_emu import SenseHat
    sense = SenseHat()
    
    sense.clear()
    humidity = sense.get_humidity()
    
    return humidity
    


