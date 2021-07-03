const char stylePage[] PROGMEM = R"=====(
* {
    box-sizing: border-box;
    margin: 0;
    padding: 0;
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
}

body {
    display: flex;
    flex-direction: column;
    justify-content: space-evenly
}

header {
    width: 100vw;
    height: 15vh;
    background-color: #009cde;
}

main {
    display: flex;
    flex-direction: column;
    width: 100vw;
    height: 70vh;
    background-color: #f4f4f4;
}

section {
    display: flex;
    flex-direction: column;
}

#first-section {
    height: 30%;
}

#information {
    display: flex;
    font-weight: bold;
    justify-content: center;
    padding: 10px;
}

#light-information {
    height: 100%;
    display: flex;
    justify-content: space-evenly;
    align-items: center;
}

.info-1 {
    display: flex;
    flex-direction: column;
}

.info-2 {
    display: flex;
    flex-direction: column;
}

#light-information p {
    padding: 10px;
}

#second-section {
    height: 70%;
}

button {
    background-color: #4c6ca0;
    color: white;
    border: none;
    font-size: 16px;
    margin: 10px;
    padding: 15px 25px;
    border-radius: 5px;
    cursor: pointer;
}

button:hover {
    color: #f4f4f4;
    background: #446190;
}

#btn {
    display: flex;
    justify-content: center;
}

footer {
    width: 100vw;
    height: 15vh;
    background-color: #1877f2;
    display: flex;
    justify-content: space-evenly;
}

#social-media {
    display: flex;
    justify-content: space-evenly;
    width: 300px;
}

#setting {
    display: flex;
    justify-content: center;
    font-weight: bold;
    padding: 15px;
}

.slidecontainer {
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    align-content: space-around;
}

.slidecontainer input {
    width: 80%;
    padding: 20px;
}

a {
    font-size: 50px;
}

i {
    color: black;
}
)=====";
