;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-;
;
; UniJoystiCle test for the C64
;
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-;

;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-;
; Macros
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-;
.macpack cbm                            ; adds support for scrcode

;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-;
; Constants
;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-;
.include "c64.inc"                      ; c64 constants

.segment "CODE"

.proc main
        sei

        ldx #$ff                        ; reset stack... just in case
        txs

        lda #0
        sta $d01a                       ; no raster interrups


        lda #0
        sta $d020                       ; border color
        lda #0
        sta $d021                       ; background color

        lda #$00                        ; background & border color
        sta $d020
        sta $d021

        lda #$7f                        ; turn off cia interrups
        sta $dc0d
        sta $dd0d

        lda $dc0d                       ; clear interrupts and ACK irq
        lda $dd0d
        asl $d019

        lda #$00                        ; turn off volume
        sta SID_Amp

        lda #%00011011                  ; charset mode, default scroll-Y position, 25-rows
        sta $d011                       ; extended color mode: off

        lda #%00001000                  ; no scroll, hires (mono color), 40-cols
        sta $d016                       ; turn off multicolor

        lda #%00011110                  ; charset at $3800
        sta $d018

        lda $dd00                       ; Vic bank 0: $0000-$3FFF
        and #$fc
        ora #3
        sta $dd00


        ldx #0
l1:
        lda screen + $0000,x
        sta $0400 + $0000,x
        tay
        lda screen_colors,y
        sta $d800 + $0000,x

        lda screen + $0100,x
        sta $0400 + $0100,x
        tay
        lda screen_colors,y
        sta $d800 + $0100,x

        lda screen + $0200,x
        sta $0400 + $0200,x
        tay
        lda screen_colors,y
        sta $d800 + $0200,x

        lda screen + $02e8,x
        sta $0400 + $02e8,x
        tay
        lda screen_colors,y
        sta $d800 + $02e8,x

        inx
        bne l1

        jsr init_sprites

        cli

        lda #%11000000
        sta $dc02                       ; disable keyboard

main_loop:

        lda #%00111111                  ; enable joystick
        sta $dc00

        jsr print_joy1
        jsr print_joy2

        lda #%01000000                  ; enable pot A
        sta $dc00
        ldx #0                          ; wait a few cycles
@l0:    dex                             ; after enabling the POT
        bne @l0
        jsr print_pot1

        lda #%10000000                  ; enable pot B
        sta $dc00
        ldx #0                          ; wait a few cycles
@l1:    dex                             ; after enabling the POT
        bne @l1
        jsr print_pot2

        jmp main_loop
.endproc

.proc init_sprites

        ldx #192                ; setup sprite frames
        stx $07f8
        stx $07fc

        inx
        stx $07f9
        stx $07fd

        inx
        stx $07fa
        stx $07fe

        inx
        stx $07fb
        stx $07ff

        ldx #7
        ldy #14
l1:
        lda #7                          ; setup sprite colors
        sta VIC_SPR0_COLOR,x

        lda posx,x
        sta VIC_SPR0_X,y
        lda posy,x
        sta VIC_SPR0_Y,y

        dey
        dey
        dex
        bpl l1

        lda #%11111111
        sta VIC_SPR_ENA

        lda #0
        sta VIC_SPR_EXP_X               ; no expansion
        sta VIC_SPR_EXP_Y
        sta VIC_SPR_MCOLOR              ; no multicolor

        rts

OFFX = 20
OFFY = 50
posx:
        .byte 12*8 + OFFX               ; sprite 0
        .byte 12*8 + OFFX               ; 1
        .byte  9*8 + OFFX               ; 2
        .byte 14*8 + OFFX               ; 3

        .byte 27*8 + OFFX
        .byte 27*8 + OFFX
        .byte 24*8 + OFFX
        .byte 29*8 + OFFX
posy:
        .byte 16*8 + OFFY               ; sprite 0
        .byte 21*8 + OFFY               ; 1
        .byte 19*8 + OFFY               ; 2
        .byte 19*8 + OFFY               ; 3

        .byte 16*8 + OFFY
        .byte 21*8 + OFFY
        .byte 19*8 + OFFY
        .byte 19*8 + OFFY

.endproc

.proc print_joy1
        lda $dc01                       ; joy #1
        eor #%00011111
        sta $f9                         ; tmp
        and #%00001111
        sta $f8                         ; tmp

        lda VIC_SPR_ENA
        and #%11110000
        ora $f8
        sta VIC_SPR_ENA

        lda $f9
        and #%00010000                  ; fire?
        beq no_fire
        lda #7                          ; color for fire on
        bne print_fire
no_fire:
        lda #11                         ; color for fire off
print_fire:
        sta $d800 + 40 * 19 + 12

        rts
.endproc

.proc print_joy2
        lda $dc00                       ; joy #1
        eor #%00011111
        sta $f9
        asl
        asl
        asl
        asl
        sta $f8                         ; tmp

        lda VIC_SPR_ENA
        and #%00001111
        ora $f8
        sta VIC_SPR_ENA

        lda $f9
        and #%00010000                  ; fire?
        beq no_fire
        lda #7                          ; color for fire on
        bne print_fire
no_fire:
        lda #11                         ; color for fire off
print_fire:
        sta $d800 + 40 * 19 + 27

        rts
.endproc

.proc print_pot1
        lda $d41a                       ; pot X
        ; sta VIC_SPR0_X
        tay                             ; save A
        and #%00001111
        tax
        lda hex,x                       ; print LSB
        sta 1024 + 20 * 40 + 4

        tya                             ; restore A

        lsr
        lsr
        lsr
        lsr
        tax
        lda hex,x                       ; print MSB
        sta 1024 + 20 * 40 + 3



        lda $d419                       ; pot Y
        ; sta VIC_SPR0_X+2
        tay                             ; save it
        and #%00001111
        tax
        lda hex,x                       ; print LSB
        sta 1024 + 21 * 40 + 4

        tya
        lsr
        lsr
        lsr
        lsr
        tax
        lda hex,x                       ; print MSB
        sta 1024 + 21 * 40 + 3
        rts
.endproc

.proc print_pot2
        lda $d41a                       ; pot X
        tay                             ; save A
        and #%00001111
        tax
        lda hex,x                       ; print LSB
        sta 1024 + 20 * 40 + 39

        tya                             ; restore A

        lsr
        lsr
        lsr
        lsr
        tax
        lda hex,x                       ; print MSB
        sta 1024 + 20 * 40 + 38



        lda $d419                       ; pot Y
        tay                             ; save it
        and #%00001111
        tax
        lda hex,x                       ; print LSB
        sta 1024 + 21 * 40 + 39

        tya
        lsr
        lsr
        lsr
        lsr
        tax
        lda hex,x                       ; print MSB
        sta 1024 + 21 * 40 + 38
        rts
.endproc

hex:    scrcode "0123456789abcdef"

screen:
        .incbin "unijoysticle-map.bin"
screen_colors:
        .incbin "unijoysticle-colors.bin"

.segment "SPRITES"
        .incbin "sprites.bin"

.segment "CHARSET"
        .incbin "unijoysticle-charset.bin"
