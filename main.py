import sqlite3
import time
import serial

conn = sqlite3.connect('mydatabase.db')

# data = "DA AF DC 73"
# timestamp = time.time()

# conn.execute('''INSERT INTO serial_data (timestamp, data)
#                  VALUES (?, ?)''', (timestamp, data))
# conn.commit()
# cursor = conn.execute('''SELECT * FROM serial_data''')
# conn.commit()
# for row in cursor:
#     print(row)


#read from serial port

# set the port and baud rate to match that of your Arduino
ser = serial.Serial('COM13', 9600)

# read data from serial
while True:
    line = ser.readline().decode('utf-8').strip()

    if line != "Found" and line != "Not Found":
        print("UID: " , line)
        query = conn.execute('''SELECT data FROM serial_data WHERE data = ? LIMIT 1''', (str(line),))
        data = query.fetchone()

        if data is not None:
            print("Data: ", data)

            ser.write(b'Found\n')
        else:
            print("No data found")
            ser.write(b'Not Found\n')




