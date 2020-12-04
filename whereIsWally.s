section .text

global whereIsWally
whereIsWally:
	push rbp
	mov rbp, rsp
	
	;LOKALIZACJE ARGUMENTOW
	;rdi		rsi		        rdx		    rcx		r8	r9
	;bitmapData	bitmapPattern	width		height	
	;[rbp - 8]	[rbp - 16]	    [rbp - 24]	[rbp-32]

	sub rsp, 32			;alokuj pamiec na stosie
	
	mov [rbp - 8], rdi		;bitmapData
	mov [rbp - 16], rsi		;bitmapPattern <- wzorzec 4x4
	mov [rbp - 24], rdx		;width
	mov [rbp - 32], rcx		;height
;CORNER CASES
    cmp rdx, 4
    jl exit_success
    cmp rcx, 4
    jl exit_success
	
	mov r8, 0			;wspolrzedna x sprawdzanego piksela
	mov r9, 0			;wspolrzedna y sprawdzanego piksela
    
    mov r10, rdx        ;prawa granica sprawdzania
    sub r10, 3

    mov r11, rcx        ;gorna granica sprawdzania
    sub r11, 3

	mov r15, 0			;licznik wystapien patternu w data

find_wally_checkpoint:
    mov rax, r9          ;obliczenie offsetu

    mov rdx, [rbp - 24]
    mul rdx              ;offset ze wspolrzednej y [w slowach]
    shl rax, 2           ;offset ze wspolrzednej y [w bajtach]

    mov rbx, r8          ;offset ze wspolrzednej x
    shl rbx, 2

    add rax, rbx         ;offset calkowity

    mov rcx, [rbp - 8]   ;adres piksela do porownania z bitmapData w rcx
    add rcx, rax

    mov rbx, [rbp - 16]      ;adres piksela z bitmapPattern w rbx

    mov eax, [rbx]          ;wartosc pixela z bitmapPattern w eax


    cmp eax, [rcx]        ;porownanie pikseli
    jne next_pixel     ;jesli pixele nie sa rowne -> kolejny pixel


;PETLA POROWNYWANIA WYCINKOW 4X4
    mov r13, 1          ;tempX - względny x
    mov r14, 0          ;tempY - względny y

compare_4x4_pixels_array:
    mov rdx, [rbp - 24]
    mov rax, r14
    mul rdx
    add rax, r13
    shl rax, 2          ;offset względny bmpData w rax
    
    mov r12, r14         ;r12 = tempY
    shl r12, 2           ;r12 *= 4
    add r12, r13         ;r12 += tempX
    shl r12, 2           ;r12 *= 4
    mov edx, [rbx+r12]    ;wartosc z bmpPattern w edx
    
    cmp edx, [rcx + rax] ;porownanie odpowiednich pixeli

    
    jne next_pixel       ;jesli nierowne -> idziemy dalej
    inc r13                 ;x++
    cmp r13, 4          ;x==4?
    jne compare_4x4_pixels_array
    inc r14             ;y++
    mov r13, 0          ;x=0
    cmp r14, 4          ;y==4?
    jne compare_4x4_pixels_array

    inc r15

next_pixel:
    inc r8              ;x++
    cmp r8, r10         ;x ? prawa granica sprawdzania
    jne find_wally_checkpoint
    inc r9              ;y++
    mov r8, 0           ;x=0
    cmp r9, r11         ;y ? gorna granica sprawdzania
    jne find_wally_checkpoint

exit_success:
    mov rax, r15
	mov rsp, rbp
	pop rbp
	ret
