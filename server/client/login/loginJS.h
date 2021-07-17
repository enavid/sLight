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
    fetch('/', {
        method: 'POST',
        headers: {
            'Content-Type': 'text/plain',
            'Authorization': 'Basic ' + btoa(`${username}:${password}`)
        }
    }).then(res => {
        if (res.status === 403) return alert('user or password is wrong !');
        res.json();
        // location.href = res.url + 'main';
    }).then(res => console.log(res))
})
)=====";