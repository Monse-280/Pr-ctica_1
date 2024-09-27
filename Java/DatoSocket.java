import java.io.*;

 // Dato para enviar por el socket

public class DatoSocket implements Serializable{
    
   //Se guarda la cadena en el atributo d y calcula su longitud para guardarla en el atricuto c.
   public DatoSocket (String cadena){
      
        // Si la cadena no es null, se guarda la cadena y su longitud 
        if (cadena != null){
            dime = cadena.length();
            cade = cadena;
        }
   }

   // Atributo entero para la dimension
   public int dime = 0;
     
   // Atributo String para la cadena
   public String cade = "";
     
   // Metodo para devolver un String
   public String toString (){
       String resultado;
       resultado = Integer.toString(dime) + " -- " + cade;
       return resultado;
   }

   // Metodo para escribir los atributos en un DataOutputStream de forma adecuada para que lo entienda un programa en c
   public void writeObject(java.io.DataOutputStream out) throws IOException{
         
        // Se envia la longitud y la cadena
        out.writeInt (dime+1);
        out.writeBytes (cade);
        out.writeByte ('\0');
   }
    
      // Metodo que lee los atributos de un DataInputStream recibidos de un progrma en C
     public void readObject(java.io.DataInputStream in) throws IOException{
         // Se lee la longitud de la cadena y se le resta 1 para eliminar el \0 que se recibe de c
         dime = in.readInt() - 1;
         
         // Array para la lectura de la cadena.
         byte [] aux = null;
         aux = new byte[dime];    // Se le da el tamano 
         in.read(aux, 0, dime);   // Se leen los bytes
         cade = new String (aux); // Se convierten a String
         in.read(aux,0,1);     // Se lee el \0
     }
}
