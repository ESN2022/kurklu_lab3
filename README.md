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


https://user-images.githubusercontent.com/24780090/213129209-90b0661f-3827-411d-8fb3-0ec773c4ee1a.mov


## Affichage 7 segments
### Uniquement Z

Pour l'affichage sur les 7 segments j'ai simplement repris le code vhdl bin_to_7seg et les fonctions du lab2. Néanmoins j'ai dû adapter le code dans la partie software afin de pouvoir gérer l'affichage sur les six 7 segments, mais aussi l'affichage des valeurs négatives. J'ai commencé par uniquement afficher Z.

![IMG_7141](https://user-images.githubusercontent.com/24780090/213132988-1f8f82fc-3f36-4ac7-ba70-589a0c73d820.jpg)

### XYZ avec bouton et interruption 
J'ai ensuite mis en place une interruption avec le bouton comme dans le lab1, afin de pouvoir switch entre la valeur de X,Y et Z.

https://user-images.githubusercontent.com/24780090/213138352-a556ad66-c6c8-473f-b8b9-29fded84c194.mov

### Utilisation du TIMER 
Pour le timer j'ai appliqué la même configuration que dans le lab2 afin de pouvoir metre à jour l'affichage toutes les 1s sur les 7 segments.


https://user-images.githubusercontent.com/24780090/213139162-befcd064-8bdd-466c-8ed8-8d63e38a25b6.mov

Voici mon application finale :


https://user-images.githubusercontent.com/24780090/213139660-b6834aa1-978d-40aa-8112-e57b28ad1e7c.mov


# Conclusion

J'ai réussi à implementer les différentes fonctionnalités demander pour le lab3. Au niveau de la complexité ce Tp semblé plus complique, mais une fois la communication avec L'ADXL comprit le reste du travail était similaire au Tp précédents. Le seul point que je ne pense pas avoir bien reussi est la partie calibration. Je pense avoir appliqué la bonne méthode afin de calibrer l'accéléromètre, mais malgré cela je n'obtenais pas les bonnes valeurs sur les différents axes. Par exemple lorsque l'appareil était à plat sur la table, j'obtiens x=0, y=0 et z = 9700. Je m'attendais en retournant l'appareil à obtenir 0 mg pour x et y et -9700 mg pour z. J'ai bien 0 pour x et y mais pour Z j'obtiens -7300 mg, je ne sais pas si le problème vien de ma calibration ou de l'appareil.
