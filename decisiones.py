# (Materia: informática) Ejercicios resueltos de la guia 4. Decisiones 

# Ejercicio 4.1.a
def es_par(num_entero):
    '''Recibe un número entero y devuelve un valor booleano si es par o no'''
    par = num_entero%2 == 0    
    if par:
        return True
    else:
        return False
    
# Ejercicio 4.1.b
def es_par_modificado(num_entero):
    '''Recibe por parámetro un número entero y devuelve (S)-> si es par (N)->si es impar (O)->si es cero'''
    cero = num_entero == 0
    par = num_entero%2 == 0
    if cero:
        return 'O'
    elif par:
        return 'S'
    elif not par:
        return 'N'
    
# Ejercicio 4.2
def val_abs(a):
    '''Recibe un número por parámetro y devuelve su valor absoluto'''
    if(a == 0):
        return 0
    elif(a < 0):
        return a + (a*-2)
    else:
        return a
    
# Ejercicio 4.3
def mayor_de_3(a, b, c):
    '''Recibe tres números por parámetros y devuelve el número mayor ingesado'''
    mayor=0
    if(a>b and a>c):
        mayor = a
    elif(b>a and b>c):
        mayor = b
    else:
        mayor = c

    return mayor

# Ejercicio 4.4
def multiplo_de_3_y_5():
    print("Ingrese dos numeros naturales")
    n1 = int(input("Ingrese el primer número (que sea menor al sigueinte número): "))
    n2 = int(input("Ingrese el segundo número: "))
    
    if(n1<n2):
        for x in range(n1,n2+1):
            multiplo_3 = x%3 == 0
            multiplo_5 = x%5 == 0
            if (multiplo_3 == True and multiplo_5 == True):
                print("TRES Y CINCO")
            elif multiplo_5:
                print("CINCO")
            elif multiplo_3:
                print("TRES")
            else:
                print(x)
        
# Ejercicio 4.5
def es_bisiesto(x):
    '''Recibe un año por parametro y devuelve un booleano si es bisiesto o no'''
    multiplo_de_4 = x%4 == 0
    multiplo_de_100 = x%100 == 0
    multiplo_de_400 = x%400 == 0

    if((multiplo_de_4 and not multiplo_de_100) or multiplo_de_400):
        return True
    else:
        return False

# Ejercicio 4.6
def cant_dias_mes(mes, anio):
    '''Recibe por parámetro el mes y año y devuelve la cantidad de días que tiene el mes'''
    bi = es_bisiesto(anio)

    if bi and mes == 2:
        return 29
    elif not bi and mes == 2:
        return 28
    elif mes == 1 or mes == 3 or mes == 5 or mes == 7 or mes == 8 or mes == 10 or mes == 12:
                return 31
    else:
        return 30

# Ejercicio 4.7
def fecha_valida(dia, mes, anio):
    cant_dias = cant_dias_mes(mes, anio)
    
    if dia > 0 and dia <= cant_dias:
        return True
    else:
        return False


    
#--------Ejercicios Opcionales-------------------

# Ejercicio 4.13
def signo_zodiaco():
    '''El usuario ingresa el día y el mes y la funcion imprime su signo del zodíaco'''
    print('Ingrese su dia y mes de nacimiento')
    dia = int(input('Ingrese el día: '))
    mes = int(input('Ingrese el mes: '))
    if(mes == 1 and dia >= 21 or mes == 2 and dia <= 19):
        print('Acuario')
    elif(mes == 2 and dia >= 20 or mes == 3 and dia <= 20):
        print('Piscis')
    elif(mes == 3 and dia >= 21 or mes ==4 and dia <= 20):
        print('Aries')
    elif(mes == 4 and dia >= 21 or mes == 5 and dia <= 20):
        print('Tauro')
    elif(mes == 5 and dia >= 21 or mes == 6 and dia <= 20):
        print('Geminis')
    elif(mes == 6 and dia >= 21 or mes == 7 and dia <= 21):
        print('Cáncer')
    elif(mes == 7 and dia >= 22 or mes == 8 and dia <= 22):
        print('Cáncer')
    elif(mes == 8 and dia >= 23 or mes == 9 and dia <= 22):
        print('Virgo')
    elif(mes == 9 and dia >= 23 or mes == 10 and dia <= 22):
        print('Libra')
    elif(mes == 10 and dia >= 23 or mes == 11 and dia <= 22):
        print('Escorpio')
    elif(mes == 11 and dia >= 23 or mes == 12 and dia <= 21):
        print('Sagitario')
    elif(mes == 12 and dia >= 22 or mes == 1 and dia <= 20):
        print('Capricornio')


def main():
    # Ejercicio 4.1
    print("Es valor es: ", es_par(1))
    
    # Ejercicio 4.2
    print("El valor absoluto es: ", val_abs(0))

    # Ejercicio 4.3
    for ternas in range(6):
        num_1 = int(input("Ingrese 1° número: "))
        num_2 = int(input("Ingrese 2° número: "))
        num_3 = int(input("Ingrese 3° número: "))
        print("El mayor es: ", mayor_de_3(num_1, num_2, num_3))
        
    # Ejercicio 4.4
    multiplo_de_3_y_5()
    
    # Ejercicio 4.5
    es_bisiesto(2000)

    # Ejercicio 4.13
    signo_zodiaco()

    #Borrar lo anterior e ir invocando cada función

main()



