const char registerIndex[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>login page</title>
    <link rel="stylesheet" href="./register.css">
</head>

<body>
    <form>
        <div class="login">
            <p>Register page</p>
        </div>

        <div class="container">
            <label for="uname"><b>Username</b></label>
            <input id="username" type="text" placeholder="Enter Username" name="uname" required>

            <label for="psw"><b>Password</b></label>
            <input id="psw" type="password" placeholder="Enter Password" name="psw" required>

            <label for="confirm-psw"><b>Confirm password</b></label>
            <input id="confirm-psw" type="password" placeholder="Enter Password agian" name="confirm-psw" required>

            <label for="ssid"><b>Wireless SSID</b></label>
            <input id="ssid" type="text" placeholder="Enter wireless SSID name" name="ssid" required>

            <label for="ssid-psw"><b>Enter Wireless password</b></label>
            <input id="ssid-psw" type="text" placeholder="Enter Password agian" name="ssid-psw" required>

            <button type="submit" id="submit">submit</button>
        </div>
    </form>
    <script src="./register.js"></script>
</body>

</html>
)=====";