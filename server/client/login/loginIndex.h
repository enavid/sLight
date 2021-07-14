const char loginIndex[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>login page</title>
    <link rel="stylesheet" href="./login.css">
</head>

<body>
    <form>
        <div class="login">
            <p>login page</p>
        </div>

        <div class="container">
            <label for="uname"><b>Username</b></label>
            <input id="username" type="text" placeholder="Enter Username" name="uname" required>

            <label for="psw"><b>Password</b></label>
            <input id="password" type="password" placeholder="Enter Password" name="psw" required>

            <button type="submit" id="login">Login</button>
        </div>
    </form>
    <script src="./login.js"></script>
</body>

</html>
)=====";