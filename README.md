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

(start python using `python -m asyncio` to use await)
```python
from bleak import BleakScanner
from bleak import BleakClient

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

## Upload a new images

First you need a bmp image in 135x240.

```python
# Init the upload for the number 0
await client.write_gatt_char("c2285d2f-44c5-4abb-af86-9d159f351081", "/0.bmp".encode(), response=True)

with open(f"data/0.bmp", 'rb') as f:
    bytes = f.read(512)
    while bytes:
        await client.write_gatt_char("c2285d2f-44c5-4abb-af86-9d159f351082",
                                    len(bytes).to_bytes(2, byteorder='big') + bytes, response=True)
        bytes = f.read(512)

await client.write_gatt_char("c2285d2f-44c5-4abb-af86-9d159f351083", b'close', response=True)
```

## Set wifi credentials

```python
await client.write_gatt_char("c1eac326-9ded-4148-90c1-6289cdbf5103", "ssid;password".encode(), response=True)
```