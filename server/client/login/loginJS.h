const char loginJS[] PROGMEM = R"=====(
const get = document.getElementById.bind(document);
const button = get('login');
const user = get('username');
const pass = get('password');
const na = get('test');

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
        //location.href = res.url + `?username=${username}&password=${password}`;
        //console.log(res.url + `?username=${username}&password=${password}`);
        location.href = '/';
    })
})
)=====";