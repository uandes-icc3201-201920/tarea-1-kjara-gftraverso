# icc3201-201920-tarea1

---


 * **Dificultades encontradas:** Conocíamos la parte teórica de los sockets y su funcionamiento, que son canales bidireccionales de comunicación, se puede usar en ambos sentidos. Podemos conectar procesos servidores y procesos clientes.  Al no estar familiarizados del todo con este tipo de comunicación fue difícil comprender el tipo de funcionamiento (en cuanto a la programación). Como por ejemplo: *socket_path*, *struct_un_addr* (dirección asociada a la puerta) ,  la manera de crear un socket (el primer argumento especifica la familia de direcciones en que se debe interpretar, en nuestro caso usamos AF_UNIX ya que usamos un pathname. El segundo argumento usamos SOCK_STREAM dado que es una conexión de circuito virtual. El tercer argumento lo dejamos en 0 ya que el sistema resuelve el valor que coresponde a ese protocolo según el valor dado en el segundo argumento).  Pero en el momento que fueron comprendidas sus funcionalidades no hubo mayor problema. Además de la implementación de threads, que no nos quedó claro cómo manejarlos.




* **Funciones no implementadas:** Cuando el cliente inicia tiene un tiempo máximo de 10 segundos para conectarse a un servidor. El esperar 10 segundos no fue implementado, para lo anterior se necesitaba el uso de threads......... Lo cual no fue comprendido del todo en modo práctico y no se nos ocurrió de qué otra manera realizar esa espera.


* **Problemas conocidos:** Al momento de ingresar la key y value, se asumió que el usuario ingresaría en key un número y en value una letra. En caso contrario, si el usuario ingresa una letra o caracter en key el programa se cae. Asumimos un usuario "happy path"
1. *ejemplo* 
           insert(w,w)
            ERROR//
          

---

*Integrantes: Gianfranco Traverso - Katherine Jara*
