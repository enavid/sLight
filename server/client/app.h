const char appJS[] PROGMEM = R"=====(
const getItem = document.getElementById.bind(document);
const Illuminance = getItem("Illuminance");
const slider1 = getItem('slider1');
const slider2 = getItem('slider2');
const brightness = getItem('lamp-brightness');
const threshold = getItem('light-threshold');
const onButton = getItem('onButton');
const offButton = getItem('offButton');
const lampStatus = getItem('lamp-status');

// Get Sensor from NodeMCU server
setInterval(async function () {
    const urls = ['/light', '/status','/lightThreshold','/lightBrightness']
    const [light, status, thresholdValue, brightnessValue] = await Promise.all(urls.map(url =>
        fetch(url).then(resp => resp.json())
    ));
    
    Illuminance.innerHTML = "Illuminance = " + light.response + " lux";
    lampStatus.innerHTML = "Lamp-status = " + status.response;
    brightness.innerHTML = "Lamp-brightness = " + brightnessValue.response + " %";
    threshold.innerHTML = "Light-threshold = " + thresholdValue.response + " %";
    slider1.value = brightnessValue.response;
    slider2.value = thresholdValue.response;
}, 2000);

// Add Event listener to Button and send data to NodeMCU server
onButton.addEventListener('click', () => {
    fetch("?lamp=1", { mode: 'no-cors', method: 'POST' });
})
offButton.addEventListener('click', () => {
    fetch("?lamp=0", { mode: 'no-cors', method: 'POST' });
})

// Add event listener to element
slider1.addEventListener('input', () => {
    brightness.innerHTML = "Lamp-brightness = " + slider1.value + " %";
});

slider2.addEventListener('input', () => {
    threshold.innerHTML = "Light-threshold = " + slider2.value + " %";
});

// Send event listener data to NodeMCU server
slider1.addEventListener('change', () => {
    fetch("?brightness=" + slider1.value, { mode: 'no-cors', method: 'POST' });
});

slider2.addEventListener('change', () => {
    fetch("?threshold=" + slider2.value, { mode: 'no-cors', method: 'POST' });
});

)=====";
