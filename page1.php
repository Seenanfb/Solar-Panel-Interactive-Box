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

echo "<iframe style=\"position: absolute; width: 100%; height: 100%; border: none\" src= \"https://www.sunnyportal.com/Templates/PublicPage.aspx?page=395e7f76-5101-4ed9-8768-65166aa886d0&plant=eab332c7-eb20-4f08-9ca5-a3e3b688bb66\"> </iframe>";

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

if ($dist < 25 ) {
//	header("Refresh: 4; url=http://munro.humber.ca/~bnns0231/iBoxProj/page1b.php");
//	header("Refresh: 4; url=http://10.111.102.131/page1b.php");
        header("Refresh: 5; url= http://$localIP/page1b.php");
	
	//sleep(4);

	//header("Refresh: 5");

	//$sql = "INSERT INTO BoxDB (distance, timestamp, page)
	//	VALUES ('$dist', '$date', '1')";

        //header("Refresh: 5; url= http://$localIP/page1b.php");
	

} else {

//	header("Refresh: 4; url=http://munro.humber.ca/~bnns0231/iBoxProj/page2.php");
//	header("Refresh: 4; url=http://10.111.102.131/page2.php");
        header("Refresh: 5; url= http://$localIP/page2.php");

	$sql = "INSERT INTO BoxDB (distance, timestamp, page)
		VALUES ('$dist', '$date', '1')";
}
fclose($buffer);

?>



</body>
</html>
