const char registerJS[] PROGMEM = R"=====(
const get = document.getElementById.bind(document);
const button = get('submit');
const user = get('username');
const pass = get('psw');
const confirmPass = get('confirm-psw');
const ssid = get('ssid');
const ssidPass = get('ssid-psw');

button.addEventListener('click', (e) => {
    e.preventDefault();
    const username = user.value;
    const password = pass.value;
    const confirmPassword = confirmPass.value;
    const ssidName = ssid.value;
    const ssidPassword = ssidPass.value;
    if (username === '' || password === '' || confirmPassword === '' || ssidName === '' || ssidPassword === '') return alert('Please Check your input');
    if (password !== confirmPassword) return alert('Your password dont match!');

    const url = location.href + 'setdata?' + `username=${username}&password=${password}&ssid=${ssidName}&ssidpass=${ssidPassword}`;

    fetch(url, {
        method: 'POST'
    }).then(res => {
        if (res.status === 202) return alert('Data set successfully!')
        else return alert('Try agin !');
    })
})
)=====";
