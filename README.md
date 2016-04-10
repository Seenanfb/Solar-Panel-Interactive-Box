# Solar Panel Interactive Box
It's a system that utilizes sensors to swap between webpages appropriately for its consumption, which, each show you different information about the solar panels it's connected to.

page1.php

Updates the database. Shows energy and power of the first of Humber's photovoltaic system or solar PV system. Constantly switches between page2.php and page1.php, swapping to page1b.php if the sensor picks up a reading under 25cm.

page1b.php

Updates the database. Shows the plant overview for Humber PV1 (the first PV system). Alternates between refreshing and swapping back to page1.php if sensor reading is above 25cm.

page2.php

Updates the database. Shows the system profiles for the PV systems 1 and 4, along with pictures. Constantly switches between page1.php and page2.php, swapping to page2b.php if the sensor picks up a reading under 25cm.

page2b.php

Updates the database. Shows the monthly report for Humber's 4th PV system. Alternates between refreshing and swapping back to page2.php if sensor reading is above 25cm.
