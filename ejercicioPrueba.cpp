#include <iostream>
#include <cstdlib>
#include <string.h>
#include <c:\Temp\archivosg.h>
using namespace std;

#define TOPEPROV 24
#define TOPEREGION 5
#define TOPEPAQ 4
#define TOPENOM 21

struct tyencomienda{
       int		peso;
	   char 	provdestino[TOPENOM];
       char		tipoenvio;
};
struct typrecio{
		float 	simple;
		float	certif;
}; 

struct tytipopaq{
       string 	descpaq;
       int 		pesod;
       int		pesoh;
};

struct typrov{
       char 	prov[TOPENOM];
       int		region;
};

struct tyVariables{
	int ing_peso;
	int ing_prov;
	char ing_tipo_envio;
};

struct tyMatriz{
	float importe;
	float importe_total;
};

void cargar_vec_provincias(typrov v_provincias[], char arch[], int tope)
{
	typrov registro;
	bool pude = false, finArch = false;
	FILE *fichero=NULL;
	int largo = sizeof(registro);
	char lee[] = "rb";
	abrirArch(arch, lee, fichero, pude);
	if (pude)
	{
		leerArch(fichero, &registro, largo, finArch, pude);
		int i = 0;
		while(pude && !finArch && i < tope)
		{		
			v_provincias[i] = registro;			
			i++;
			leerArch(fichero, &registro, sizeof(registro), finArch, pude);
		}
		cout<<endl;
		cerrarArch(fichero);
	}
	else
	{
		cout<<"Archivo no encontrado...";
	}
}

int busca_peso(int peso, tytipopaq vector[], int tope)
{
	int i = 0;
	bool flag = false;
	while(i < tope && !flag)
	{
		if(peso >= vector[i].pesod  && peso <= vector[i].pesoh)
		{
			flag = true;
		}
		else
		{
			i++;
		}		
	}
	if(i == tope)
	{
		i = -1;
	}
	return i;
}

int busca_provincia(char prov[], typrov vecProv[],int tope)
{
	int i = 0;	
	while(i < tope && strcmp(vecProv[i].prov, prov) != 0)
	{
	    i++;
	}
	if(i == tope)
	{
		i = -1;
	}
	return i;
}

float busca_simple_o_certif(char opt, int indice, typrecio vec[])
{
	float precio;
	if(opt == 'S'){
		precio = vec[indice].simple;
	}else
	{
		precio = vec[indice].certif;
	}
	return precio;
}

void menu(int &opt)
{
	cout << "                 Ingrese Peso del Paquete   " << endl; 
	cout << "sobre chico: [DE 1 a 200] *** sobre grande: [DE 201 a 350]" << endl;
	cout << "caja chica: [DE 351 a 500] *** caja grande: [DE 501 a 999]" << endl;
	cout << "[-1 para finalizar]: ";
	cin >> opt;
	cout << endl;
}

void ingreso_datos(tyVariables &ing, tytipopaq tytipopaq[], typrov vecProv[], string vecRegion[], typrecio vecPre[], int t_paq)
{
	menu(ing.ing_peso);
	
	if(ing.ing_peso != -1)
	{
		while(busca_peso(ing.ing_peso, tytipopaq, t_paq) == -1){
			cout << "Ingrese un peso adecuado!" << endl;
			menu(ing.ing_peso);
			busca_peso(ing.ing_peso, tytipopaq, t_paq);
		}
		
		cout << "Ingrese El numero de provincia [de 1 a 24]: ";
		cin >> ing.ing_prov;
		while(ing.ing_prov < 1 || ing.ing_prov > 24)
		{
			cout << "Ingrese un numero de provincia correcto!" << endl;
			cout << "Ingrese El numero de provincia [de 1 a 24]: ";
		    cin >> ing.ing_prov;
		}
						
		cout << "Ingrese tipo de envío ('S' - Simple / 'C' - Certificado): ";
		cin >> (ing.ing_tipo_envio);

		while(ing.ing_tipo_envio != 'S' && ing.ing_tipo_envio != 'C'){
			cout << "Ingrese tipo de envío ('S' - Simple / 'C' - Certificado): ";
	     	cin >> (ing.ing_tipo_envio);
		}
	}	
}

void inicializa_matriz(float m[][TOPEREGION], int t_tq, int t_reg)
{
	for(int i = 0; i < t_tq; i++)
	{
		for(int j = 0; j < t_reg; j++)
		{
			m[i][j] = 0.00;
		}
	}
}

void inicializa_vec(int v[], int tope)
{
	for(int i = 0; i < tope; i++)
	{
		v[i] = 0;
	}
}

void mostrar_tipo_envio_importe(float m[][TOPEREGION], tytipopaq v_paq[], string v_reg[], int t_tq, int t_reg)
{
	for(int i = 0; i < t_tq; i++)
	{
		cout << "Tipo envio: [" << v_paq[i].descpaq << "]" << endl;
		for(int j = 0; j < t_reg; j++)
		{			
			cout << "El importe recaudado en la region " << v_reg[j] << " es: "  << m[i][j] << endl;
		}
		cout << "*************************************************************************************" << endl;
		cout << endl;
	}
}

void muestra_region_importe(string region, float import)
{
	cout << "\\-" << endl;
	cout << region << " importe a facturar: " << import << endl;
	cout << "\\-" << endl;
}

void busca_region_importe(int cont_env_prov[], tyVariables &ing, typrov v_prov[], string v_reg[], float m[][TOPEREGION], tytipopaq v_paq[], typrecio v_precio[], int t_tq, int t_reg)
{
	int indxPaq = busca_peso(ing.ing_peso, v_paq, t_tq);	
	int idxPrv = ing.ing_prov - 1;
	cont_env_prov[idxPrv]++;
	int indxReg = v_prov[idxPrv].region;
	float importe = busca_simple_o_certif(ing.ing_tipo_envio, indxPaq, v_precio);
	m[indxPaq][indxReg] += importe;
	muestra_region_importe(v_reg[indxReg], importe);
}

void busca_prov_may_envios(int v_cont[], typrov v_prov[], int t_prov)
{
	int mayor = 0;
	int pos;
	for(int i = 0; i < t_prov; i++)
	{
		if(v_cont[i] > mayor)
		{
			mayor = v_cont[i];
			pos = i;		
		}
	}
	
	cout << "La provincia que recibio la mayor cantidad de envios fue: " << v_prov[pos+1].prov;
}

int main(){
	tytipopaq tytipopaq[TOPEPAQ]={"sobre chico",1,200,"sobre grande",201,350,"caja chica",351,500,"caja grande",501,999};
	typrov vecProv[TOPEPROV]; //={"CABA",0,"Buenos Aires",0,"Catamarca",1,"Chaco",1,"Chubut",3,i"Cordoba",4,"Corrientes",1,"Entre Ríos",4,"Formosa",1,"Jujuy",1,"La Pampa",3,"La Rioja",2,"Mendoza",2,"Misiones",1,"Neuquén",3,"Río Negro",3,"Salta",1,"San Juan",2,"San Luis",2,"Santa Cruz",3,"Santa Fe",4,"Santiago del Estero",1,"Tierra del Fuego",3,"Tucumán",1};
    string vecRegion[TOPEREGION]={"Region BsAs y CABA", "Region del Norte Grande Argentino","Region del Nuevo Cuyo","Region de la Patagonia","Region Centro"};
	typrecio vecPre[TOPEPAQ]={30,35,50,60,70,100,90,120}; // vector de precios de encomiendas, por tipo de paquete y  según tipo de envío ( simple y certificada)
    tyVariables ingreso;
    float m[TOPEPAQ][TOPEREGION];
    int cont_env_prov[TOPEPROV];
    char arch_prov[] = "provincias.dat";
	cargar_vec_provincias(vecProv, arch_prov, TOPEPROV);
	inicializa_matriz(m, TOPEREGION, TOPEPROV);
	inicializa_vec(cont_env_prov, TOPEPROV);
	
	ingreso_datos(ingreso, tytipopaq, vecProv, vecRegion, vecPre, TOPEPAQ);
	while(ingreso.ing_peso != -1)
	{
		busca_region_importe(cont_env_prov, ingreso, vecProv, vecRegion, m, tytipopaq, vecPre, TOPEPAQ, TOPEREGION);	
		ingreso_datos(ingreso, tytipopaq, vecProv, vecRegion, vecPre, TOPEPAQ);
	}
	mostrar_tipo_envio_importe(m, tytipopaq, vecRegion, TOPEPAQ, TOPEREGION);
	busca_prov_may_envios(cont_env_prov, vecProv, TOPEPROV);	
}
