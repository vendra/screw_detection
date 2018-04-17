===========================================  
= 2) Screw Detection (Soluzione Proposta) =  
===========================================  
Screw Detection Demo:  
  
$ mkdir build && cd build  
$ cmake ..   
$ make  
  
-It is necessary to decompress the dataset inside the 'dataset' folder  
  
Usage:  
$ ./ScrewDetection -h  
(Make sure that default.xml points to the dataset, otherwise specify a correct .xml)

Instructions:   
        -Left/Right arrows navigate between images of a set  
        -Up/Down arrows change template  
        -'+' e '-' keys select the closer or farther set of images, respectively  
        -Press 'q' key to exit  



==========ITA=========  
Screw detection funziona 'standalone':  
  
$ mkdir build && cd build  
$ cmake ..   
$ make  
  
-E' necessario decomprimere i dataset all'interno della cartella dataset prima di utilizzarli  
  
Per utilizzo:   
$ ./ScrewDetection -h   
(assicurarsi che il file default.xml punti al dataset, altrimenti specificare un .xml corretto)  

Funzionamento:   
        -Le frecce dx/sx cambiano tra le immagini all'interno di un set  
        -Le frecce su/giù cambiano i template  
        -I tasti '+' e '-' selezionano il set di immagini più vicino o lontano, rispettivamente  
        -Premere 'q' per uscire  

NOTA: Potrebbero esserci problemi di compatibilità con OpenCV2,  
in particolare alla riga 146 del file main.cpp.   