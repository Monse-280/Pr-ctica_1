#include <Socket_Servidor.h>
#include <Socket.h>
#include <string.h>
#include <stdio.h>

main (){
	int Socket_Servidor;
	int Socket_Cliente;
   	int Aux;
   	int Longitud_Cadena;
	char Cadena[100];

	//Se abre el socket servidor, el numero de dicho servicio debe ser 5000.
	Socket_Servidor = Abre_Socket_Inet ("cpp_java");
	if (Socket_Servidor == -1){
		printf ("Ocurrio un error no se pudo abrir socket servidor\n");
		exit (-1);
	}

	//Se espera un cliente que quiera conectarse
	Socket_Cliente = Acepta_Conexion_Cliente (Socket_Servidor);
	if (Socket_Servidor == -1){
		printf ("Ocurrio un error no se pudo abrir socket cliente\n");
		exit (-1);
	}

   // Se envia la longitud de una cadena
   Longitud_Cadena = 6;
   strcpy (Cadena, "Hola");

   // El entero es transformado a formato red para enviarlo 
   Aux = htonl(Longitud_Cadena);
   Escribe_Socket (Socket_Cliente, (char *)&Aux, sizeof(Longitud_Cadena));
   printf ("Cliente C: Enviado %d\n", Longitud_Cadena-1);
  
   // Se envia la cadena 
   Escribe_Socket (Socket_Cliente, Cadena, Longitud_Cadena);
   printf ("Cliente C: Enviado %s\n", Cadena);
   
   
	// Se lee la informacion recibida
   Lee_Socket (Socket_Cliente, (char *)&Aux, sizeof(Longitud_Cadena));

   // El entero recibido hay que transformarlo de formato red a formato hardware
   Longitud_Cadena = ntohl(Aux);
   printf ("Servidor C: Recibido %d\n", Longitud_Cadena-1);
  
   // Se lee la cadena
	Lee_Socket (Socket_Cliente, Cadena, Longitud_Cadena);
   printf ("Servidor C: Recibido %s\n", Cadena);

	//Se cierran los sockets
	close (Socket_Cliente);
	close (Socket_Servidor);
}
