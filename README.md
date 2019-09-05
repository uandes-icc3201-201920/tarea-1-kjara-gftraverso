# icc3201-201920-tarea1

---
En esta parte de la tarea consistió en implementar un sistema de base de datos no relacional del tipo pares (tuplas) clave-valor. El usuario ingresa el valor de la clave, siempre debe ser un entero positivo.En cuanto al  ***proceso servidor*** se inicia desde la línea de comando y se puede entregar o no la ruta de dominio a utilizar, escucha y acepta la conexión de un cliente. Al momento de ingresar el comando solo es capaz de procesar uno, procesa y entrega el resultado al cliente, y cuando éste se desconecta, el servidor  sigue esperando por otra conexión. Finalmente el ***proceso cliente*** es muy similar al procesor servidor en cuanto a su iniciación a través de la consola, este se debe iniciar en un tiempo máximo de 10 segundos para conectarse con un servidor, si se excede ese tiempo  muestra error y se espera al siguiente comando. Los comandos que se pueden ejecutar de cliente son: *connect* , *disconnect* , *insert(key,value)* , *get(key)* , *peek(key)* , *update(key,value)* , *delete(key)*, *list*. Para todo esto utilizamos el canal de comunicación llamado **socket**.

Los ***sockets*** son canales bidireccionales de comunicación. Se puede usar el canal en ambos sentidos. Con los Unix Domain Sockets(U.D.S) podemos conectar procesos servidores y procesos clientes. Varios clientes se pueden comunicar con un servidor, cabe destacar que para esta entrega solo un cliente se comunicaba con un servidor a través de U.D.S. Además los U.D.S permiten un flujo confiable de datos (reliable streams) y también la transmisión de paquetes no confiables (sin orden ni acuso de recibo).

Los ***threads*** se entiende como flujo de ejecución que vive dentro de un proceso, compartes espacios de memoria y recursos del proceso a que pertenecen. Son muy utilizados para la programación paralela, poder descomponer un programa en varios threads para conseguir paralelismo (multiprocesamiento).

 * **Dificultades encontradas:** Conocíamos la parte teórica de los sockets y su funcionamiento, y al no estar familiarizados del todo con este tipo de comunicación fue difícil comprender el tipo de funcionamiento (en cuanto a la programación). Como por ejemplo: *socket_path*, *struct_un_addr* (dirección asociada a la puerta) ,  la manera de crear un socket (el primer argumento especifica la familia de direcciones en que se debe interpretar, en nuestro caso usamos AF_UNIX ya que usamos un pathname. El segundo argumento usamos SOCK_STREAM dado que es una conexión de circuito virtual. El tercer argumento lo dejamos en 0 ya que el sistema resuelve el valor que coresponde a ese protocolo según el valor dado en el segundo argumento).  Pero en el momento que fueron comprendidas sus funcionalidades no hubo mayor problema. Además de la implementación de threads, que no nos quedó claro cómo manejarlos.
 Cabe destacar que el código base no fue utilizado del todo, su estructura no fue comprendida perfectamente, por lo que preferimos usar otro método para realizar la comunicación inter-procesos.


* **Funciones no implementadas:** Cuando el cliente inicia tiene un tiempo máximo de 10 segundos para conectarse a un servidor. El cronómetro, esperar 10 segundos no fue implementado, para lo anterior se necesitaba el uso de threads ya que era un proceso dentro de otro, pero no fue comprendido del todo en modo práctico y no se nos ocurrió de qué otra manera realizar esa espera.


* **Problemas conocidos:** Al momento de ingresar la key y value, se asumió que el usuario ingresaría en key un número y en value una letra. En caso contrario, si el usuario ingresa una letra o caracter en key para cualquier  comando que requiera key, el programa se cae. Asumimos un usuario "happy path"
1. *ejemplo* 
           insert(w,w)
            ERROR//
          

---

*Integrantes: Gianfranco Traverso - Katherine Jara*

---
* Definición de socket obtenida de clase3

