Key with value pair generation.c have raw code and explained the process of working below


# Freshworks
Drive for Interview
ROUND 1:


!!!! IF IT ASK FOR PIN
 
 
 PIN : 1254701










NAME : NAVEEN SANGATH E
UNIVERSITY ROLL NO : 17BEC104

PROGRAMMING LANGUAGE : C

OS USED: WINDOWS 10

PREREQUISTES:
           
           
   used compiler : CODEBLOCKS with gcc compiler installed in PC
 
 
 KEY WORDS USED:
           
           
   DRIVE NAMED E://
           
   creating two files as new.txt and access.txt
            
LIBRARIES USED:


  stdio.h -->standard input output 
  
  
  time.h  -->fetching present time of system
  
  
  string.h-->using string function - strcpy only used
  
  If ACCESS CODE is 1 --> Some one is already accessing the file
  If ACCESS CODE is 0 --> No one is accessing the file
  


EXPLANATION OF CRD IMPLEMENTATION:


     I have Implemented File like a DATABASE.
     CREATE :
            
            Initially checking the presense of new.txt - If no file found, new.txt will be created
            Getting the input from the user in format  % KEY <space> VALUE <space> TIME %
            Checking the constrains of 
                                      1.KEY < 33 characters
                                      2.VALUE < 17KB
                                      3.TIME > 0
            Transversing through the file to check KEY unique value
            Setting access code in access.txt as 1
            If all the above constraints passed :
                    new.txt file -> stores each input data in new line 
            Setting access code in access.txt as 0
  
    READ :
          Getting the KEY to find match value
          Transversing through the file and searching for the data with same KEY
          Setting access code in access.txt as 1
          If the KEY matched:
                  return the VALUE and KEY
          Setting access code in access.txt as 0
          
    DELETE :
          Getting the KEY to find 
          Transversing through the file and searching for the data with same KEY
          Setting access code in access.txt as 1
          If the KEY matched:
                  The data will be deleted
          Setting access code in access.txt as 0
      
      
      Process of deleting a line / data:
                Initializing a file named temp.txt
                Transversing through the data
                        If the KEY matches,Data is not copied to temp.txt
                Finally,
                        removing new.txt and renaming temp.txt ->new.txt
    
          
 I tried to implement the Access to one user restricting multiple user to access the same file twice.


This is only possible if user exit properly.
  
  
Things not Implemented:


Threat security


Way to IMPLEMENT :


1.This could be Done with JAVA using PROTECTED CLASS through which the data cannot be access.


2.It could be access through the method which could implemented to return those values.
