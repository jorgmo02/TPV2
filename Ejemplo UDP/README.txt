Ejecutarlo como siempre

   TPV2 server 2000
   TPV2 client localhost 2000

Si comparas los 2 ejemplos creo que lo vas a entender bastante
bien. No hay nada difícil.

Los mas importante entender a la hora de trabajar con UDP es:


- Lo que se envía son packets (UDPpacket)

- No está garantizado que los paquetes llegan, tampoco en orden, pero
  eso depende de tu aplicación, yo no lo tengo en cuenta en ese
  ejemplo.

- No establecemos conexión, cada vez que enviamos mensajes decimos a
  quien queremos enviarlo

- No se puede identificar cuando un cliente desconecta, tiene que
  avisar con mensaje adecuado. En ejemplo puedes ver que capturo el
  CTRL-C para envira un mensaje adecuado, con TCP era suficiente
  cerrar el socket.

- No sé si lo del CTRL-C compila en windows, si no puedes quitar la
  primera linea del main y el método sigintHandler

