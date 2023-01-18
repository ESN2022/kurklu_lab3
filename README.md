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

À l'aide des fichiers fournis par l'IP opencores_i2c, j'ai d'abord initialisé la communication avec l'i2c à l'aide de la fonction I2C_init() et la fonction I2C_start() sur le registre 0x1D pour vérifier son bon fonctionnement. J'ai ensuite écrit les deux fonctions ecriture_i2c() et lecture_i2c(), pour les lectures et écriture en m'aidant encore une fois des fichiers fournis par l'IP. J'ai ensuite réalisé des lectures sur les registres ACT_INACT_CTL(0X27), POWER_CTL(0x2D) et DATA_FORMAT(0x31), pour vérifier s'il était bien initialisé. J'ai finalement écrit 0x8 sur POWER_CTL, afin d'activer les mesures et 0x7, sur DATA_FORMAT afin d'être en full résolution de +-16g.

## Affichage UART

Pour l'affichage sur l'UART j'ai d'abord lu les registres X0(0x32), X1(0x33), Y0(0x34), Y1(0x35), Z0(0x36) et Z1(0x37). J'ai ensuite réalisé un shift et un ou, entre le LSB et MSB afin d'avoir les mesures finales. Finalement j'ai affiché les veleurs obtenus sur l'UART.

https://user-images.githubusercontent.com/24780090/213125986-3d57668c-5c14-4567-ad5c-54ee17405554.mov

## Calibration

Pour la calibration j'ai d'abord écrit des 0 sur les registres, OFSX(0x1E), OFSY(0x1F) et OFSZ(0x20) afin d'enlever les valeurs d'offset. J'ai ensuite lu les mesures sur l'UART. Par exemple pour Z j'obtenais la valeur 7c0 --base(10)--> 1984 --x3.9--> 7737 mg. La valeur que l'on veut  pour Z, lorsque la carte et à plat est de 9800 mg, j'ai donc ajouté progressivement de l'offset dans le registre OFSZ afin d'obtenir le résultat souhaiter. J'ai réalisé la même démarche pour X ET Y afin d'obtenir pour les 2 registres la 0 mg.

https://user-images.githubusercontent.com/24780090/213128463-bebdde23-f9a1-4730-a1e5-a36f1d428e3e.mov


## Affichage 7 segments

# Conclusion
