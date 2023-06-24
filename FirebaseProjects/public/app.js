// Database Paths
var dataBedroom1TemperaturePath = "bedroom1temperature";
var dataBedroom2TemperaturePath = "bedroom2temperature";
var dataBathroomTemperaturePath = "bathroomtemperature";
var dataKitchenTemperaturePath  = "kitchentemperature";

var dataBedroom1HumidityPath = "bedroom1humidity";
var dataBedroom2HumidityPath = "bedroom2humidity";
var dataBathroomHumidityPath = "bathroomhumidity";
var dataKitchenHumidityPath  = "kitchenhumidity";

var dataKitchenGasPath  = "kitchengas";



// Get a database reference 
const dataBedroom1TempReading = database.ref(dataBedroom1TemperaturePath);
const dataBedroom2TempReading = database.ref(dataBedroom2TemperaturePath);
const dataBathroomTempReading = database.ref(dataBathroomTemperaturePath);
const dataKitchenTempReading = database.ref(dataKitchenTemperaturePath);

const dataBedroom1HumReading = database.ref(dataBedroom1HumidityPath);
const dataBedroom2HumReading = database.ref(dataBedroom2HumidityPath);
const dataBathroomHumReading = database.ref(dataBathroomHumidityPath);
const dataKitchenHumReading = database.ref(dataKitchenHumidityPath);

const dataKitchenGasReading = database.ref(dataKitchenGasPath);




// Variables to save database current values
var floatBedroom1TempReading;
var floatBedroom2TempReading;
var floatBathroomTempReading;
var floatKitchenTempReading;

var floatBedroom1HumReading;
var floatBedroom2HumReading;
var floatBathroomHumReading;
var floatKitchenHumReading;

var floatKitchenGasReading;


// Attach an asynchronous callback to read the data

//KITCHEN

dataKitchenTempReading.on('value', (snapshot) => {
  floatKitchenTempReading = snapshot.val();
  console.log(floatKitchenTempReading);
  document.getElementById("kitchen-temp").innerHTML = floatKitchenTempReading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dataKitchenHumReading.on('value', (snapshot) => {
  floatKitchenHumReading = snapshot.val();
  console.log(floatKitchenHumReading);
  document.getElementById("kitchen-hum").innerHTML = floatKitchenHumReading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dataKitchenGasReading.on('value', (snapshot) => {
  floatKitchenGasReading = snapshot.val();
  console.log(floatKitchenGasReading);
  document.getElementById("kitchen-gas").innerHTML = floatKitchenGasReading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

//BEDROOM 1

dataBedroom1TempReading.on('value', (snapshot) => {
  floatBedroom1TempReading = snapshot.val();
  console.log(floatBedroom1TempReading);
  document.getElementById("bedroom1-temp").innerHTML = floatBedroom1TempReading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dataBedroom1HumReading.on('value', (snapshot) => {
  floatBedroom1HumReading = snapshot.val();
  console.log(floatBedroom1HumReading);
  document.getElementById("bedroom1-hum").innerHTML = floatBedroom1HumReading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

//BEDROOM 2

dataBedroom2TempReading.on('value', (snapshot) => {
  floatBedroom2TempReading = snapshot.val();
  console.log(floatBedroom2TempReading);
  document.getElementById("bedroom2-temp").innerHTML = floatBedroom2TempReading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dataBedroom2HumReading.on('value', (snapshot) => {
  floatBedroom2HumReading = snapshot.val();
  console.log(floatBedroom2HumReading);
  document.getElementById("bedroom2-hum").innerHTML = floatBedroom2HumReading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

//BATHROOM

dataBathroomTempReading.on('value', (snapshot) => {
  floatBathroomTempReading = snapshot.val();
  console.log(floatBathroomTempReading);
  document.getElementById("bathroom-temp").innerHTML = floatBathroomTempReading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dataBathroomHumReading.on('value', (snapshot) => {
  floatBathroomHumReading = snapshot.val();
  console.log(floatBathroomHumReading);
  document.getElementById("bathroom-hum").innerHTML = floatBathroomHumReading;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

