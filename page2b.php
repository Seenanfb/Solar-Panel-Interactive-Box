<!DOCTYPE html>
<html>
<head>
</head>
<body>
<?php



$servername = "sql3.freesqldatabase.com";
$username = "sql3111161";
$password = "vfqqJSzUpj";
$dbname = "sql3111161";


$buffer = fopen("test.txt","r") or die("Error: Unable to open file!");

$dist = fread($buffer, filesize("test.txt"));

$date = date('Y-m-d H:i:s');

$localIP = getHostByName(getHostName());

$page = "2b";

echo "<iframe style=\"position: absolute; width: 100%; height: 96%; border: none\" src=\"https://www.sunnyportal.com/Templates/PublicPage.aspx?page=b0330343-fefd-452c-a599-4d491ada684f&plant=59161da0-3471-4b51-8af1-93f059b5fc2b\"> </iframe>";
	
  //connection to db
        $conn = new mysqli($servername, $username, $password, $dbname);

        //check
        if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
        }

        $sql = "INSERT INTO BoxDB (distance, timestamp, page)
                VALUES ('$dist', '$date', '$page')";

        if ($conn->query($sql) === TRUE) {
                //To verify db update:
                echo "Database updated.";
        } else {
                echo "Error: " . $sql . "<br>" . $conn->error;
        }

        $conn->close();


if ($dist <= 25) {

	header("Refresh: 5");

} else  {

	//header("Refresh: 4; url= http://munro.humber.ca/~bnns0231/iBoxProj/page2.php");
	//header("Refresh: 4; url= http://10.111.102.131/page2.php");

	header("Refresh: 5; url= http://$localIP/page2.php");
}
fclose($buffer);

?>



</body>
</html>
