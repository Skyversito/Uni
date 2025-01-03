#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define borrar_pantalla system("cls")
#include <locale.h>
#include <windows.h>


//Prototipo 1
struct trabajador 
{ 
	short ID; 
	char nombre[50]; 
	long dni; 
	float sueldo; 
	char cargo[16];
	char ZonaResidencia[16]; 
	char rendimiento[10];
	short eliminado;
	
}; 

struct trabajador* leerArchivo(int *cantidad); 
struct trabajador RegistrarEmpleado(); 
void guardarArchivo(struct trabajador* trabajadores, int cantidad); 
void modificarValor(struct trabajador* trabajadores, int cantidad); 
void MostrarEmpleados(struct trabajador* trabajadores, int cantidad); 
void OrdenarEmpleados(struct trabajador* trabajadores, int cantidad);
void Rendimientos(struct trabajador* trabajadores, int cantidad);
 void EliminarEmpleado (struct trabajador* trabajadores ,int cantidad);
void SueldoTotal (struct trabajador* trabajadores , int cantidad);
void CacheEmpleados(struct trabajador* trabajadores, int cantidad); 

int main(){ 
	
	struct trabajador* trabajadores = NULL; 
	int cantidad = 0; 
	short opcion; 
	short vuelta_menu;
	setlocale(LC_ALL, "spanish"); // Cambiar locale en Linux y Windows
	SetConsoleCP(1252); // Solo para Windows, necesaria
	SetConsoleOutputCP(1252); // Solo para Windows,necesaria
	SetConsoleTitle("Control de empleados"); //Probado en Windows 7, optativa
	
	
	trabajadores = leerArchivo(&cantidad); 
	
	do{ 
		
	printf("=========================================\n");	
		printf("\033[38;5;159mBienvenido al menu de gestion de personal\033[0m\n");
		printf("=========================================\n");
		printf("\033[38;5;1m1\033[0m. A�adir empleado\n");
		printf("\033[38;5;1m2\033[0m. Guardar Cambios ");	
		printf("\033[38;5;1m\n3\033[0m. Listar empleados\n");
		printf("\033[38;5;1m4\033[0m. Modificar empleado\n");
		printf("\033[38;5;1m5\033[0m. Rendimientos\n");
		printf("\033[38;5;1m6\033[0m. Eliminar empleado\n");
		printf("\033[38;5;1m7\033[0m. Calcular total de sueldos\n");
	    printf("\033[38;5;1m8\033[0m. Cache de empleados eliminados\n");
		printf("\033[38;5;1m0\033[0m. Salir\n");
		
	
		
		scanf("%hd",&opcion); 
        borrar_pantalla;
		
		switch (opcion) { 
		case 1: 
		    printf("\033[38;5;46m\nA�adiendo empleado...\n\033[0m");
			cantidad++; 
			trabajadores = realloc(trabajadores,cantidad*sizeof(struct trabajador)); 
			if(trabajadores == NULL){ 
				printf("Error al asignar memoria.\n"); 
				break; 
			} 
			trabajadores[cantidad-1]=RegistrarEmpleado(); 
			
			break; 
		case 2: 
			guardarArchivo(trabajadores,cantidad); 
			printf("\nDatos Guardado!\n\n");  
			
			break; 
			
		case 3: 
			
			do{
			    MostrarEmpleados(trabajadores,cantidad);  
				
				printf("\n\033[38;5;28mPara volver al menu presione '0'\033[0m\n");
				printf("\n\033[38;5;28mPara ordenar empleados por salario presione'1'\033[0m\n");
				scanf("%hd" , &vuelta_menu);
				
			}while(vuelta_menu != 0 && vuelta_menu != 1);
		    borrar_pantalla;
		    
			if(vuelta_menu == 1){
				
			OrdenarEmpleados(trabajadores , cantidad);
			printf("\n\033[38;5;28mPara volver al menu presione '0'\033[0m\n");
			scanf("%hd" , &vuelta_menu);
			borrar_pantalla;
			}
			
			
		
			break;
			 
			
		case 4: 
			modificarValor(trabajadores,cantidad); 
			break; 
			
		    
		case 5:
			borrar_pantalla;
		    do{
			Rendimientos(trabajadores, cantidad);	
		    printf("\n\033[38;5;28mPara volver al menu presione '0'\033[0m\n");
			scanf("%hd" , &vuelta_menu);
			
			}while(vuelta_menu != 0); 
			borrar_pantalla;
			break;
		    
		case 6:
			borrar_pantalla;
			for(int i=0;i<cantidad;i++){
			if(trabajadores[i].eliminado == 0){
				trabajadores[i].ID = 0;
			}	
			}
		    
			EliminarEmpleado(trabajadores , cantidad);
			
			
			
			break;
			
		case 7:
			SueldoTotal(trabajadores,cantidad);
			printf("\n\033[38;5;28mPara volver al menu presione '0'\033[0m\n");
			scanf("%hd" , &vuelta_menu);
			borrar_pantalla;
		break;	
		case 8:
		     //NO TERMINADO
			borrar_pantalla;
			CacheEmpleados(trabajadores, cantidad);
			
			break;
		case 0: 
			guardarArchivo(trabajadores,cantidad); 
			printf("\nDatos Guardados"); 
			break; 
			
			default: 
			printf("\nOpcion invalida\n"); 
			break; 
		} 
		
	}while(opcion != 0); 
	
	free(trabajadores); 
	
	return 0; 
} 


struct trabajador* leerArchivo(int *cantidad){ 
	FILE* archivo = fopen("InfoEmpleados.dat","rb"); 
	if(archivo == NULL) 
	{ 
		printf("No se encotro archivo. Primera vez en el sistema"); 
		return NULL; 
	} 
	
	fseek(archivo,0,SEEK_END); 
	*cantidad = ftell(archivo)/sizeof(struct trabajador); 
	fseek(archivo,0,SEEK_SET); 
	
	struct trabajador* trabajadores = (struct trabajador*) malloc ((*cantidad)*sizeof(struct trabajador)); 
	fread(trabajadores,sizeof(struct trabajador),*cantidad,archivo); 
	
	fclose(archivo); 
	return trabajadores; 
} 

struct trabajador RegistrarEmpleado(struct trabajador* trabajadores , int cantidad){ 
	struct trabajador aux; 
	
	
	
	
	printf("\nIngrese el ID: "); 
	scanf(" %hd",&aux.ID); 
	fflush(stdin);
	printf("\nIngrese el nombre: "); 
   scanf(" %[^\n]49s", aux.nombre);

	printf("\nIngrese el dni: ");
	scanf(" %ld", &aux.dni);
	printf("\ningrese sueldo: ");
	scanf(" %f" , &aux.sueldo);
	printf("\n Ingrese cargo: ");
	scanf(" %[^\n]15s" , aux.cargo);
	printf("\n Ingrese zona de residencia: ");
    scanf(" %[^\n]49s",aux.ZonaResidencia); 
	
	aux.eliminado = 1;
	
	return aux; 
	
} 

void guardarArchivo(struct trabajador* trabajadores, int cantidad){ 
	
	FILE* archivo = fopen("InfoEmpleados.dat","wb"); 
	if(archivo == NULL){ 
		printf("Error al guardar archivo\n"); 
		return; 
	} 
	
	fwrite(trabajadores,sizeof(struct trabajador),cantidad,archivo); 
	fclose(archivo);  
} 

void modificarValor(struct trabajador* trabajadores, int cantidad){ 
	short aux_ID; 
	printf("\nIngrese ID de empleado: "); 
	scanf("%hd",&aux_ID); 
	
	for(int i=0;i < cantidad;i++){ 
		
		if(aux_ID == trabajadores[i].ID){ 
			printf("\nA continuacion modifique los datos: "); 
			trabajadores[i]=RegistrarEmpleado(trabajadores, cantidad); 
			printf("\nDatos actualizados!\n\n"); 
			return; 
		} 
	} 
	printf("El ID no se encuentra registrado");  
	return; 
} 

void MostrarEmpleados(struct trabajador* trabajadores, int cantidad){ 
		
	
	
	if(cantidad==0) 
	{ 
		printf("\nNo hay empleados registrados..."); 
		return; 
	} 
	
	printf("Trabajadores: \n\n"); 
	
	printf("|%-15s           |%-15s               |  %-5s   | %-10s |   %-10s    |  %-10s   |\n", "\033[38;5;213mNombre\033[0m","\033[38;5;213mDNI\033[0m" ,"\033[38;5;213mID\033[0m", "\033[38;5;213mZona de Residencia\033[0m", "\033[38;5;213mCargo\033[0m", "\033[38;5;213mSalario\033[0m");
	printf("--------------------------------------------------------------------------------------------\n");
	
	
	for (int i = 0; i < cantidad; i++) {
	 if(trabajadores[i].eliminado == 1){
		 printf("| %-15s | %-15ld  | %-5d | %-18s | %-10s |\033[38;5;22m %-10.2f \033[0m|\n", 
			 trabajadores[i].nombre, 
			 trabajadores[i].dni,
			 trabajadores[i].ID, 
			 trabajadores[i].ZonaResidencia, 
			 trabajadores[i].cargo, 
			 trabajadores[i].sueldo);
		 printf("--------------------------------------------------------------------------------------------\n");
	 }
		
	}
	return; 
}

void OrdenarEmpleados(struct trabajador* trabajadores, int cantidad){
	struct trabajador auxiliar;
	short i , j;

	
	for(i = 0; i<cantidad ;i++){
		for(j = i + 1; j < cantidad;j++){
			if ((trabajadores[i].sueldo < trabajadores[j].sueldo)) {
				auxiliar = trabajadores[i];
				trabajadores[i] = trabajadores[j];
				trabajadores[j] = auxiliar;
			}
			
		}
	}
	printf("|%-15s         |%-15s           |   %-5s  | %-10s |   %-10s    |   %-10s  |\n", "\033[38;5;213mNombre\033[0m","\033[38;5;213mDNI\033[0m" ,"\033[38;5;213mID\033[0m", "\033[38;5;213mZona de Residencia\033[0m", "\033[38;5;213mCargo\033[0m", "\033[38;5;213mSalario\033[0m");
	printf("-----------------------------------------------------------------------------------------\n");
	

	for (int i = 0; i < cantidad; i++) {
		if(trabajadores[i].eliminado == 1){
		   
			printf("| %-15s | %-10ld | %-5d | %-18s | %-10s |\033[38;5;22m %-10.2f \033[0m|\n", 
			trabajadores[i].nombre, 
			trabajadores[i].dni,
			trabajadores[i].ID, 
			trabajadores[i].ZonaResidencia, 
			trabajadores[i].cargo, 
			trabajadores[i].sueldo);
			printf("------------------------------------------------------------------------------------------\n");	
		}
		
		
	}
	return; 
	
}

void Rendimientos(struct trabajador* trabajadores, int cantidad){
	short rendimiento;
	
	printf("\033[38;5;1m1\033[0m. Definir rendimientos / \033[38;5;1m2\033[0m. Analizar rendimientos\n");
	scanf("%hd" , &rendimiento);
	
	if(rendimiento == 1){
		for(int i=0;i<cantidad;i++){
			printf("%s:" , trabajadores[i].nombre);
			scanf("%s" , trabajadores[i].rendimiento);
		}
	   }
	if(rendimiento == 2){
	printf("|%-15s           | %-5s    |   %-10s    |   %-15s   |\n", "\033[38;5;213mNombre\033[0m","\033[38;5;213mID\033[0m", "\033[38;5;213mCargo\033[0m", "\033[38;5;213mRendimiento\033[0m");
		printf("----------------------------------------------------------\n");
		
		for (int i = 0; i < cantidad; i++) {
			printf("| %-15s | %-5d | %-10s | %-15s |", 
				trabajadores[i].nombre, 
				trabajadores[i].ID, 
				trabajadores[i].cargo,
				trabajadores[i].rendimiento);
			printf("\n----------------------------------------------------------\n");
		}	
	}
	
	
}

void SueldoTotal (struct trabajador* trabajadores , int cantidad){
	
	float total = 0;
	
	if(cantidad != 0)
	{
		for(short i = 0; i<cantidad; i++)
		{
			if(trabajadores[i].eliminado == 1){
				total += trabajadores[i].sueldo;
			}
			
		}
	}
	printf("Sueldo total de todos los empleados: %.2f\n",total);
	//return total;
}

void EliminarEmpleado (struct trabajador* trabajadores,int cantidad){
	short aux_ID; 
	char respuesta;
	
	
	printf("\nIngrese ID de empleado: "); 
	scanf(" %hd",&aux_ID); 

	
	for(int i=0;i < cantidad;i++){ 
	
	
		
	if(aux_ID == trabajadores[i].ID){ 
	printf("\nDesea eliminar a %s? s/n\n " , trabajadores[i].nombre); 
	scanf(" %c" , &respuesta);
	
	if(respuesta == 's'){
	trabajadores[i].eliminado = 0;
	trabajadores[i].ID = 0;
	
		printf("\nEmpleado %s eliminado correctamente!\n\n" , trabajadores[i].nombre);
     return;
	 }
	}
	if(respuesta == 'n'){
		borrar_pantalla;
		return;
		}
}
	printf("Empleado no registrado.");
	return;
}

void CacheEmpleados(struct trabajador* trabajadores, int cantidad){
    //NO TERMINADO
	long aux_DNI;
	short DNI_encontrado;
	
	if(cantidad==0) 
	{ 
		printf("\nNo hay empleados eliminados..."); 
		return; 
	} 
	
	printf("Trabajadores eliminados: \n\n"); 
	
	printf("|%-15s           |%-15s               |  %-5s   | %-10s |   %-10s    |  %-10s   |\n", "\033[38;5;213mNombre\033[0m","\033[38;5;213mDNI\033[0m" ,"\033[38;5;213mID\033[0m", "\033[38;5;213mZona de Residencia\033[0m", "\033[38;5;213mCargo\033[0m", "\033[38;5;213mSalario\033[0m");
	printf("--------------------------------------------------------------------------------------------\n");
	
	
	for (int i = 0; i < cantidad; i++) {
		if(trabajadores[i].eliminado == 0){
			printf("| %-15s | %-15ld  | %-5d | %-18s | %-10s |\033[38;5;22m %-10.2f \033[0m|\n", 
				trabajadores[i].nombre, 
				trabajadores[i].dni,
				trabajadores[i].ID, 
				trabajadores[i].ZonaResidencia, 
				trabajadores[i].cargo, 
				trabajadores[i].sueldo);
			printf("--------------------------------------------------------------------------------------------\n");
		}
		
	}
	printf("\n\033[38;5;22mIngrese DNI del empelado que quiera volver a incorporar o ingrese 0 para volver al menu:\n  \033[0m ");
	scanf("%ld" , &aux_DNI);
	if(aux_DNI){
		for(int i=0;i < cantidad;i++){ 
			DNI_encontrado = 0;
		
			if(aux_DNI == trabajadores[i].dni){ 
				DNI_encontrado = 1;
				printf("\nA continuacion reingrese los datos: "); 
				trabajadores[i]=RegistrarEmpleado(trabajadores, cantidad); 
				printf("\nDatos actualizados!\n\n"); 
				return; 
			} 
		
		} 
	
	}
	if(DNI_encontrado != 1 && aux_DNI != 0){
	
			borrar_pantalla;
			printf("\n\033[38;5;1mNo se encontro el DNI buscado\033[0m\n\n");
			
		
	}
	else if(aux_DNI==0){
		borrar_pantalla;
		return;
	}
		
	
	
	
	
}

/*short ID; 
char nombre[50]; 
long dni; 
float sueldo; 
char cargo[16];
char ZonaResidencia[16]; 
char rendimiento[10];*/

//
