_CG_DEFCHAR
.(
	lda #<_CG_DATA
	sta tmp0
	lda #>_CG_DATA
	sta tmp0+1
	lda #$00
	sta tmp1
	lda #$B9
	sta tmp1+1
	
	ldy #0
boucle1
	dey
	lda (tmp0),y
	sta (tmp1),y
	cpy #0
	bne boucle1
	
	inc tmp0+1
	inc tmp1+1
	
	ldy #0
boucle2
	dey
	lda (tmp0),y
	sta (tmp1),y
	cpy #0
	bne boucle2
	
	inc tmp0+1
	inc tmp1+1
	
	ldy #120
boucle3
	dey
	lda (tmp0),y
	sta (tmp1),y
	cpy #0
	bne boucle3
	
	rts
.)

_CG_DATA
_CHARSET	
CardSpace	
.byt 0,0,0,0,0,0,0,0
Card1	; ==> caractere 33 en LORES 1
	.byt 0,0,3,7,14,12,12,12
	.byt 0,0,48,56,28,12,12,12
	.byt 15,15,12,12,12,12,0,0
	.byt 60,60,12,12,12,12,0,0
Card2
	.byt 0,0,3,7,14,12,0,0
	.byt 0,0,48,56,28,12,12,28
	.byt 0,1,3,7,15,15,0,0
	.byt 56,48,32,0,60,60,0,0
Card3
	.byt 0,0,3,7,14,12,0,1
	.byt 0,0,48,56,28,12,28,56
	.byt 1,0,12,14,7,3,0,0
	.byt 56,28,12,28,56,48,0,0
Card4
	.byt 0,0,0,0,1,3,7,14
	.byt 0,0,28,60,60,44,12,12
	.byt 15,15,0,0,0,0,0,0
	.byt 60,60,12,12,12,12,0,0
Card5
	.byt 0,0,15,15,12,12,15,15
	.byt 0,0,60,60,0,0,48,56
	.byt 0,0,12,14,7,3,0,0
	.byt 28,12,12,28,56,48,0,0
Card6
	.byt 0,0,3,7,14,12,15,15
	.byt 0,0,56,60,12,0,48,56
	.byt 14,12,12,14,7,3,0,0
	.byt 28,12,12,28,56,48,0,0
Card7
	.byt 0,0,15,15,0,0,1,3
	.byt 0,0,60,60,28,56,48,32
	.byt 3,3,3,3,3,3,0,0
	.byt 0,0,0,0,0,0,0,0
Card8
	.byt 0,0,3,7,14,12,14,7
	.byt 0,0,48,56,28,12,28,56
	.byt 7,14,12,14,7,3,0,0
	.byt 56,28,12,28,56,48,0,0
Card9
	.byt 0,0,3,7,14,12,12,14
	.byt 0,0,48,56,28,12,12,28
	.byt 7,3,0,12,15,7,0,0
	.byt 60,60,12,28,56,48,0,0
Card10
	.byt 0,0,13,13,13,13,13,13
	.byt 0,0,60,60,44,44,44,44
	.byt 13,13,13,13,13,13,0,0
	.byt 44,44,44,44,60,60,0,0
CardJ
	.byt 0,0,0,0,0,0,0,0
	.byt 0,0,12,12,12,12,12,12
	.byt 0,0,12,14,7,3,0,0
	.byt 12,12,12,28,56,48,0,0
CardQ
	.byt 0,0,3,7,14,12,12,12
	.byt 0,0,48,56,28,12,12,12
	.byt 12,12,12,14,7,3,0,0
	.byt 12,12,28,56,60,60,0,0
CardK
	.byt 0,0,12,12,12,12,12,15
	.byt 0,0,12,12,12,28,56,48
	.byt 15,12,12,12,12,12,0,0
	.byt 48,56,28,12,12,12,0,0

CardTrefle
	.byt 0,0,0,1,3,3,3,13
	.byt 0,0,0,32,48,48,48,44
	.byt 31,31,31,13,1,3,0,0
	.byt 62,62,62,44,32,48,0,0
Cardcarreau
	.byt 0,0,1,3,3,7,15,15
	.byt 0,0,32,48,48,56,60,60
	.byt 15,15,7,3,3,1,0,0
	.byt 60,60,56,48,48,32,0,0
CardCoeur
	.byt 0,0,0,12,30,31,31,31
	.byt 0,0,0,12,30,62,62,62
	.byt 15,15,7,3,1,0,0,0
	.byt 60,60,56,48,32,0,0,0
CardPique
	.byt 0,0,1,1,3,3,7,15
	.byt 0,0,32,32,48,48,56,60
	.byt 31,31,31,13,1,3,0,0
	.byt 62,62,62,44,32,48,0,0

CardHG ; 101
	.byt 0,7,15,28,24,24,24,24
CardHD ; 102
	.byt 0,56,60,14,6,6,6,6
CardBG ; 103
	.byt 24,24,24,24,28,15,7,0
CardBD ; 104
	.byt 6,6,6,6,14,60,56,0
CardGauche ; 105
	.byt 24,24,24,24,24,24,24,24
CardDroite ; 106
	.byt 6,6,6,6,6,6,6,6
CardHaut ; 107
	.byt 0,63,63,0,0,0,0,0
CardBas ; 108
	.byt 0,0,0,0,0,63,63,0

CardMotif ; 109
	.byt 33,51,30,12,12,30,51,33

CardBG2
    .byt 24,24,24,24,28,31,31,24
CardBD2
    .byt 6,6,6,6,14,62,62,6
