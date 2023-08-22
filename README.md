# mmc_lbr
libreria para utilizar una memoria microSD tipo sdHC sin formato fat

Esta libreria actualmente la he utilizado com memorias microSD HC I tanto de 4GB, 8 GB y 32GB
en un micro controlador PIC18F4620
como es lenguale C se podria adaptar a cualquier micro

como usar la libreria,

1.- Iniciar el puerto de comunicaciones SPI bien sea por software o usando un puerto SPI del micro.
2.- Iniciar la memoria SD con la funcion mmc_init();
3.- declarar las siguientes variables
    char bufferSd[512]
    unsigned int bufferSdCount = 0

la utilidad del buffer es porque la memoria tipo HC esta configurada por defecto que se debe escribir de a una pagina a la vez
cada pagina es de 512 bytes
entonces si se configura la memoria para escribir mas paginas por ejemplo 2 paginas el bufferSD seria de 1024 posiciones
esto influye en la cantidad de memoria ram disponible en el micro. para este caso esta con la configuracion por defecto.
segun sea el caso, se debe hacer una rutina de como ir guardando los datos en el bufferSD e ir verificando su estado para esp
esta la utilidad de bufferSdCount es llevar el registro de la cantidad de datos que se van guardando en el buffer al llegar al
maximo de 512 bytes se utiliza la rutina de ejmplo:

    if(bufferSdCount >= 510){  // guarda en memoria
        Write_page(page, 0);
        page++;
        bufferSdCount = 0;
    }

esta rutina lo que hace es verificar que ya se lleno el bufferSD y lo descarga a la memoria mediante la funcion Write_page(page,0)
la variable page,es la variable que especifica en que direccion de la memoria se va a escribir, para el caso de las memorias
tipo HC las direcciones no son posiciones sino paginas, y el valor 0 es una variable dentro de la funcion que se utiliza para escribir 
informacion en la pagina especificada por page o si por el contrario el valor es 1 entonces la pagina especificada se llena de 0xFF,
en otras palabras se borra esa pagina.

para leer una pagina en una direccion especifica se utiliza la funcion Read_page(dir), donde dir es direccion de la pagina que se
va a leer, cuando se utiliza esta funcion toda la informacion que se lee de la pagina de la memoria se guarda en el bufferSD asi luego
para usar los datos requeridos estos se deben extraer del bufferSD creando una rutina segun sea el caso.

hasta el momento esta libreria me ha funcionado pero con un inconveniente que no he logrado resolver el cual es,
al momento de iniciar el circuito y hacer la primera lectura en la memoria SD, esta lectura me da datos erroneos, luego apartir de
de la segunda lectura en la memoria esta trabaja muy bien sin ningun tipo de error, esta falla me trae como consecuencia que no
puedo crear mi propia FAT en la memoria SD, (llamese a mi propia FAT a mi manera de gestionar los datos dentro de la memoria)
entonces esta FAT la estoy haciendo es en la eprom del microcontrolador y hacer esto me trae como falla que al cambiar una memoria 
por otra el programa cree que tiene los datos guardados de la memoria anterior.
