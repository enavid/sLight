const char htmlPage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <title>IOT</title>
    <link rel="stylesheet" href="./style.css">
</head>

<body>
    <header>

    </header>
    <main>
        <section id="first-section">
            <div>
                <p id="information">Information</p>
            </div>
            <div id="light-information">
                <div class="info-1">
                    <p id="light-threshold">Light-threshold = 50 %</p>
                    <p id="Illuminance">Illuminance = 0 lux</p>
                </div>
                <div class="info-2">
                    <p id="lamp-brightness">Lamp-brightness = 50 %</p>
                    <p id="lamp-status">Lamp-status = OFF</p>
                </div>
            </div>
        </section>
        <section id="second-section">
            <div>
                <p id="setting">Setting</p>
            </div>
            <div id="btn">
                <button id="offButton">OFF</button>
                <button id="onButton">ON</button>
            </div>
            <div class="slidecontainer">
                <p>Light brightness</p>
                <input id="slider1" type="range" min="1" max="100" value="50">
                <p>Threshold</p>
                <input id="slider2" type="range" min="1" max="100" value="50">
            </div>
        </section>

    </main>
    <footer>
        <div id="social-media">
            <a href="https://github.com/enavid">
                <i class="fa fa-github"></i>
            </a>
            <a href="www.linkedin.com/in/enavid">
                <i class="fa fa-linkedin-square"></i>
            </a>
            <a href="https://twitter.com/en_navid1">
                <i class="fa fa-twitter-square"></i>
            </a>
        </div>
    </footer>
    <script src="./app.js"></script>
</body>

</html>
)=====";
