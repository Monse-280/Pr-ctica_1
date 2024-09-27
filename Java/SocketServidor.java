import java.net.*;
import java.io.*;

//Clase principal para instanciar un socket servidor,
//Se enlaza con un cliente que recibe una cadena 

public class SocketServidor
{    
    public static void main (String [] args){
        // Se instancia la clase principal
        new SocketServidor();
    }
    
    public SocketServidor(){
        try{
            // Se crea un socket servidor con un puerto definido.
            ServerSocket socket = new ServerSocket (15557);
            
            // recibe y acepta una conexion con un cliente la cual se mantiene inactivo hasta que se ejecute el cliente
            System.out.println ("En espera del cliente");
            Socket cliente = socket.accept();
            System.out.println ("Se establecio la coneccion con el cliente " + cliente.getInetAddress());
            cliente.setSoLinger (true, 10);

            // Se declara un dato para enviar.
            DatoSocket dato = new DatoSocket("Hola");

            // Se prepara un flujo de salida de datos para escribir en el socket
            DataOutputStream bufferSalida = new DataOutputStream (cliente.getOutputStream());
            
            // Enviamos el dato.
            dato.writeObject (bufferSalida);
            System.out.println ("Cliente Java: Enviado " + dato.toString());

            // Se prepara el flujo de entrada de datos para leer del socket
            DataInputStream bufferEntrada = new DataInputStream (cliente.getInputStream());

            // Se crea un dato para leer lo que fue enviado 
            DatoSocket aux = new DatoSocket("");
            aux.readObject (bufferEntrada);
            System.out.println ("Cliente java: Recibido " + aux.toString());
            
            // Se cierra el socket con el cliente.
            cliente.close();
            
            // Se cierra el socket encargado de aceptar clientes
            socket.close();
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}
