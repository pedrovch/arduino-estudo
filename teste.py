cont = -1
while cont < 150:
    cont = cont +1
    if cont % 7 != 0 and cont % 11 != 0:
        print(cont)

    if cont % 7 == 0 and cont % 11 != 0:
        print('Múltiplo de 7')

    if cont % 11 == 0 and cont % 7 != 0:
        print('Múltiplo de 11')    

    if cont % 7 == 0 and cont % 11 == 0:
        print('Múltiplo de 7 e 11')    