   #                                 README                       
Run This Commands in terminal:
//(In Terminal1)

$cd File_share/

File_Share/$ cd Peer1/

File_Share/Peer1/ $ gcc fileshare.c -o server 

File_Share/Peer1/ $ ./server


//(In other Terminal2)

$cd File_share/

File_Share/$ cd Peer2/

File_Share/Peer2/ $ gcc fileshare.c 

File_Share/Peer2/ $ ./a.out
 
Give any port no. In Terminal1 and Terminal2(Binding an unique port number)
Ex:5000(in Terminal1),6000(in Terminal2)

Now in Terminal2 or Terminal1 make any Terminal as Client programme by entering the Port number given in another Terminal

Then another Terminal acts as Server and Accepts Requests.

Now in Terminal (which is acting as Client),Can Accept following Requests

Requests are:

q or Q  (for quit)

IndexGet LongList

IndexGet ShortList                          

IndexGet RegEx “*mp3” (“*mp3 ”if file extension is mp3) 

FileHash Verify filename

FileHash CheckAll XXXXXXXX NOT WORKING XXXXXXXXXX

FileUpload filename

FileDownload filename
