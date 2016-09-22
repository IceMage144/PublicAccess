       EXTERN  puts
s      IS      $0
puts   SUBU    s,rSP,16  Carrega endereco do primeiro caractere.
       LDOU    s,s,0
       SETW    rX,2
write  LDB     rY,s,0    Carrega caractere atual.
       JZ      rY,end
       INT     #80
       ADDU    s,s,1     Pula para o proximo caractere.
       JMP     write
end    RET     1