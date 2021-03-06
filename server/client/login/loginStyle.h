const char loginStyle[] PROGMEM = R"=====(
body {
    display: flex;
    justify-content: center;
    align-content: center;
    align-items: center;
    font-family: Arial, Helvetica, sans-serif;
}

form {
    width: 35%;
    border: 3px solid #f1f1f1;
}

input[type=text],
input[type=password] {
    width: 100%;
    padding: 12px 20px;
    margin: 8px 0;
    display: inline-block;
    border: 1px solid #ccc;
    box-sizing: border-box;
}

button {
    background-color: #04AA6D;
    color: white;
    padding: 14px 20px;
    margin: 8px 0;
    border: none;
    cursor: pointer;
    width: 100%;
}

button:hover {
    opacity: 0.8;
}

.login {
    text-align: center;
    margin: 24px 0 12px 0;
    font-size: 2rem;
}

img.avatar {
    width: 40%;
    border-radius: 50%;
}

.container {
    padding: 16px;
}

span.psw {
    float: right;
    padding-top: 16px;
}
)=====";