#$0 -> zero
#$1 -> EOT
#$2 -> col
#$3 -> comparações
#$4 -> parágrafos
#$5 -> count
#$6 -> spaces
#$7 -> xspaces
#$8 -> newspaces
#$9 -> i
#$a -> len(linha)
#$b -> redparag
#$c -> reader
#$d -> redchar
#$e -> auxiar

def main():
    col = int(input("Quantas colunas?\n")) #$2
    xspaces = 0 #$7
    spaces = 0 #$6
    newspaces = 0 #$8
    f = open("texto.txt", mode="r")
    for linha in f:
        count = 0 #$5
        while count < len(linha):
            spaces = 0
            xspaces = 0
            newspaces = 0
            i = 0 #$9
            while i < col and linha[i+count] != '\n':
                if linha[i+count] == ' ':
                    spaces += 1
                i += 1
            if linha[i+count] != ' ' and linha[i+count] != '\n':
                while linha[i+count] != ' ' and i != 0:
                    i -= 1
                    xspaces += 1
                if (spaces <= 1):
                    i = 0
                    while (linha[i+count] != ' ' and linha[i+count] != '\n'):
                        print(linha[i+count], end='')
                        i += 1
                else:
                    spaces -= 1
                    newspaces = (xspaces//spaces)+1
                    if newspaces > 1:
                        while xspaces >= spaces:
                            xspaces -= spaces
                    for j in range(i):
                        if linha[j+count] != ' ':
                            print(linha[j+count], end='')
                        else:
                            for k in range(newspaces):
                                print('_', end='')
                            if spaces <= xspaces:
                                print('_', end='')
                            spaces -= 1
            else:
                for j in range(i):
                    if linha[j+count] != ' ':
                        print(linha[j+count], end='')
                    else:
                        print('_', end='')
            print()
            count += i+1
        #loop para voltar no count < len(linha)
    #loop para voltar no for linha in f

if __name__ == '__main__':
	main()