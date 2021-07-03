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
    const urls = ['/light', '/status']
    const [light, status] = await Promise.all(urls.map(url =>
        fetch(url).then(resp => resp.json())
    ));
    Illuminance.innerHTML = "Illuminance " + light.response + " lux";
    lampStatus.innerHTML = "Lamp-status = " + status.response;
}, 2000);

// Add Event listener to Button and send data to NodeMCU server
onButton.addEventListener('click', () => {
    fetch("?lamp=ON", { mode: 'no-cors', method: 'POST' });
})
offButton.addEventListener('click', () => {
    fetch("?lamp=OFF", { mode: 'no-cors', method: 'POST' });
})

// Add event listener to element
slider1.addEventListener('input', () => {
    brightness.innerHTML = "Light-brightness = " + slider1.value + " %";
});

slider2.addEventListener('input', () => {
    threshold.innerHTML = "Light-threshold = " + slider2.value + " %";
});

// Send event listener data to NodeMCU server
slider1.addEventListener('change', () => {
    fetch("?threshold=" + slider1.value, { mode: 'no-cors', method: 'POST' });
});

slider2.addEventListener('change', () => {
    fetch("?brightness=" + slider2.value, { mode: 'no-cors', method: 'POST' });
});

)=====";