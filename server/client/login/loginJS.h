const char loginJS[] PROGMEM = R"=====(
const get = document.getElementById.bind(document);
const button = get('login');
const user = get('username');
const pass = get('password');

button.addEventListener('click', async function (e) {
    e.preventDefault();
    const username = user.value;
    const password = pass.value;

    if (username === '' || password === '') return alert('Please Check your input');

    const result = await fetch('?password=' + password + '&' + 'username=' + username);
    if (result.status === 403) return alert('user or password is wron !');
    if (result.status === 200) window.location = result.url;
})
)=====";