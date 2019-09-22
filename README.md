# icc3201-201920-tarea1-2

---
En esta parte de la tarea consistió en la implementación de concurrencia en la base de datos no relacional minimalista antes implementada. El usuario ingresa el valor de la clave, siempre debe ser un entero positivo.En cuanto al  ***proceso servidor*** se inicia desde la línea de comando y se puede entregar o no la ruta de dominio a utilizar, escucha y acepta la conexión del cliente (cabe destacar que el servidor puede aceptar múltiples conexiones concurrentes de clientes). El servidor debe correr en su thread principal un ciclo para que permita escuchar conexiones de múltiples clientes a través del ***unix domain socket local*** . Cuando la conexión es aceptada, se desencadenan las siguientes acciones:
1. Servidor crea un client socket, desde el cual le es posible leer y escribir datos desde/hacia un cliente conectado.
2. Luego  crea un thread que procesa los comandos de la sesión cliente a través del client socket generado.
3. El thread debe correr un loop que espere un comando desde el cliente, lo ejecute y retorne el resultado por el socket. 
4. Cuando el cliente ejecuta disconnect, se debe cerrar el client socket y además el thread que procesa su sesión en el servidor debe terminar.

El ***proceso cliente*** es muy similar al procesor servidor en cuanto a su iniciación a través de la consola, este se debe iniciar en un tiempo máximo de 10 segundos para conectarse con un servidor, si se excede ese tiempo  muestra error y se espera al siguiente comando. Los comandos que se pueden ejecutar de cliente son: *connect* , *disconnect* , *insert(key,value)* , *get(key)*  , *update(key,value)* , *delete(key)*, *list*. 

La ***sincronización de las estructura de datos***: dado que habrán múltiples cientes conectados al servidor es necesario sincronizar el acceso a la base de datos, para evitar todo tipo de anomalías en la seccion crítica del proceso servidor. El contador de claves autogeneradas debe ser sincronizado como un contador exacto.Por otro lado, el almacenamiento de pares clave-valor debe ser sincronizado minimizando el sacrificio de rendimiento utilizando locks de lectura y escritura.


Los ***sockets*** son canales bidireccionales de comunicación. Se puede usar el canal en ambos sentidos. Con los Unix Domain Sockets(U.D.S) podemos conectar procesos servidores y procesos clientes. Varios clientes se pueden comunicar con un servidor, cabe destacar que para esta entrega solo un cliente se comunicaba con un servidor a través de U.D.S. Además los U.D.S permiten un flujo confiable de datos (reliable streams) y también la transmisión de paquetes no confiables (sin orden ni acuso de recibo).

Los ***threads*** se entiende como flujo de ejecución que vive dentro de un proceso, compartes espacios de memoria y recursos del proceso a que pertenecen. Son muy utilizados para la programación paralela, poder descomponer un programa en varios threads para conseguir paralelismo (multiprocesamiento).

 * **Dificultades encontradas:** Conocíamos la parte teórica de los sockets y su funcionamiento, ya se estaba familiarizado en la manera de programarlos por lo que no hubo mayor problema. Sin embargo, la implementación de threads fue complejo manejarlos, pero al indagar e investigar más sobre el tema se pudieron realizar las funciones requeridas para esta entrega.
 

* **Funciones no implementadas:** En esta parte de la tarea todas las funciones fueron implementadas. Sin embargo, cuando el cliente inicia tiene un tiempo máximo de 10 segundos para conectarse a un servidor (el cronómetro, esperar 10 segundos no fue implementado, esto era de la entrega anterior, no creímos necesaria su creación dado que no afectaba esta entrega).


* **Problemas conocidos:** Al momento de ingresar la key y value, se asumió que el usuario ingresaría en key un número y en value una letra. En caso contrario, si el usuario ingresa una letra o caracter en key para cualquier  comando que requiera key, el programa se cae. Asumimos un usuario "happy path"
1. *ejemplo* 
           insert(w,w)
            ERROR//
          

---

*Integrantes: Gianfranco Traverso - Katherine Jara*

---
* Definición de socket obtenida de clase3

