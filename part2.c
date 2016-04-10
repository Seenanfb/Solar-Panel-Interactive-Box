// Test code for the Interactive Box
//
// It will take a ranging from the module and print results
// to the screen. From those results, it will determine if anything is close 
// enough to display 1 of 2 browser pages.
//

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>


void openBrowser(void);
void motionTimer(void);

int main(int argc, char **argv)
{
	FILE *fp;
	FILE *fp2;

	FILE *distp;
	FILE *distp2;
	FILE *distpb;
	FILE *testp;

	FILE *toucher;

	//FILE *browserp;

	int i = 0;
	int x = 0;
	int status;

	unsigned char lowByte;
	unsigned char highByte;
	unsigned int result;

	char name[] = "distance.txt";
	char nameb[] = "~/var/www/distance.txt";
	char other[] = "time.txt";
	char otherb[] = "~/var/www/time.txt";
	char testf[] = "test.txt";
	char buff[5];
	memset(buff, 0, sizeof buff);

	double seconds = 0;
	double msecs;

	time_t starter;
	time_t ender;

	pthread_t threader;

	


	toucher = popen("touch ~/PROJECT/distance.txt ~/PROJECT/time.txt", "w");
	fclose(toucher);


	printf("**** Interactive Box test browser program ****\n");

	openBrowser();
        //browserp = popen("sensible-browser http://munro.humber.ca/~bnns0231/ceng355/sample.html > /dev/null 2>&1", "r");
	//browserp = popen("sensible-browser http://munro.humber.ca/~bnns0231/iBoxProj/page1.php > /dev/null 2>&1", "r");
	//fclose(browserp);

	int fd;			// File descriptor

	char *fileName = "/dev/i2c-1";	
	// Name of the port we will be using

	int  address = 0x70;	// Address of the SRF02 shifted right one bit

	unsigned char buf[10];	
	// Buffer for data being read/ written on the i2c bus

	while(1){	//Forever checks the changing distance of people
		if ((fd = open(fileName, O_RDWR)) < 0) {					// Open port for reading and writing
			printf("Failed to open i2c port\n");
			exit(1);
		}

		if (ioctl(fd, I2C_SLAVE, address) < 0) {				// Set the port options and set the address of the device we wish to speak to
			printf("Unable to get bus access to talk to slave\n");
			exit(1);
		}

		buf[0] = 0;													// Commands for performing a ranging
		buf[1] = 81;

		if ((write(fd, buf, 2)) != 2) {								// Write commands to the i2c port
			printf("Error writing to i2c slave\n");
			exit(1);
		}

		usleep(750000);		// This sleep waits for the ping to come back

		buf[0] = 0;		// This is the register we wish to read from

		if ((write(fd, buf, 1)) != 1) {								// Send the register to read from
			printf("Error writing to i2c slave\n");
			exit(1);
		}

		if (read(fd, buf, 4) != 4) {								// Read back data into buf[]
			printf("Unable to read from slave\n");
			exit(1);
		}
		else {
			highByte = buf[2];
			lowByte = buf[3];
			result = (highByte <<8) + lowByte;
			// Calculate range as a word value
			//printf("Software v: %u \n",buf[0]);
			printf("Range was: %u\n",result);

			distp = fopen(name, "w");
			if(distp == NULL)
			{
				fprintf(stderr, "Error opening file (distance)\n");
				exit(1);
			}	

			fprintf(distp, "%u", result);
			fprintf(distp, "\n");
			fclose(distp);

			if(result <= 25){

				distp2 = fopen(other, "w");
				if(distp == NULL)
				{
					fprintf(stderr, "Error opening file\n");
					exit(1);
				}	
				//				fseek(distp2, 0, SEEK_END);
				fprintf(distp2, "%.2f", seconds);
				fprintf(distp2, "\n");
				fclose(distp2);


			testp = fopen(testf, "w");
			if(testp == NULL)
			{
				fprintf(stderr, "Error opening file (test)\n");
				exit(1);
			}	

			fprintf(testp, "%u", result);
			fprintf(testp, "\n");
			fclose(testp);

/*	if(pthread_create(&threader, NULL, motionTimer, &x))
	{
	fprintf(stderr, "Error creating thread\n");
	exit(1);
	}*/
				time(&starter);
motionTimer();
				time(&ender);
	/*			if(pthread_join(threader, NULL)){
					fprintf(stderr, "Error joining main thread");
					exit(2);
				}*/

				seconds = difftime(ender, starter);
				msecs = seconds * 1000;
				fprintf(stdout, "Time close to sensor: %.2f\n", seconds);
			}

			else{
				seconds=0;
				
			testp = fopen(testf, "w");
			if(testp == NULL)
			{
				fprintf(stderr, "Error opening file\n");
				exit(1);
			}	

			fprintf(testp, "%u", result);
			fprintf(testp, "\n");
			fclose(testp);
			}
		}

		sleep(3);
		//Proper sleep value = 
	}
	return 0;
}


void openBrowser(void)
{

FILE *browserp;
FILE *ipgetter;

char theIP[20];
memset(theIP, 0, sizeof theIP);

char thePage[150] = "(sensible-browser http://";  //)
char theRest[150] = "/page1.php &) > /dev/null 2>&1";

if (NULL == (ipgetter = popen("hostname --ip-address", "r"))) { //get the current local IP
    fprintf(stderr, "Error creating hostname...");
	exit(1);
}

fgets(theIP, sizeof(theIP), ipgetter);
fclose(ipgetter);

theIP[strcspn(theIP, "\n")] = 0; //Terminates the newline placed at the end of fgets function

strcat(thePage, theIP);
strcat(thePage, theRest); //Add the IP to the website link

//sleep(500); //For debugging purposes

	browserp = popen(thePage, "r");
	//browserp = popen("(sensible-browser http://munro.humber.ca/~bnns0231/iBoxProj/ &)  > /dev/null 2>&1", "r");
	//browserp = popen("./browse.sh & > /dev/null 2>&1", "r");
	fclose(browserp);

//return;
}


//void *motionTimer(void *thing)
void motionTimer(void)
{

//Function to time how long you've been close to the sensor (within 25cm)


	int i = 0;
	int status;
	unsigned char lowByte;
	unsigned char highByte;
	unsigned int result;
	int fd;                 // File descriptor

	char *fileName = "/dev/i2c-1";
	int  address = 0x70;    // Address of the SRF02 shifted right one bit

	unsigned char buf[10];

	while(1){
		if ((fd = open(fileName, O_RDWR)) < 0) {                                        // Open port for reading and writing
			printf("Failed to open i2c port\n");
			exit(1);
		}

		if (ioctl(fd, I2C_SLAVE, address) < 0) {                                // Set the port options and set the address of the device we wish to speak to
			printf("Unable to get bus access to talk to slave\n");
			exit(1);
		}

		buf[0] = 0;                                                                                                     // Commands for performing a ranging
		buf[1] = 81;

		if ((write(fd, buf, 2)) != 2) {                                                         // Write commands to the i2c port
			printf("Error writing to i2c slave\n");
			exit(1);
		}

		usleep(750000);         // This sleep waits for the ping to come back

		buf[0] = 0;             // This is the register we wish to read from

		if ((write(fd, buf, 1)) != 1) {                                                         // Send the register to read from
			printf("Error writing to i2c slave\n");
			exit(1);
		}

		if (read(fd, buf, 4) != 4) {                                                            // Read back data into buf[]
			printf("Unable to read from slave\n");
			exit(1);
		}
		else {
			highByte = buf[2];
			lowByte = buf[3];
			result = (highByte <<8) + lowByte; //Same function repeats itself as a timer
		}
		if(result > 25)
			break;


//return NULL;
	}
}
