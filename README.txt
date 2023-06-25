GitHub repo: https://github.com/Doominsky/home_monitoring_project

RO

Conditii:

Arduino IDE:

Instalati urmatoarele biblioteci Arduino: WiFi, Adafruit ESP8266, Adafruit Unified Sensor, DHT sensor Library, Firebase Arduino Client Library for ESP8266 and ESP32, pachetul standard ESP8266
(Pentru instalarea librariilor, in arduino IDE, navigati la Tools -> Manage Libraries -> Tastati fiecare librarie mentionata si apasati Install. Pentru pachetul standard ESP8266, navigati in File -> Preferences -> Additional Boards Manager URLs: introduceti: https://dl.espressif.com/dl/package_esp32_index.json,http://arduino.esp8266.com/stable/package_esp8266com_index.json)

Pycharm:

Instalati urmatoarele module: pandas, serial.tools.list_ports, matplot.pyplot, xlwings, pydrive.auth, pydrive.drive
Pentru instalarea acestor module, navigați în File -> Settings -> Python interpreter -> Add (semnul plus) -> introduceti fiecare librarie

Etape pentru utilizarea proiectului:

1. In codul Arduino pentru NodeMCU, parametrii de WiFi trebuie schimbati cu reteaua proprie WiFi, si variabila broadcast_address trebuie schimbata cu adresa MAC a dispozitivulul NodeMCU central propriu
2. Urmariti acest videoclip pentru a seta Google API: https://www.youtube.com/watch?v=rGTIJ0yvlQA
3. Pe langa fisierul main.py de tip Python, va fi nevoie si de un fisier client_secret.json care va contine parametrii contului d-voastra de Google Drive
4. In codul de Python, linia 98 si 212, trebuie schimbata calea de salvare, cu o cale valida aferenta dispozitivului d-voastra de calcul 
5. La linia 218, trebuie schimbat parametrul folder-ului destinatie pentru Google Drive
6. La linia 28 din codul Python, trebuie schimbat port-ul in caz ca nu este COM5
7. Conectati dispozitivul cu Arduino la un port USB
8. Asigurati-va ca sistemul este conectat la internet prin Firebase (datele se vor schimba atat in website, cat si in baza de date)
9. Porniti script-ul
10. Introduceti un numar de minute pentru interogare (numar intreg)
11. Veti primi o copie Excel a interogarii in stocarea dispozitivului de calcul, si o copie in cadrul contului Google

EN

Prerequisites:

Arduino IDE:

Install the following Arduino libraries: WiFi, Adafruit ESP8266, Adafruit Unified Sensor, DHT sensor Library, Firebase Arduino Client Library for ESP8266 and ESP32, ESP8266 standard package
(To install the libraries, in the Arduino IDE, navigate to Tools -> Manage Libraries -> Type each library mentioned and click Install. For the standard ESP8266 package, navigate to File -> Preferences -> Additional Boards Manager URLs: enter: https://dl.espressif.com/dl/package_esp32_index.json,http://arduino.esp8266.com/stable/package_esp8266com_index.json)

Pycharm:

Install the following modules: pandas, serial.tools.list_ports, matplot.pyplot, xlwings, pydrive.auth, pydrive.drive
To install these modules, navigate to File -> Settings -> Python interpreter -> Add (plus sign) -> enter each library

Steps for using the project:

1. In the Arduino code for the NodeMCU, the WiFi parameters must be changed to the own WiFi network, and the broadcast_address variable must be changed to the MAC address of the own central NodeMCU device.
2. Watch this video to set up the Google API: https://www.youtube.com/watch?v=rGTIJ0yvlQA
3. In addition to the Python main.py file, you will also need a client_secret.json file that will contain the parameters of your Google Drive account.
4. In the Python code, line 98 and 212, you must change the save path to a valid path for your computing device 
5. The Google Drive destination folder must be changed in line 218
6. At line 28 in the Python code, the port must be changed in case it's not COM5
7. Connect your Arduino device to a USB port
8. Make sure the system is connected to the internet via Firebase (data will change both in the website and in the database)
9. Start the script
10. Enter a number of minutes for the query (integer)
11. You will receive an Excel copy of the query in your computing device storage, and a copy in your Google account