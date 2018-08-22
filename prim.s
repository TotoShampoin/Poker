
;------ Transforme en posit2ion mémoire une posit2ion X,Y (PLOT)
CALCPOS
.(
 LDA #$BB
 STA posit2+1
 CLC
 LDA #$80
 ADC COL
 LDX LIG
 BEQ F1
F2
 ADC #$28
 BCC F3
 INC posit2+1
 CLC
F3
 DEX
 BNE F2
F1
 STA posit2
 RTS
.)

posit2 .dsb 2
COL .dsb 1
LIG .dsb 1

;----- Affiche à la posit2ion posit2 le texte spécifié en ($0A)
PRINT
.(
 LDA posit2
 LDX posit2+1
 STA $0C
 STX $0D
 LDY #$0
G1
 LDA ($0A),Y
 BEQ G2
 STA ($0C),Y
 INY
 BEQ G2
 JMP G1
G2
 RTS
.)

;----- Liste des Textes à afficher : 2 / 4 / 8 / 16 / 32 ... 65536 (mais bon...)
TXT0
.byt $20,$20,$20,$20,$20,$00,$20,$20,$20,$20,$20,$00
TXT1
.byt $20,$20,$32,$20,$20,$00,$20,$20,$20,$20,$20,$00
TXT2
.byt $20,$20,$34,$20,$20,$00,$20,$20,$20,$20,$20,$00
TXT3
.byt $20,$20,$38,$20,$20,$00,$20,$20,$20,$20,$20,$00
TXT4
.byt $20,$31,$36,$20,$20,$00,$20,$20,$20,$20,$20,$00
TXT5
.byt $20,$33,$32,$20,$20,$00,$20,$20,$20,$20,$20,$00
TXT6
.byt $20,$36,$34,$20,$20,$00,$20,$20,$20,$20,$20,$00
TXT7
.byt $20,$31,$32,$38,$20,$00,$20,$20,$20,$20,$20,$00
TXT8
.byt $20,$32,$35,$36,$20,$00,$20,$20,$20,$20,$20,$00
TXT9
.byt $20,$35,$31,$32,$20,$00,$20,$20,$20,$20,$20,$00
TXT10
.byt $03,$70,$71,$72,$07,$00,$03,$20,$20,$20,$07,$00
TXT11
.byt $05,$73,$74,$75,$07,$00,$05,$20,$20,$20,$07,$00
TXT12
.byt $05,$76,$77,$78,$07,$00,$05,$20,$20,$20,$07,$00
TXT13
.byt $20,$38,$31,$20,$20,$00,$20,$39,$32,$20,$20,$00
TXT14
.byt $20,$31,$36,$20,$20,$00,$20,$33,$38,$34,$20,$00
TXT15
.byt $20,$33,$32,$20,$20,$00,$20,$37,$36,$38,$20,$00
TXT16
.byt $20,$36,$35,$20,$20,$00,$20,$35,$33,$36,$20,$00
TXT17
.byt $04,$0A
.asc "GAGNE"
.byt $07,$08,$00

TXTPTRL 
 .byt >TXT0
 .byt >TXT1
 .byt >TXT2
 .byt >TXT3
 .byt >TXT4
 .byt >TXT5
 .byt >TXT6
 .byt >TXT7
 .byt >TXT8
 .byt >TXT9
 .byt >TXT10
 .byt >TXT11
 .byt >TXT12
 .byt >TXT13
 .byt >TXT14
 .byt >TXT15
 .byt >TXT16

TXTPTRH
 .byt <TXT0
 .byt <TXT1
 .byt <TXT2
 .byt <TXT3
 .byt <TXT4
 .byt <TXT5
 .byt <TXT6
 .byt <TXT7
 .byt <TXT8
 .byt <TXT9
 .byt <TXT10
 .byt <TXT11
 .byt <TXT12
 .byt <TXT13
 .byt <TXT14
 .byt <TXT15
 .byt <TXT16

;----- tableau des données principales

_CA .byt $0,$2,$0,$0,$3,$0,$5,$9,$2,$0,$0,$B,$A,$C,$D,$E

;--- variable temporaire

PGTMP .byt $00
 .byt $00,$00 ;-- attention au débordement mémoire...
 
;---- affichage du contenu du tableau

_REFRESH
.(
 LDX #$00  ; compteur de lignes
 LDY #$00  ; compteur de colonness
ETIQ
 TXA
 PHA
 ASL
 ASL
 CLC
 ADC #$8  ; on multiplie par 4 et on ajoute 8 pour avoir la posit2ion à l'écran de la ligne X
 STA LIG
 TYA
 PHA
 STA COL
 ASL
 ADC COL
 ASL
 ADC #$B
 STA COL ; on multiplie par 6 et on ajoute 12 pour avoir la posit2ion de la colonne Y
 JSR CALCPOS ; La commande PRINT a maintenant la posit2ion à laquelle écrire
 PLA
 TAY
 PLA
 TAX
 TXA  ; instruction inutile, c'est pour marquer le coup
 PHA
 ASL
 ASL
 STA PGTMP  ; on multiplie la ligne X par 4
 TYA
 PHA
 CLC
 ADC PGTMP  ; on ajoute Y ==> A contient un indice dans le vecteur CA
 TAX
 LDY _CA,X  ; on charge la valeur de _CA[X] dans Y. Il faut ensuite aller chercher la chaîne correspondante
 LDA TXTPTRL,Y  ; via un tableau de pointeurs
 STA $0B
 LDA TXTPTRH,Y
 STA $0A
 JSR PRINT
 LDA $0A
 CLC
 ADC #$6
 STA $0A
 BCC H3
 INC $0B
 CLC
H3
 INC LIG
 JSR CALCPOS
 JSR PRINT 
 PLA
 TAY 
 PLA
 TAX
 INY
 TYA
 SEC
 SBC #$4
 BEQ H4
 JMP ETIQ
H4
 LDY #$0
 INX
 TXA
 SEC
 SBC #$4
 BEQ H5
 JMP ETIQ
H5 
 LDA _TOPGAGNE
 BEQ H6
 LDA #>TXT17
 STA $0B
 LDA #<TXT17
 STA $0A
 LDA #$0D
 STA LIG
 LDA #$01
 STA COL
 JSR CALCPOS
 JSR PRINT
 LDA #$0C
 STA LIG
 LDA #$01
 STA COL
 JSR CALCPOS
 JSR PRINT
H6
 RTS
.)

;-- code MONASM original ORG $7200
;--- Redéfinition des caractères  bord du tableau
CHARAC
 .byt $00,$00,$00,$3F,$3F,$00,$00,$00
 .byt $00,$00,$00,$0F,$0F,$0C,$0C,$0C
 .byt $00,$00,$00,$3C,$3C,$0C,$0C,$0C
 .byt $0C,$0C,$0C,$0F,$0F,$00,$00,$00
 .byt $0C,$0C,$0C,$3C,$3C,$00,$00,$00
 .byt $0C,$0C,$0C,$0C,$0C,$0C,$0C,$0C
 .byt $0C,$0C,$0C,$0F,$0F,$0C,$0C,$0C
 .byt $00,$00,$00,$3F,$3F,$0C,$0C,$0C
 .byt $0C,$0C,$0C,$3C,$3C,$0C,$0C,$0C
 .byt $0C,$0C,$0C,$3F,$3F,$00,$00,$00
 .byt $0C,$0C,$0C,$3F,$3F,$0C,$0C,$0C
 .byt $00,$00,$00,$0C,$0C,$0C,$0C,$0C
 .byt $0C,$0C,$0C,$0C,$0C,$00,$00,$00
 .byt $00,$00,$00,$0F,$0F,$00,$00,$00
 .byt $00,$00,$00,$3C,$3C,$00,$00,$00
 .byt $05,$0D,$05,$05,$05,$05,$05,$00
 .byt $37,$11,$11,$17,$14,$14,$37,$00
 .byt $14,$14,$14,$1C,$04,$04,$04,$00
 .byt $1D,$05,$05,$1D,$11,$11,$1D,$00
 .byt $35,$15,$15,$17,$11,$11,$31,$00
 .byt $1C,$14,$14,$1C,$14,$14,$1C,$00
 .byt $15,$15,$15,$1D,$05,$05,$05,$00
 .byt $37,$15,$15,$17,$11,$11,$37,$00
 .byt $1C,$10,$10,$1C,$14,$14,$1C,$00


_DEFCH
.(
 LDX #$C0
K1
 LDA CHARAC,X
 STA $B708,X
 DEX
 BNE K1
 RTS
.)

SCR1
 .byt $62,$61,$61,$61,$61,$61,$68,$61,$61,$61,$61,$61,$68,$61,$61,$61,$61,$61
 .byt $68,$61,$61,$61,$61,$61,$63,$00
SCR2
 .byt $66,$20,$20,$20,$20,$20,$66,$20,$20,$20,$20,$20,$66,$20,$20,$20,$20,$20
 .byt $66,$20,$20,$20,$20,$20,$66,$00
SCR3
 .byt $67,$61,$61,$61,$61,$61,$6B,$61,$61,$61,$61,$61,$6B,$61,$61,$61,$61,$61
 .byt $6B,$61,$61,$61,$61,$61,$69,$00
SCR4
 .byt $64,$61,$61,$61,$61,$61,$6A,$61,$61,$61,$61,$61,$6A,$61,$61,$61,$61,$61
 .byt $6A,$61,$61,$61,$61,$61,$65,$00

;---- Affichage des bords du tableau

_AFFSCR
.(
 LDA #>SCR1
 STA $0B
 LDA #<SCR1
 STA $0A
 LDA #$6
 STA LIG
 LDA #$0A
 STA COL
 JSR CALCPOS
 JSR PRINT
M1
 INC LIG 
 LDA #>SCR2
 STA $0B
 LDA #<SCR2
 STA $0A
 JSR CALCPOS
 JSR PRINT
 INC LIG
 JSR CALCPOS
 JSR PRINT
 INC LIG
 JSR CALCPOS
 JSR PRINT
 INC LIG
 LDA LIG
 SEC
 SBC #$16
 BEQ M2
 LDA #>SCR3
 STA $0B
 LDA #<SCR3
 STA $0A
 JSR CALCPOS
 JSR PRINT
 JMP M1
M2
 LDA #>SCR4
 STA $0B
 LDA #<SCR4
 STA $0A
 JSR CALCPOS
 JSR PRINT
 RTS
.)

;----  MONASM - ORG $7350

_SC .word $0
_TOPGAGNE .byt $00
_CL .byt $1

_MV .byt 1
MV2 .byt 1

;---- Traitement flèche gauche
_TRGAU
.(
 LDA #$00
 STA _MV
 STA MV2
D1
 PHA
 CLC
 TAX
D5
 LDA _CA,X
 BNE D14
 JMP D2
D14
 TXA
 TAY
D7
 INY
 TYA
 STA PGTMP
 PLA
 PHA
 CLC
 ADC #$4
 CMP PGTMP
 BEQ D2
 LDA _CA,Y
 BEQ D7
 CMP _CA,X
 BNE D2
 INC _CA,X
 INC _CL
 LDA #$0
 STA _CA,Y
 INC _MV
 JSR SCORE
D2
 INX
 TXA
 STA PGTMP
 PLA
 PHA
 CLC
 ADC #$3
 CMP PGTMP
 BEQ D8
 JMP D5
D8
 CLC
 PLA
 PHA
 TAX
D10
 LDA #$0
 STA MV2
 LDA _CA,X
 BEQ D15
 JMP D9
D15
 TXA 
 TAY
D12
 INY
 TYA
 STA PGTMP
 PLA
 PHA
 CLC
 ADC #$4
 CMP PGTMP
 BEQ D13
 LDA _CA,Y
 BEQ D12
 DEY
 STA _CA,Y
 INY
 LDA #$0
 STA _CA,Y
 INC MV2
 JMP D12
D13
 LDA MV2
 BEQ D3
 INC _MV
 JMP D10
D9
 INX
 TXA
 STA PGTMP
 PLA
 PHA
 CLC
 ADC #$4
 CMP PGTMP
 BEQ D3
 JMP D10
D3
 PLA
 CLC
 ADC #$4
 CMP #$10
 BEQ D16
 JMP D1
D16
 RTS
.)

;---- Incrément du score lors d une somme

SCTMP
  .word $0
SCORE
.(
 LDA #$1
 STA SCTMP
 LDA #$0
 STA SCTMP+1
 LDA _CA,X
 CMP #$0B
 BNE BL2
 STA _TOPGAGNE
BL2
 TAY
BL1
 CLC
 ASL SCTMP
 ROL SCTMP+1
 SEC
 DEY
 BNE BL1
 CLC
 LDA SCTMP
 ADC _SC
 STA _SC
 LDA SCTMP+1
 ADC _SC+1
 STA _SC+1
 RTS
.)

;---- Transformation du sommet de la pile sur 2 octets en 2^n

_PUISINIT
  .byt $0
  .byt $0
_PUISRES
  .word $0
_PUISS
.(
 LDA #$1
 STA _PUISRES
 LDA #$0
 STA _PUISRES+1
 LDY _PUISINIT
PL1
 CLC
 ASL _PUISRES
 ROL _PUISRES+1
 SEC
 DEY
 BNE PL1
 RTS
.)
;----- Traitement flèche BAS
_TRBAS
.(
 LDA #$0
 STA _MV
 STA MV2
U1
 PHA
 CLC
 ADC #$C
 TAX
U5
 LDA _CA,X
 BNE U6
 JMP U2
U6
 TXA
 TAY
U7
 TYA
 SEC
 SBC #$4
 BMI U2
 TAY
 LDA _CA,Y
 BEQ U7
 CMP _CA,X
 BNE U2
 INC _CA,X
 INC _CL
 LDA #$0
 STA _CA,Y
 INC _MV
 JSR SCORE
U2
 TXA
 SEC
 SBC #$4
 TAX
 STA PGTMP
 PLA
 PHA
 CMP PGTMP
 BEQ U8
 JMP U5
U8
 CLC
 ADC #$C
 TAX
U10
 LDA #$0
 STA MV2
 LDA _CA,X
 BEQ U11
 JMP U9
U11
 TXA
 TAY
U12
 SEC
 DEY
 DEY
 DEY
 DEY
 BMI U13
 LDA _CA,Y
 BEQ U12
 CLC
 INY
 INY
 INY
 INY
 STA _CA,Y
 SEC
 DEY
 DEY
 DEY
 DEY 
 LDA #$0
 STA _CA,Y
 INC MV2
 JMP U12
U13
 LDA MV2
 BEQ U3
 INC _MV
 JMP U10
U9
 TXA
 SEC
 SBC #$4
 TAX
 STA PGTMP
 PLA
 PHA
 CMP PGTMP
 BEQ U3
 JMP U10
U3
 PLA
 CLC
 ADC #$1
 CMP #$4
 BEQ U4
 JMP U1
U4
 RTS
.)

;--- Flèche droite

_TRDRO
.(
 LDA #$0
 STA _MV
 STA MV2
D1
 PHA
 CLC
 ADC #$3
 TAX
D5
 LDA _CA,X
 BNE D6
 JMP D2
D6
 TXA
 TAY
D7
 TYA
 STA PGTMP
 PLA
 PHA
 CMP PGTMP
 BEQ D2
 DEY
 LDA _CA,Y
 BEQ D7
 CMP _CA,X
 BNE D2
 INC _CA,X
 INC _CL
 LDA #$0
 STA _CA,Y
 INC _MV
 JSR SCORE
D2 
 DEX
 TXA
 STA PGTMP
 PLA
 PHA
 CLC
 CMP PGTMP
 BEQ D8
 JMP D5
D8 
 CLC
 PLA
 PHA
 ADC #$3
 TAX
D10 
 LDA #$0
 STA MV2
 LDA _CA,X
 BEQ D11
 JMP D9
D11 
 TXA
 TAY
D12 
 TYA
 STA PGTMP
 PLA
 PHA
 CMP PGTMP
 BEQ D13
 DEY
 LDA _CA,Y
 BEQ D12
 INY
 STA _CA,Y
 DEY 
 LDA #$0
 STA _CA,Y
 INC MV2
 JMP D12
D13 
 LDA MV2
 BEQ D3
 INC _MV
 JMP D10
D9 
 TXA
 STA PGTMP
 PLA
 PHA
 CMP PGTMP
 BEQ D3
 DEX
 JMP D10
D3 
 PLA
 CLC
 ADC #$4
 CMP #$10
 BEQ D4
 JMP D1
D4 
 RTS
.)


  
_TRHAU
.(
 LDA #$0
 STA _MV
 STA MV2
E1 PHA
 TAX
E5
 LDA _CA,X
 BNE E6
 JMP E2
E6
 TXA
 TAY
E7
 TYA
 CLC
 ADC #$4
 STA PGTMP
 TAY
 CLC
 PLA
 PHA
 ADC #$10
 CMP PGTMP
 BEQ E2
 LDA _CA,Y
 BEQ E7
 CMP _CA,X
 BNE E2
 INC _CA,X
 INC _CL
 LDA #$0
 STA _CA,Y
 INC _MV
 JSR SCORE
E2
 TXA
 CLC
 ADC #$4
 TAX
 STA PGTMP
 PLA
 PHA
 ADC #$C
 CMP PGTMP
 BEQ E8
 JMP E5
E8
 PLA
 PHA
 TAX
E10
 LDA #$0
 STA MV2
 LDA _CA,X
 BEQ E11
 JMP E9
E11
 TXA
 TAY
E12
 CLC
 TYA
 ADC #$4
 TAY
 STA PGTMP
 PLA
 PHA
 ADC #$10
 CMP PGTMP
 BEQ E13
 LDA _CA,Y
 BEQ E12
 DEY
 DEY
 DEY
 DEY 
 STA _CA,Y
 INY
 INY
 INY
 INY
 LDA #$0
 STA _CA,Y
 INC MV2
 JMP E12
E13
 LDA MV2
 BEQ E3
 INC _MV
 JMP E10
E9
 TXA
 CLC
 ADC #$4
 TAX
 STA PGTMP
 PLA
 PHA
 ADC #$C
 CMP PGTMP
 BEQ E3
 JMP E10
E3 
 PLA
 CLC
 ADC #$1
 CMP #$4
 BEQ E4
 JMP E1
E4
 RTS
.)

ranPGTMP .byt $00
_rand01
.(
	ldx #$ff
	jsr $E355
	lda $D1
	and #$01
	tax
	lda #$00
	rts
.)

_rand1248
.(
	ldx #$ff
	jsr $E355
	lda $D1
	and #$0F
	tax
	lda #$00
	rts
.)