# Nixie-clock
 
This arduino project is a custom firmware for the [EleksTube IPS Nixie Tube Digital Clock](https://elekstube.com/products/elekstube-ips-rgb-digital-clock-imitate-nixie-tubes-clock-6-digit-lcd-proposal-mode-custom-style-best-boyfriend-gift-shelf-clock).

This repository take some code from the [frankcohen/EleksTubeIPSHack](https://github.com/frankcohen/EleksTubeIPSHack) repository.

This project provide a simple base splitting the different components of the clock:
- Back Lights
- Bluetooth (BLE)
- Wifi
- Buttons
- Screens
- Time 
- Files (LITTLEFS)

Each componenent can call the others using the Clock instance.

# Bluetooth (BLE)

The current implementation provides some simple example of the bluetooth implementation. (Not used in the original clock.)

A class can extends the **BluetoothService** class, it abstract the interaction with the BLEManager class.

Here is a simple example to turn on/off the back lights with python

```python
# Get the device
device = [device for device in await BleakScanner.discover() if device.name == "Clock Service"]
assert len(device) == 1

# Create BleakClient
client = BleakClient(device[0].address)

# Connect
assert await client.connect()

# Send 0 value to address POWER_UUID
await client.write_gatt_char("bb5e995d-5863-4aa1-bafe-0e6a9fd4aa71", b'\x00', response=True)
```