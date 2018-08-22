
.zero

*= $7A

tmpC .dsb 2
tmpE .dsb 2

.text

_CardX .dsb 1
_CardY .dsb 1
_CardNumber .dsb 1
_CardColor  .dsb 1

posit .dsb 2
posNumber .dsb 2
posColor .dsb 2

cardCaract .dsb 1

CG_defCardAddr
.(
	lda #$BB
	sta posit+1
	clc
	lda #$80
	adc _CardY
	ldx _CardX
	beq fin
boucle1
	adc #$28
	bcc boucle2
	inc posit+1
	clc
boucle2
	dex
	bne boucle1
fin
	sta posit
	rts
.)

CG_printCardNumber
.(
	clc
	lda posit
	adc #$2B
	sta CG_plot+1
	lda posit+1
	adc #0
	sta CG_plot+2

	ldx _CardNumber	
	dex
	txa
	asl
	asl
	adc #33
	tax
	jmp CG_printCardContent
.)

CG_plot
.(
	stx $1234
	rts
.)

CG_printCardColor
.(
	clc
	lda posit
	adc #124
	sta CG_plot+1
	lda posit+1
	adc #0
	sta CG_plot+2

	ldx _CardColor	
	dex
	txa
	asl
	asl
	adc #85
	tax
	jmp CG_printCardContent

.)

CG_printCardContent
.(
; caractère 1
	jsr CG_plot

;caractère 2	
	inx
	inc CG_plot+1
	bcc suite
	inc CG_plot+2
suite
	jsr CG_plot

; caractère 3
	inx
	clc
	lda #$27
	adc CG_plot+1
	sta CG_plot+1
	bcc suite2
	inc CG_plot+2
suite2
	jsr CG_plot
	
;caractère 4
	inx
	inc CG_plot+1
	bcc suite3
	inc CG_plot+2
suite3
	jsr CG_plot
	rts
.)

CG_printCardBorder
.(
	lda _CardColor
	
	cmp #1
	beq noire
	cmp #4
	beq noire
	cmp #2
	beq rouge
	cmp #3
	beq rouge
	cmp #5
	beq etiflip
	
	
noire

	lda #<carteNoire
	sta tmpC
	lda #>carteNoire
	sta tmpC+1
	ldx #$6
	jmp suite

rouge
	lda #<carteRouge
	sta tmpC
	lda #>carteRouge
	sta tmpC+1
	ldx #$6
	jmp suite

etiflip
	lda #<carteFlip
	sta tmpC
	lda #>carteFlip
	sta tmpC+1
	ldx #$6
	jmp suite
	
suite
	lda posit
	sta tmpE
	lda posit+1
	sta tmpE+1

boucle1
	ldy #$6
boucle2
	lda (tmpC),y
	sta (tmpE),y

	dey
	bne boucle2

	clc
	lda tmpC
	adc #6
	sta tmpC
	lda tmpC+1
	adc #0
	sta tmpC+1

	clc
	lda tmpE
	adc #40
	sta tmpE
	lda tmpE+1
	adc #0
	sta tmpE+1
	

	dex
	bne boucle1
	rts
	
.)

CG_eraseCard
.(

	ldx #$6

	lda posit
	sta tmpE
	lda posit+1
	sta tmpE+1

	lda #32
	
boucle1
	ldy #$6
boucle2
	sta (tmpE),y

	dey
	bne boucle2

	clc
	lda tmpE
	adc #40
	sta tmpE
	lda tmpE+1
	adc #0
	sta tmpE+1
	lda #32

	dex
	bne boucle1
	rts
	
.)

_printCard
.(
	ldy #0
	lda (sp),y
	sta _CardY
	iny
	iny
	lda (sp),y
	sta _CardX
	iny
	iny
	lda (sp),y
	sta _CardNumber
	iny
	iny
	lda (sp),y
	sta _CardColor
	
	jsr CG_defCardAddr
	jsr CG_printCardBorder
	ldx _CardNumber
	cpx #0
	beq fin
	jsr CG_printCardNumber
	jsr CG_printCardColor
fin
	rts
	

.)

_eraseCard
.(
	ldy #0
	lda (sp),y
	sta _CardY
	iny
	iny
	lda (sp),y
	sta _CardX
	
	jsr CG_defCardAddr
	jsr CG_eraseCard
	rts
	

.)

carteRouge
.byt 0
.byt 001,101,107,107,107,102
.byt 001,105,032,032,032,106
.byt 001,105,032,032,032,106
.byt 001,105,032,032,032,106
.byt 001,105,032,032,032,106
.byt 001,103,108,108,108,104

carteNoire
.byt 0
.byt 000,101,107,107,107,102
.byt 000,105,032,032,032,106
.byt 000,105,032,032,032,106
.byt 000,105,032,032,032,106
.byt 000,105,032,032,032,106
.byt 000,103,108,108,108,104

carteFlip
.byt 0
.byt 000,032,101,107,102,032
.byt 000,032,105,032,106,032
.byt 000,032,105,032,106,032
.byt 000,032,105,032,106,032
.byt 000,032,105,032,106,032
.byt 000,032,103,108,104,032

cartePaquet
.byt 0
.byt 000,101,107,107,107,102
.byt 000,105,032,032,032,106
.byt 000,105,032,032,032,106
.byt 000,105,032,032,032,106
.byt 000,105,032,032,032,106
.byt 000,110,108,108,108,111

Efface
.byt 0
.byt 000,032,032,032,032,032
.byt 000,032,032,032,032,032
.byt 000,032,032,032,032,032
.byt 000,032,032,032,032,032
.byt 000,032,032,032,032,032
.byt 000,032,032,032,032,032
