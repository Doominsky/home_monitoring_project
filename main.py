import pandas as pd
import serial.tools.list_ports
import matplotlib.pyplot as plt
import xlwings as xw
from pydrive.auth import GoogleAuth
from pydrive.drive import GoogleDrive

ports = serial.tools.list_ports.comports()
serial_instance = serial.Serial()

time_array = []
temps_gateway = []
hums_gateway = []
gases_gateway = []
temps_D98F = []
hums_D98F = []
temps_A942 = []
hums_A942 = []
temps_15B5 = []
hums_15B5 = []

port_list = []

for port in ports:
    port_list.append(port)
    print(str(port))

port_variable = "COM5"

serial_instance.baudrate = 115200
serial_instance.port = port_variable
serial_instance.open()
counter = 0
xvalue = 0

SA = int(input("Introduce the time amount (min): "))
# time.sleep(5)
TA = SA * 2

while counter < TA:
    if serial_instance.in_waiting:
        packet_temp_gateway = serial_instance.readline()
        decoded_values_temp_gateway = str(packet_temp_gateway[0:len(packet_temp_gateway)].decode('utf'))
        packet_hum_gateway = serial_instance.readline()
        decoded_values_hum_gateway = str(packet_hum_gateway[0:len(packet_hum_gateway)].decode('utf'))
        packet_gas_gateway = serial_instance.readline()
        decoded_values_gas_gateway = str(packet_gas_gateway[0:len(packet_gas_gateway)].decode('utf'))
        # D98F
        packet_temp_D98F = serial_instance.readline()
        decoded_values_temp_D98F = str(packet_temp_D98F[0:len(packet_temp_D98F)].decode('utf'))
        packet_hum_D98F = serial_instance.readline()
        decoded_values_hum_D98F = str(packet_hum_D98F[0:len(packet_hum_D98F)].decode('utf'))
        # A942
        packet_temp_A942 = serial_instance.readline()
        decoded_values_temp_A942 = str(packet_temp_A942[0:len(packet_temp_A942)].decode('utf'))
        packet_hum_A942 = serial_instance.readline()
        decoded_values_hum_A942 = str(packet_hum_A942[0:len(packet_hum_A942)].decode('utf'))
        # 15B5
        packet_temp_15B5 = serial_instance.readline()
        decoded_values_temp_15B5 = str(packet_temp_15B5[0:len(packet_temp_15B5)].decode('utf'))
        packet_hum_15B5 = serial_instance.readline()
        decoded_values_hum_15B5 = str(packet_hum_15B5[0:len(packet_hum_15B5)].decode('utf'))

        time_array.append(xvalue)
        temps_gateway.append(float(decoded_values_temp_gateway.rstrip("\n")))
        hums_gateway.append(float(decoded_values_hum_gateway.rstrip("\n")))
        gases_gateway.append(float(decoded_values_gas_gateway.rstrip("\n")))
        temps_D98F.append(float(decoded_values_temp_D98F.rstrip("\n")))
        hums_D98F.append(float(decoded_values_hum_D98F.rstrip("\n")))
        temps_A942.append(float(decoded_values_temp_A942.rstrip("\n")))
        hums_A942.append(float(decoded_values_hum_A942.rstrip("\n")))
        temps_15B5.append(float(decoded_values_temp_15B5.rstrip("\n")))
        hums_15B5.append(float(decoded_values_hum_15B5.rstrip("\n")))
        xvalue += 0.5
        counter += 1

        print(str(packet_temp_gateway) + " | " + str(packet_hum_gateway) + " | " +
              str(packet_gas_gateway) + " | " + str(packet_temp_D98F) + " | " + str(packet_hum_D98F) + " | " +
              str(packet_temp_A942) + " | " + str(packet_hum_A942) + " | " + str(packet_temp_15B5) + " | " +
              str(packet_hum_15B5))

        print(str(float(decoded_values_temp_gateway.rstrip("\n"))) + " | " +
              str(float(decoded_values_hum_gateway.rstrip("\n"))) + " | " + str(
            float(decoded_values_gas_gateway.rstrip("\n"))) +
              " | " + str(float(decoded_values_temp_D98F.rstrip("\n"))) + " | " + str(
            float(decoded_values_hum_D98F.rstrip("\n"))) +
              " | " + str(float(decoded_values_temp_A942.rstrip("\n"))) + " | " + str(
            float(decoded_values_hum_A942.rstrip("\n"))) +
              " | " + str(float(decoded_values_temp_15B5.rstrip("\n"))) + " | " + str(
            float(decoded_values_hum_15B5.rstrip("\n"))))

data_all_gateway = [temps_gateway, hums_gateway, gases_gateway]
data_frame_gateway = pd.DataFrame(data_all_gateway)
data_all_D98F = [temps_D98F, hums_D98F]
data_all_A942 = [temps_A942, hums_A942]
data_all_15B5 = [temps_15B5, hums_15B5]

data_frame_gateway.to_excel('C:\\Users\\Andrei\\Contacts\\Desktop\\Test_excel\\Data.xlsx',
                            sheet_name="Data")  # MUST CHANGE WITH YOUR DESKTOP OR FAVORITE FOLDER PATH

time_list = []
for i in range(0, int(TA)):
    time_list.append(i / 2)

wb = xw.Book()
sht_gateway = wb.sheets[0]
# sht_D98F = wb.sheets[0]
sht_A942 = wb.sheets[1]
sht_15B5 = wb.sheets[2]

sht_gateway.name = "K&B1"
# sht_D98F.name = "Bedroom 1"
sht_A942.name = "Bedroom 2"
sht_15B5.name = "Bathroom"

# GATEWAY
fig_temp_gateway = plt.figure()
x = time_list
y = temps_gateway
plt.plot(x, y)
plt.grid(False)
plt.title("Temperature Kitchen")
plt.xlabel("Time (min)")
plt.ylabel("Temperature (C)")
sht_gateway.pictures.add(fig_temp_gateway, name="Temperature test Kitchen", update=False,
                         left=sht_gateway.range("A1").left, top=sht_gateway.range("A1").top, height=230,
                         width=250)
fig_hums_gateway = plt.figure()
y = hums_gateway
plt.plot(x, y)
plt.title("Humidity Kitchen")
plt.xlabel("Time (min)")
plt.ylabel("Humidity (%)")
sht_gateway.pictures.add(fig_hums_gateway, name="Humidity test Kitchen", update=False,
                         left=sht_gateway.range("G1").left, top=sht_gateway.range("G1").top, height=230,
                         width=250)
fig_gases_gateway = plt.figure()
y = gases_gateway
plt.plot(x, y)
plt.title("Gas Kitchen")
plt.xlabel("Time (min)")
plt.ylabel("Gas Concentration (%)")
sht_gateway.pictures.add(fig_gases_gateway, name="Gas test Kitchen", update=False,
                         left=sht_gateway.range("M1").left, top=sht_gateway.range("M1").top, height=230,
                         width=250)

# D98F
fig_temp_D98F = plt.figure()
y = temps_D98F
plt.plot(x, y)
plt.grid(False)
plt.title("Temperature Bedroom 1")
plt.xlabel("Time (min)")
plt.ylabel("Temperature (C)")
sht_gateway.pictures.add(fig_temp_D98F, name="Temperature test Bedroom 1", update=False,
                         left=sht_gateway.range("A20").left, top=sht_gateway.range("A20").top, height=230,
                         width=250)
fig_hums_D98F = plt.figure()
y = hums_D98F
plt.plot(x, y)
plt.title("Humidity Bedroom 1")
plt.xlabel("Time (min)")
plt.ylabel("Humidity (%)")
sht_gateway.pictures.add(fig_hums_D98F, name="Humidity test Bedroom 1", update=False,
                         left=sht_gateway.range("G20").left, top=sht_gateway.range("G20").top, height=230,
                         width=250)

# A942
fig_temp_A942 = plt.figure()
y = temps_A942
plt.plot(x, y)
plt.grid(False)
plt.title("Temperature Bedroom 2")
plt.xlabel("Time (min)")
plt.ylabel("Temperature (C)")
sht_A942.pictures.add(fig_temp_A942, name="Temperature test Bedroom 2", update=False,
                      left=sht_A942.range("A1").left, top=sht_A942.range("A1").top, height=230,
                      width=250)
fig_hums_A942 = plt.figure()
y = hums_A942
plt.plot(x, y)
plt.title("Humidity Bedroom 2")
plt.xlabel("Time (min)")
plt.ylabel("Humidity (%)")
sht_A942.pictures.add(fig_hums_A942, name="Humidity test Bedroom 2", update=False,
                      left=sht_A942.range("G1").left, top=sht_A942.range("G1").top, height=230,
                      width=250)

# 15B5
fig_temp_15B5 = plt.figure()
y = temps_15B5
plt.plot(x, y)
plt.grid(False)
plt.title("Temperature Bathroom")
plt.xlabel("Time (min)")
plt.ylabel("Temperature (C)")
sht_15B5.pictures.add(fig_temp_15B5, name="Temperature test Bathroom", update=False,
                      left=sht_15B5.range("A1").left, top=sht_15B5.range("A1").top, height=230,
                      width=250)
fig_hums_15B5 = plt.figure()
y = hums_15B5
plt.plot(x, y)
plt.title("Humidity Bathroom")
plt.xlabel("Time (min)")
plt.ylabel("Humidity (%)")
sht_15B5.pictures.add(fig_hums_15B5, name="Humidity test Bathroom", update=False,
                      left=sht_15B5.range("G1").left, top=sht_15B5.range("G1").top, height=230,
                      width=250)

# SAVE CONTENT

wb.save(path='C:\\Users\\Andrei\\Contacts\\Desktop\\Test_excel\\Data_Chart.xlsx')

gauth = GoogleAuth()
drive = GoogleDrive(gauth)

upload_file = 'C:\\Users\\Andrei\\Contacts\\Desktop\\Test_excel\\Data_Chart.xlsx'
gfile = drive.CreateFile({'parents': [{'id': '1xOLjqpaCZMZsuhe9yB5kyre-Oa1RiApq'}]})
gfile.SetContentFile(upload_file)
gfile.Upload()
print(temps_gateway)
print(hums_gateway)
print(gases_gateway)
print(temps_D98F)
print(hums_D98F)
print(temps_A942)
print(hums_A942)
print(temps_15B5)
print(hums_15B5)
