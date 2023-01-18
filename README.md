# kurklu_lab3

# Introduction
Dans le cadre de notre cours de conception conjointe en GE5A a Polyteh Clermont, nous sommes amenées à mettre en pratique les connaissances théoriques acquises lors de TP. Ses travaux sont réalisés sur une carte Terasic DE10 - Lite basé sur un FPGA Altera MAX 10. Pour ce troisième projet notre objectif est d'interfacer un accéléromètre ADXL345 par i2c. Le régler correctement puis réaliser l'affichage des différents axes sur les afficheurs 7 segments en utilisant un timer et des interruptions.

# Architecture
Voici l'architecture que j'ai réalisée sur paint :
![lab3](https://user-images.githubusercontent.com/24780090/213120076-4c1e3f18-3208-48f5-9a04-559f55001bc2.png)

J'ai tout d'abord repris les éléments afin de reconstruire mon system basic :

* Une clock
* Une RAM
* Un NIOS-2
* Un JTAG

Par la suite, j'ai ajouté les PIO afin de pouvoir gérer mes I/O :

* PIO sur 7 bits pour le segment0
* PIO sur 7 bits pour le segment1
* PIO sur 7 bits pour le segment2
* PIO sur 7 bits pour le segment3
* PIO sur 7 bits pour le segment4
* PIO sur 7 bits pour le segment5
* Un TIMER
* PIO sur 1 bit pour le bouton

# Avancement

## Initialisation I2C
## Affichage UART
## Calibration
## Affichage 7 segments

# Conclusion
