#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

typedef struct {
    int codigo;
    char nombres[41];
    char apellidos[41];
    char puesto[41];
    float sueldoBase;
    float Bonificacion; 
} tEmpleado;


void continuar()
{
    printf("\nPresione una tecla para continuar\n\n");
    getch();
}

void crear()
{
    FILE *arch;
    arch=fopen("empleado.dat","wb");
    if (arch==NULL)
        exit(1);
    fclose(arch);
    continuar();
}


void cargar()
{
    FILE *arch;
    arch=fopen("empleado.dat","ab");
    if (arch==NULL)
        exit(1);
    tEmpleado Empleado;

    printf("Ingrese el codigo del empleado: ");
    scanf("%i",&Empleado.codigo);
    fflush(stdin);
    printf("Ingrese el nombre: ");
    gets(Empleado.nombres);
    printf("Ingrese el apellidos: ");
    gets(Empleado.apellidos);
    printf("Ingrese el Puesto: ");
    gets(Empleado.puesto);
    printf("Ingrese Sueldo base: ");
    scanf("%f",&Empleado.sueldoBase);
    printf("Ingrese bonificacion : ");
    scanf("%f",&Empleado.Bonificacion);
        
    fwrite(&Empleado, sizeof(tEmpleado), 1, arch);
    fclose(arch);
    continuar();
}

void listado()
{
    FILE *arch;
    arch=fopen("empleado.dat","rb");
    if (arch==NULL)
        exit(1);
    tEmpleado Empleado;
    fread(&Empleado, sizeof(tEmpleado), 1, arch);
    while(!feof(arch))
    {
       printf("_____________________\n\n codigo: %i\n nombres: %s \n apellidos: %s \n Puesto: %s\n Sueldo Base: %0.2f\n Bonificacion: %0.2f\n ", Empleado.codigo, Empleado.nombres,  Empleado.apellidos,  Empleado.puesto, Empleado.sueldoBase, Empleado.Bonificacion);
        fread(&Empleado, sizeof(tEmpleado), 1, arch);
    }
    fclose(arch);
    continuar();
}

void consulta()
{
    FILE *arch;
    arch=fopen("empleado.dat","rb");
    if (arch==NULL)
        exit(1);
    printf("Ingrese el codigo del empleado a consultar: ");
    int cod;
    scanf("%i", &cod);
    tEmpleado Empleado;
    int existe=0;
    fread(&Empleado, sizeof(tEmpleado), 1, arch);
    while(!feof(arch))
    {
        if (cod==Empleado.codigo)
        {
            printf("codigo: %i\n nombres: %s \n apellidos: %s \n Puesto: %s\n Sueldo Base: %0.2f\n Bonificacion: %0.2f\n ", Empleado.codigo, Empleado.nombres,  Empleado.apellidos,  Empleado.puesto, Empleado.sueldoBase, Empleado.Bonificacion);
           existe=1;
           break;
        }
        fread(&Empleado, sizeof(tEmpleado), 1, arch);
    }
    if (existe==0)
        printf("No existe el empleado con dicho codigo\n");
    fclose(arch);
    continuar();
}

void modificacion()
{
    FILE *arch;
    arch=fopen("empleado.dat","r+b");
    if (arch==NULL)
        exit(1);
    printf("Ingrese el codigo del empleado a modificar: ");
    int cod;
    scanf("%i", &cod);
    fflush(stdin);
    tEmpleado Empleado;
    int existe=0;
    fread(&Empleado, sizeof(tEmpleado), 1, arch);
    while(!feof(arch))
    {
        if (cod==Empleado.codigo)
        {
           printf("%i %s %s %s %0.2f\n", Empleado.codigo, Empleado.nombres,  Empleado.apellidos,  Empleado.puesto, Empleado.sueldoBase, Empleado.Bonificacion);
           printf("Ingrese nuevos nombres: ");
           gets(Empleado.nombres);
           printf("Ingrese nuevos apellidos: ");
           gets(Empleado.apellidos);
           printf("Ingrese nuevo puesto: ");
           gets(Empleado.puesto);
           printf("Ingrese nuevo sueldo base: ");
           scanf("%f",&Empleado.sueldoBase);
           printf("Ingrese nueva Bonificacion: ");
           scanf("%f",&Empleado.Bonificacion);
           int pos=ftell(arch)-sizeof(tEmpleado);
           fseek(arch,pos,SEEK_SET);
           fwrite(&Empleado, sizeof(tEmpleado), 1, arch);
           printf("\nSe modificaron los datos.\n");
           existe=1;
           break;
        }
        fread(&Empleado, sizeof(tEmpleado), 1, arch);
    }
    if (existe==0)
        printf("No existe un empleado con dicho codigo\n");
    fclose(arch);
    continuar();
}

void eliminar()
{
	printf("Ingrese el codigo del empleado a eliminar: ");
    int cod;
    scanf("%i", &cod);
	
	FILE *arch1;
    arch1=fopen("temp.dat","wb");
    if (arch1==NULL)
        exit(1);
    fclose(arch1);
	
	FILE *arch2;
    arch2=fopen("empleado.dat","rb");
    if (arch2==NULL)
        exit(1);
    tEmpleado Empleado;
    fread(&Empleado, sizeof(tEmpleado), 1, arch2);
    while(!feof(arch2))
    {
    	if (Empleado.codigo != cod) {
    		FILE *arch3;
		    arch3=fopen("temp.dat","ab");
		    if (arch3==NULL)
		        exit(1);
	    	fwrite(&Empleado, sizeof(tEmpleado), 1, arch3);
	    	fclose(arch3);
		}
       
       fread(&Empleado, sizeof(tEmpleado), 1, arch2);
    }
    fclose(arch2);
    
    remove("empleado.dat");
    rename("temp.dat", "empleado.dat");
    
    printf("\nSe eliminaron los datos.\n");
    continuar();
}

int main()
{
    int opcion;
    do {
        printf("1 - Crear un archivo llamado \"empleado.dat\"\n");
        printf("2 - Crear un nuevo registro \n");
        printf("3 - Listado completo de Registros\n");
        printf("4 - Consulta de Registros\n");
        printf("5 - Modificar un Registro \n");
        printf("6 - Eliminar un Registro \n");
        printf("7 - Finalizar\n\n");
        printf("Ingrese su opcion: ");
        scanf("%i",&opcion);
        switch (opcion) {
            case 1:crear();
                   break;
            case 2:cargar();
                   break;
            case 3:listado();
                   break;
            case 4:consulta();
                   break;
            case 5:modificacion();
                   break;
            case 6:eliminar();
                   break;
        }
    } while (opcion!=7);
    return 0;
}
