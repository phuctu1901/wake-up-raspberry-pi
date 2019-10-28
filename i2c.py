# Raspberry Pi to Arduino I2C Communication 
# Python Code 
 
import smbus
def ConvertStringToBytes(src): 
    converted = [] 
    for b in src: 
        converted.append(ord(b))
    print(converted)
    return converted
 
# Slave Addresses for Arduinos 
ARDUINO_1_ADDRESS = 0x09 # I2C Address of Arduino 1 
 # I2C Address of Arduino 3 
 
# Create the I2C bus 
I2Cbus = smbus.SMBus(1) 
 

value = input("Value to send: ") 

 
# also quit if you messed up
print(value)
#if bSelect != "on" or bSelect != "off": quit() 
 
BytesToSend = ConvertStringToBytes(value) 
I2Cbus.write_i2c_block_data(0x09, 0x00, BytesToSend) 
print("Sent " + "0x09" + " the " + value + " command.") 
 
# This function converts a string to an array of bytes. 

