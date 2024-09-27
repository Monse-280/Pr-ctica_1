#include <stdio.h>
#include <Socket_Cliente.h>
#include <Socket.h>

main (){
	int Socket_Con_Servidor;
   	int Longitud_Cadena = 0;
   	int Aux;
	char Cadena[100];

	/* Se abre la conexion con el servidor, pasando el nombre del ordenadory el servicio solicitado "localhost"
	corresponde al nombre del mismo ordenador en el que estamos corriendo.El servicio debe ser 5000*/
	
	Socket_Con_Servidor = Abre_Conexion_Inet ("localhost", "cpp_java");
	if (Socket_Con_Servidor == 1){
		printf ("No se logro establecer conexion con el servidor\n");
		exit (-1);
	}

   	// Se lee un entero con la longitud de la cadena
   	Lee_Socket (Socket_Con_Servidor, (char *)&Aux, sizeof(int));
   	Longitud_Cadena = ntohl (Aux);
   	printf ("Cliente C: Recibido %d\n", Longitud_Cadena-1);

   	//Se lee la cadena
   	Lee_Socket (Socket_Con_Servidor, Cadena, Longitud_Cadena);
   	printf ("Cliente C: Recibido %s\n", Cadena);
   
	// Se va a enviar una cadena de 6 caracteres, incluido el \0. Previamente se envia un entero con el 6.
	strcpy (Cadena, "Hola como estas");
   	Longitud_Cadena = 10;

   	// Antes de enviar el entero hay que transformalo a formato red */
   	Aux = htonl (Longitud_Cadena);
   	Escribe_Socket (Socket_Con_Servidor, (char *)&Aux, sizeof(Longitud_Cadena));
   	printf ("Servidor C: Enviado %d\n", Longitud_Cadena-1);

   	// Se envia la cadena 
	Escribe_Socket (Socket_Con_Servidor, Cadena, Longitud_Cadena);
   	printf ("Servidor C: Enviado %s\n", Cadena);
	close (Socket_Con_Servidor);
}
