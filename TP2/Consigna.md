# Trabajo Práctico #2 – "Logística"

Listas encadenadas

## 1. Enunciado

Un operador logístico lleva registro de sus envíos y genera un archivo binario con los datos de los movimientos hechos en el día. El archivo tiene un registro por cada uno de los envíos hechos desde su depósito central, con la siguiente estructura.

- Ciudad: nombre de la ciudad destino, string serializado con un largo de 14 caracteres.
- Código de transportista: Entero con valores de cero a cinco.
- Producto: string serializado con un largo de 10 caracteres.
- Unidades: Entero
- Monto: valor total del envío, declarado al seguro. Float.

Se tiene también un archivo de texto con los nombres correspondientes a los códigos de los transportistas.

Se pide:

1. Leer los archivos y cargar las estructuras de datos que se consideren necesarias.
2. Emitir un listado que informe, para cada ciudad: total de unidades despachadas y sumatoria de los montos asegurados. A continuación para cada transportista, utilizando el nombre del mismo, la cantidad de envíos hechos por el mismo a la ciudad en cuestión. Luego deben listarse los envíos a dicha ciudad con las columnas: producto, unidades y monto. Debe ordenarse el listado por producto y hacer un corte de control por dicho campo, informando los totales correspondientes.

   Nota: El total general no hace falta, ya que fue informado previamente.
3. Informe a que ciudad se hizo el menor total de unidades despachadas.
4. Para la ciudad informada en el punto anterior, haga un loop pidiendo el nombre de un producto. Busque en los envíos hechos e informe cuantos envíos de ese producto a esa ciudad se hicieron.

**Consideraciones:** Utilice un criterio de comparación en todos los casos donde sea aplicable. Utilice los headers entregados en el aula virtual para manejo de archivos binarios y listas.

## 2. Modo de entrega

En el repositorio del grupo en github se subirá el fuente, nombrado como main.cpp según la siguiente estructura:

```text
-- 26-XXX-YY
   -- TP2 // Carpeta para este TP
      |-- readme.md // Breve descripción del TP e integrantes
      |-- main.cpp // Archivo fuente del programa
```

Donde XXX son los últimos 3 dígitos de su curso y YY es el número del grupo, es decir, el repositorio asignado.

Una vez que terminen, el modo de entrega, o sea de avisar que ya está listo para corregir, es poner un anuncio en la parte de discusiones.

## 3. Fechas de entrega

Última fecha para hacer una primera entrega: 05/11

Última fecha entrega: 26/11