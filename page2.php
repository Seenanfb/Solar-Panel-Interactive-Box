<!DOCTYPE html>
<html>
<head>
</head>
<body>
<?php

$buffer = fopen("test.txt","r") or die("Error: Unable to open file!");
$dist = fread($buffer, filesize("test.txt"));

$date = date('Y-m-d H:i:s');

$servername = "sql3.freesqldatabase.com";
$username = "sql3111161";
$password = "vfqqJSzUpj";
$dbname = "sql3111161";

$localIP = getHostByName(getHostName());


echo "<table style =\"width: 1000px;\">
<tr>
<td align=\"left\" width=\"50%\">
<iframe style=\"width:100%; height:250px;\" src=\" https://www.sunnyportal.com/Templates/PublicPage.aspx?page=bfb5bd1b-f475-4470-9455-2c138e1b2e6a&plant=eab332c7-eb20-4f08-9ca5-a3e3b688bb66\"> </iframe>
</td>

<tr> <td align=\"left\" width=\"50%\">
<iframe style=\" width: 100%; height: 250px;\" src=\"https://www.sunnyportal.com/Templates/PublicPage.aspx?page=10483e48-f643-4357-993e-b0258e96fbd9&plant=59161da0-3471-4b51-8af1-93f059b5fc2b\"> </iframe>
</td></tr>";

	//connection to db
	$conn = new mysqli($servername, $username, $password, $dbname);

	//check
	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	} 

	$sql = "INSERT INTO BoxDB (distance, timestamp, page)
		VALUES ('$dist', '$date', '1')";

	if ($conn->query($sql) === TRUE) {
		//To verify db update:
		echo "Database updated.";
	} else {
		echo "Error: " . $sql . "<br>" . $conn->error;
	}

	$conn->close();

if ($dist < 25) {
//	header("Refresh: 4; url=http://munro.humber.ca/~bnns0231/iBoxProj/page2b.php");
//	header("Refresh: 4; url=http://10.111.102.131/page2b.php");
        header("Refresh: 5; url= http://$localIP/page2b.php");

} else {

//	header("Refresh: 4; url=http://munro.humber.ca/~bnns0231/iBoxProj/page1.php");
//	header("Refresh: 4; url=http://10.111.102.131/page1.php");
	header("Refresh: 5; url= http://$localIP/page1.php");


}
fclose($buffer);

?>
</body>
</html>

