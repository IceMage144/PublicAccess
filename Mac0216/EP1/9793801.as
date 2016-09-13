reader      IS     $0
EOT         IS     $1
col         IS     $2
comp        IS     $3
count       IS     $4
spaces      IS     $5
xspaces     IS     $6
newspaces   IS     $7
aux         IS     $8
auxII       IS     $9
mem         IS     $10
i           IS     $11
j           IS     $12
k           IS     $13
            EXTERN main
main        SETW   rX,1
            SUBU   rSP,rSP,28
readCols    LDBU   aux,rSP,0                     *Lê o número de colunas da
            CMPU   comp,aux,48                   *linha de comando
            JN     comp,endRC
            CMPU   comp,aux,57
            JP     comp,endRC
            MULU   col,col,10
            SUBU   aux,aux,48
            ADDU   col,col,aux
            ADDU   rSP,rSP,1
            JMP    readCols
endRC       XOR    EOT,EOT,EOT
            XOR    aux,aux,aux
readNStore  INT    #80                           *Lê o texto e o guarda na
            JN     rA,endRNS                     *memória
            CMPU   comp,rA,10
            JNZ    comp,5
            CMPU   comp,auxII,2
            JZ     comp,readNStore
            ADDU   auxII,auxII,1
            JMP    readNStore
            CMPU   comp,rA,32
            JP     comp,8
            CMPU   comp,auxII,0
            JP     comp,readNStore
            CMPU   comp,aux,1
            JZ     comp,readNStore
            SETW   aux,1
            SETW   rA,32
            JMP    17
            XOR    aux,aux,aux
            CMPU   comp,auxII,1
            JNZ    comp,6
            SETW   mem,32
            STBU   mem,EOT,0
            ADDU   EOT,EOT,1
            XOR    auxII,auxII,auxII
            JMP    9
            CMPU   comp,auxII,2
            JNZ    comp,7
loop        JZ     auxII,6
            SETW   mem,10
            STBU   mem,EOT,0
            ADDU   EOT,EOT,1
            SUBU   auxII,auxII,1
            JMP    loop
            STBU   rA,EOT,0
            ADDU   EOT,EOT,1
            JMP    readNStore
endRNS      SETW   rX,2
            SETW   mem,10
            STBU   mem,EOT,0
            ADDU   EOT,EOT,1
readingLine CMPU   comp,count,EOT
            JZ     comp,end
            XOR    spaces,spaces,spaces
            XOR    xspaces,xspaces,xspaces
            XOR    newspaces,newspaces,newspaces
            XOR    i,i,i
countSpcs   CMPU   comp,i,col                    *Conta os espaços da linha
            JNN    comp,endCS
            LDBU   reader,i,count
            CMPU   comp,reader,10
            JZ     comp,6
            CMPU   comp,reader,32
            JNZ    comp,2
            ADDU   spaces,spaces,1
            ADDU   i,i,1
            JMP    countSpcs
endCS       LDBU   reader,i,count
notspaced   CMPU   comp,reader,32                *Entra aqui se a linha não
            JZ     comp,spaced                   *está espaçada corretamente
            CMPU   comp,reader,10
            JZ     comp,spaced
countXspcs  LDBU   reader,i,count                *Calcula quantos espaços a
            CMPU   comp,reader,32                *mais na linha serão precisos
            JZ     comp,isOneWord
            JZ     i,isOneWord
            ADDU   xspaces,xspaces,1
            SUBU   i,i,1
            JMP    countXspcs
isOneWord   CMPU   comp,spaces,1                 *Entra aqui se a linha tiver
            JP     comp,isMoreWords              *só uma palavra
            XOR    i,i,i
printLine   LDBU   reader,i,count
            CMPU   comp,reader,32                *Printa a palavra
            JZ     comp,loopback
            CMPU   comp,reader,10
            JZ     comp,loopback
            OR     rY,reader,0
            INT    #80
            ADDU   i,i,1
            JMP    printLine
isMoreWords SUBU   spaces,spaces,1               *Entra aqui se a linha tiver
            DIVU   newspaces,xspaces,spaces      *mais de uma palavra
            ADDU   newspaces,newspaces,1
setSpaces   CMPU   comp,newspaces,1              *Calcula o novo espaçamento
            JNP    comp,endResize
resize      CMPU   comp,xspaces,spaces
            JN     comp,endResize
            SUBU   xspaces,xspaces,spaces
            JMP    resize
endResize   XOR    j,j,j
printSpcdLn CMPU   comp,j,i                      *Printa a linha com o novo
            JZ     comp,loopback                 *espaçamento
            LDBU   reader,j,count
printWord   CMPU   comp,reader,32
            JZ     comp,printSpaces
            OR     rY,reader,0
            INT    #80
            ADDU   j,j,1
            JMP    printSpcdLn
printSpaces XOR    k,k,k
new         CMPU   comp,k,newspaces
            JZ     comp,extra
            SETW   rY,32
            INT    #80
            ADDU   k,k,1
            JMP    new
extra       CMPU   comp,spaces,xspaces
            JP     comp,2
            INT    #80
            SUBU   spaces,spaces,1
            ADDU   j,j,1
            JMP    printSpcdLn
spaced      XOR    j,j,j                         *Entra aqui se a linha já está
printLineII CMPU   comp,j,i                      *espaçada corretamente
            JZ     comp,loopback
            LDBU   reader,j,count
            OR     rY,reader,0
            INT    #80
            ADDU   j,j,1
            JMP    printLineII
loopback    SETW   rY,10                         *Faz os preparativos para o
            INT    #80                           *próximo loop
            ADDU   count,i,count
            ADDU   count,count,1
            JMP    readingLine
end         INT    0                             *Finaliza o programa