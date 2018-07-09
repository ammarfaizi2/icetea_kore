<!DOCTYPE html>
<html>
<head>
	<title>Login</title>
	<link rel="stylesheet" type="text/css" href="/assets/css/login.css">
</head>
<body>
	<center>
		<div class="cg">
			<h2>Login</h2>
			<form method="post" action="/login_action">
				<label>Username:</label><br/>
				<input type="text" name="username" required/><br/><br/>
				<label>Password:</label><br/>
				<input type="password" name="password" required/><br/><br/>
				<button>Login</button>
			</form>
		</div>
	</center>
</body>
</html>